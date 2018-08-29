/*==============================================================================

sceneの処理 [scene.cpp]
作成者 : 中西　祐介
作成日 : 2016/4/17
--------------------------------------------------------------------------------
■Update :
==============================================================================*/

/*------------------------------------------------------------------------------
　ヘッダファイル
 ------------------------------------------------------------------------------*/
#include "scene.h"
#include "modeGame.h"
#include <algorithm>

CScene* CScene::m_Top[NUM_PRIORITY] = {};
int CScene::m_nNumScene = 0;
std::vector<CScene*> CScene::c_scene = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CScene::CScene(int Priolity)
{
	if (Priolity == PRIORITY_BILLBOARD)
	{
		c_scene.push_back(this);
	}

	if (m_Top[Priolity] == NULL)
	{
		m_Top[Priolity] = this;
		m_Next = NULL;
	}
	else
	{
		CScene* scene = m_Top[Priolity];
		while (scene->m_Next != NULL)
		{
			scene = scene->m_Next;
		}
		scene->m_Next = this;
		this->m_Next = NULL;
	}

	// 削除フラグ初期化
	m_Delete = false;
	m_doUninit = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CScene::~CScene()
{
}

//=============================================================================
// 終了処理
//=============================================================================
void CScene::Uninit(void)
{
	//Release();
	SetDelete();
}

//=============================================================================
// 更新処理
//=============================================================================
void CScene::UpdateAll(void)
{
	// 更新処理
	for (int nCnt = 0; nCnt < NUM_PRIORITY; nCnt++)
	{
		CScene* scene = m_Top[nCnt];
		while (scene != NULL)
		{
			scene->Update();
			scene = scene->m_Next;
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CScene::DrawAll(void)
{
	//for( int nCnt = 0; nCnt < NUM_PRIORITY; nCnt++ )
	{
		CScene* scene = m_Top[PRIORITY_3D];
		while (scene != NULL)
		{
			scene->Draw();
			scene = scene->m_Next;
		}

		for (auto it = c_scene.begin(); it != c_scene.end(); ++it)
		{
			(*it)->Draw();
		}

		scene = m_Top[PRIORITY_2D];
		while (scene != NULL)
		{
			scene->Draw();
			scene = scene->m_Next;
		}
	}
}

//=============================================================================
// 全削除
//=============================================================================
void CScene::ReleaseAll(void)
{
	for (int nCnt = 0; nCnt < NUM_PRIORITY; nCnt++)
	{
		CScene* scene = m_Top[nCnt];
		CScene* next = NULL;
		while (scene != NULL)
		{
			next = scene->m_Next;
			scene->Uninit();
			delete scene;
			scene = next;
		}

		m_Top[nCnt] = NULL;
	}
}

//=============================================================================
// 削除チェック
//=============================================================================
void CScene::CheckRelease(void)
{
	for (int nCnt = 0; nCnt < NUM_PRIORITY; nCnt++)
	{
		CScene* scene = m_Top[nCnt];
		while (scene != NULL)
		{
			scene = scene->m_Next;
		}

		// 削除処理
		CScene* scenePrev = m_Top[nCnt];
		CScene* sceneNext = NULL;
		scene = m_Top[nCnt];

		while (scene != NULL)
		{
			sceneNext = scene->m_Next;
			if (scene->m_Delete)
			{
				if (scene == m_Top[nCnt])
				{
					m_Top[nCnt] = scene->m_Next;
				}
				else
				{
					scenePrev->m_Next = scene->m_Next;
				}

				delete scene;
				scene = NULL;
			}
			else
			{
				scenePrev = scene;
			}

			scene = sceneNext;
		}
	}

	// ビルボードの削除
	c_scene.erase(std::remove_if(c_scene.begin(), c_scene.end(), [](CScene* p) {if (p->GetDoUninit()) { return true; }return false; }), c_scene.end());
}

//=============================================================================
// 終了処理のチェック
//=============================================================================
void CScene::CheckUninit(void)
{
	for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
	{
		CScene* scene = m_Top[nCnt];
		while (scene != NULL)
		{
			if (scene->GetDoUninit())
			{
				scene->Uninit();
			}

			scene = scene->m_Next;
		}
	}
}

//=============================================================================
// ビルボードのソート
//=============================================================================
void CScene::SortBillboard(void)
{
	// カメラの水平線からの距離でソートする	
	CScene* billboard = m_Top[PRIORITY_BILLBOARD];
	CScene* next = NULL;
	D3DXVECTOR3 vecC = CModeGame::GetCamera()->GetFlatLine();
	D3DXVECTOR3 posCam = CModeGame::GetCamera()->GetPosEye();
	while (billboard != NULL)
	{
		D3DXVECTOR3 vecP = billboard->GetPos() - posCam;
		D3DXVECTOR3 vecH = vecC * D3DXVec3Dot(&vecC, &vecP) / 1 - vecP;
		billboard->SetLenToCamLine(D3DXVec3Length(&vecH));

		billboard = billboard->m_Next;
	}

	std::sort(c_scene.begin(), c_scene.end(), [](CScene* a, CScene* b) {return a->m_lenToCamLine > b->m_lenToCamLine; });
}