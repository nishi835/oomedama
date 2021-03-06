/*==============================================================================

backgroundの処理 [background.cpp]
作成者 : 中西　祐介
作成日 :
--------------------------------------------------------------------------------
■Update :
==============================================================================*/

/*------------------------------------------------------------------------------
　ヘッダファイル
 ------------------------------------------------------------------------------*/
#include "main.h"
#include "scene2D.h"
#include "background.h"

/*------------------------------------------------------------------------------
 　マクロ定義
 ------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
　初期化
------------------------------------------------------------------------------*/
void CBackground::Init(void)
{
	CScene2D::Init();
}

/*------------------------------------------------------------------------------
　終了処理
 ------------------------------------------------------------------------------*/
void CBackground::Uninit(void)
{
	//CScene::Release();
	CScene::SetDelete();
}

/*------------------------------------------------------------------------------
　更新
 ------------------------------------------------------------------------------*/
void CBackground::Update(void)
{
	CScene2D::Update();
}

/*------------------------------------------------------------------------------
　ポリゴン描画処理
 ------------------------------------------------------------------------------*/
void CBackground::Draw(void)
{
	CScene2D::Draw();
}

/*------------------------------------------------------------------------------
　作成
 ------------------------------------------------------------------------------*/
CBackground* CBackground::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float alpha,  char* filePass)
{
	CBackground* pBackground = new CBackground(CScene::PRIORITY_2D);

	// 初期化
	pBackground->SetPos(pos);
	pBackground->SetSize(size);
	pBackground->SetAlpha(alpha);

	// テクスチャIDの設定
	pBackground->SetTexID(CTextureManager::LoadTexture(filePass, CTextureManager::TEXTYPE_NONE));
	pBackground->Init();

	return pBackground;
}

