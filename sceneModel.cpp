/*==============================================================================

モデルの処理 [model.cpp]
作成者 : 中西　祐介
作成日 : 2016/4/17
--------------------------------------------------------------------------------
■Update :
==============================================================================*/

/*------------------------------------------------------------------------------
　ヘッダファイル
 ------------------------------------------------------------------------------*/
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "sceneModel.h"
#include "player.h"

/*------------------------------------------------------------------------------
 　マクロ定義
------------------------------------------------------------------------------*/
#define WHITE_TEXTURE_NAME  "data/TEXTURE/white.jpg"

/*------------------------------------------------------------------------------
  　グローバル変数
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
　静的メンバ変数
------------------------------------------------------------------------------*/
char CSceneModel::m_filePass[256] = {};

/*------------------------------------------------------------------------------
　モデルの初期化
------------------------------------------------------------------------------*/
void CSceneModel::Init(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// モデルのロード
	HRESULT hr;
	
	hr = (D3DXLoadMeshFromX(m_filePass,		// モデルのファイル名
		D3DXMESH_MANAGED,		// CreateVertexBufferを使う宣言
		pDevice,				// デバイス
		NULL,					// 隣接情報
		&m_pBuffMatModel,		// モデルのマテリアル情報のポインタを格納
		NULL,
		&m_nNumMatModel,        // マテリアルの数
		&m_pMeshModel			// メッシュ情報インターフェースのポインタを格納
	));

	// エラーチェック
	if (FAILED(hr))
	{
		MessageBox(NULL, "モデル読み込み失敗", "エラー", MB_OK); // エラーチェック
	}

	// マテリアルの取得
	D3DXMATERIAL* pMat; // マテリアル情報のアドレス格納用
	pMat = (D3DXMATERIAL*)m_pBuffMatModel->GetBufferPointer();

	// テクスチャをインターフェースに格納
	for (int nCnt = 0; nCnt < (int)m_nNumMatModel; nCnt++)
	{
		// テクスチャがなければ、白いテクスチャを貼る
		if (pMat[nCnt].pTextureFilename == NULL)
		{
			if (FAILED(D3DXCreateTextureFromFile(pDevice,				     // デバイスのポインタを渡す
				WHITE_TEXTURE_NAME,		     // テクスチャのファイル名
				&m_pTextureModel)))	     // テクスチャインターフェースの格納
			{
				MessageBox(NULL, "白テクスチャ読み込み失敗", "エラー", MB_OK); // エラーチェック
			}
		}
		else
		{
			// テクスチャファイルのパスを修正
			char* aStr = "data\\TEXTURE";
			char* aTemp = strstr(pMat[nCnt].pTextureFilename, aStr);

			// テクスチャの読み込み
			if (FAILED(D3DXCreateTextureFromFile(pDevice,				    // デバイスのポインタを渡す
				aTemp,					    // テクスチャのファイル名
				&m_pTextureModel)))	    // テクスチャインターフェースの格納
			{
				MessageBox(NULL, "テクスチャ読み込み失敗", "エラー", MB_OK);  // エラーチェック
			}
		}
	}
}

/*------------------------------------------------------------------------------
　モデルの終了処理
------------------------------------------------------------------------------*/
void CSceneModel::Uninit(void)
{
	// テクスチャインターフェースの開放	
	if (m_pTextureModel != NULL)
	{
		m_pTextureModel->Release();
		m_pTextureModel = NULL;
	}

	// マテリアル情報インターフェースの開放
	if (m_pBuffMatModel != NULL)
	{
		m_pBuffMatModel->Release();
		m_pBuffMatModel = NULL;
	}

	// メッシュ情報インターフェースの開放
	if (m_pMeshModel != NULL)
	{
		m_pMeshModel->Release();
		m_pMeshModel = NULL;
	}
}

/*------------------------------------------------------------------------------
　モデルの更新
------------------------------------------------------------------------------*/
void CSceneModel::Update(void)
{
}

/*----------------------------------------------------------------------------
　モデルの描画
------------------------------------------------------------------------------*/
void CSceneModel::Draw(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// ワールド座標変換行列の作成 //////////////////////////////////////////////
	D3DXMATRIX mtxWorld,  // ワールド座標変換行列格納
		mtxRot,	  // 回転行列格納
		mtxPos;	  // 平行移動行列格納

	// 単位行列で初期化する
	D3DXMatrixIdentity(&mtxWorld);

	// --- 拡大行列の反映 ---

	// --- 回転行列の反映 ---

	// 回転行列作成関数（ Y, X, Zの順で回転する )
	D3DXMatrixRotationYawPitchRoll(&mtxRot,		   // 格納用
		m_rotThe,      // Y軸
		-m_rotFai,	   // X軸
		0.0f		   // Z軸
	);

	// 行列の積算
	D3DXMatrixMultiply(&mtxWorld, // 出力
		&mtxWorld, // 左項
		&mtxRot   // 右項
	);

	// --- 平行移動行列の反映 ---

	// 平行移動行列作成関数
	D3DXMatrixTranslation(&mtxPos,			// 格納用
		m_pos.x,	// X移動量
		m_pos.y,	// Y移動量
		m_pos.z		// Z移動量
	);

	// 行列の積算
	D3DXMatrixMultiply(&mtxWorld, // 出力
		&mtxWorld, // 左項
		&mtxPos    // 右項
	);

	// デバイスに設定
	pDevice->SetTransform(D3DTS_WORLD, // ワールド座標
		&mtxWorld	// 
	);

	// 現在のマテリアル情報の格納
	D3DMATERIAL9 matDef;
	pDevice->GetMaterial(&matDef);

	// マテリアルの取得
	D3DXMATERIAL* pMat; // マテリアル情報のアドレス格納用
	pMat = (D3DXMATERIAL*)m_pBuffMatModel->GetBufferPointer();

	// マテリアルの設定/テクスチャの設定/メッシュの描画
	for (int nCnt = 0; nCnt < (int)m_nNumMatModel; nCnt++)
	{
		// マテリアルの設定
		pDevice->SetMaterial(&pMat[nCnt].MatD3D);

		// テクスチャの設定
		pDevice->SetTexture(0, m_pTextureModel);

		// メッシュの描画
		m_pMeshModel->DrawSubset(nCnt);
	}

	// マテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

/*------------------------------------------------------------------------------
　作成
 ------------------------------------------------------------------------------*/
CSceneModel* CSceneModel::Create(D3DXVECTOR3 pos, float rotThe, float rotFai, char* filePass)
{
	CSceneModel* pSceneModel = new CSceneModel(2);

	pos.y = CModeGame::GetMeshField()->GetHeight(pos);
	pSceneModel->SetPos(D3DXVECTOR3(pos.x, pos.y, pos.z));
	pSceneModel->SetFilePass(filePass);
	pSceneModel->SetRotThe(rotThe);
	pSceneModel->SetRotFai(rotFai);
	pSceneModel->Init();
	return pSceneModel;
}
