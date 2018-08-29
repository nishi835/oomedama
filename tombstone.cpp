/*==============================================================================

tombstoneの処理 [tombstone.cpp]
作成者 : 中西　祐介
作成日 :
--------------------------------------------------------------------------------
■Update :
==============================================================================*/

//-------------------------------------------------------------------------------
//  ヘッダ
//-------------------------------------------------------------------------------
#include "main.h"
#include "modeGame.h"
#include "textureManager.h"
#include "renderer.h"
#include "tombstone.h"
#include "camera.h"
#include "light.h"

//-------------------------------------------------------------------------------
//  マクロ
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
//  デストラクタ
//-------------------------------------------------------------------------------
CTombstone::~CTombstone()
{
}

//-------------------------------------------------------------------------------
//  初期化
//-------------------------------------------------------------------------------
void CTombstone::Init(D3DXVECTOR3 pos, char* filePass)
{
	// パラメータ設定
	m_pos = pos;
	strcpy_s(m_filePass, filePass);

	// 初期化
	CSceneModel::Init();

	// モデルの半径取得 ///////////////////////////////////////////////////////////

	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	LPD3DXMESH pCloneMesh;
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;
	VERTEX_3D* pVertex;

	// メッシュの取得
	m_pMeshModel->CloneMeshFVF(D3DXMESH_MANAGED, FVF_VERTEX_3D, pDevice, &pCloneMesh);

	// 頂点数のカウント
	int count = pCloneMesh->GetNumVertices();

	// 頂点バッファ取得
	pCloneMesh->GetVertexBuffer(&pVtxBuff);

	// 頂点バッファをロック
	VERTEX_3D* vertex;
	pVtxBuff->Lock(0, 0, (void**)&vertex, 0);

	// 半径の取得
	D3DXVECTOR3 temp;
	float len = 0;
	m_radius = 0;
	for (int i = 0; i < count; i++)
	{
		temp = vertex[i].pos;
		len = D3DXVec3Length(&temp);
		m_radius = max(len, m_radius);
	}
	
	// 高さ設定
	m_pos.y = CModeGame::GetMeshField()->GetHeight(m_pos) - m_radius * 0.07f;

	// オブジェクトタイプの設定
	SetObjType(OBJTYPE_NONE);
}

//-------------------------------------------------------------------------------
//  終了処理
//-------------------------------------------------------------------------------
void CTombstone::Uninit(void)
{
}

//-------------------------------------------------------------------------------
//  描画
//-------------------------------------------------------------------------------
void CTombstone::Draw(void)
{
	CSceneModel::Draw();
}

//-------------------------------------------------------------------------------
//  作成
//-------------------------------------------------------------------------------
CTombstone* CTombstone::Create(D3DXVECTOR3 pos, float rotThe, float rotFai, char* filePass)
{
	CTombstone* pTombstone = new CTombstone(PRIORITY_3D);
	pTombstone->SetRotThe(rotThe);
	pTombstone->SetRotFai(rotFai);
	pTombstone->Init(pos, filePass);
	return pTombstone;
}

