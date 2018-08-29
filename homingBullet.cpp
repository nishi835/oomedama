/*==============================================================================

homingBulletの処理 [homingBullet.cpp]
作成者 : 中西　祐介
作成日 :
--------------------------------------------------------------------------------
■Update :
==============================================================================*/

/*------------------------------------------------------------------------------
　ヘッダファイル
 ------------------------------------------------------------------------------*/
#include "main.h"
#include "renderer.h"
#include "sceneModel.h"
#include "homingBullet.h"

/*------------------------------------------------------------------------------
 　マクロ定義
------------------------------------------------------------------------------*/
#define WHITE_TEXTURE_NAME  "data/TEXTURE/white.jpg"

/*------------------------------------------------------------------------------
  　デストラクタ
------------------------------------------------------------------------------*/
CHomingBullet::~CHomingBullet()
{
}

/*------------------------------------------------------------------------------
　初期化
------------------------------------------------------------------------------*/
void CHomingBullet::Init(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// モデルのロード
	HRESULT hr;

	hr = (D3DXLoadMeshFromX(m_FilePass,		// モデルのファイル名
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

	// オブジェクトタイプの設定
	SetObjType(OBJTYPE_NONE);
}

/*------------------------------------------------------------------------------
　終了処理
------------------------------------------------------------------------------*/
void CHomingBullet::Uninit(void)
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

	CScene::SetDelete();
}

/*------------------------------------------------------------------------------
　更新
------------------------------------------------------------------------------*/
void CHomingBullet::Update(void)
{
	if (!m_use) return;

	// 移動
	m_pos += m_velocity;

	// 進行方向ベクトルの設定 /////////////////////////////////////////

	// 外積で、回転軸を求める
	D3DXVECTOR3 vecOrg = m_velocity;
	D3DXVec3Normalize(&vecOrg, &vecOrg);

	D3DXVECTOR3 vecTarget = m_targetPos - m_pos;
	D3DXVec3Normalize(&vecTarget, &vecTarget);

	D3DXVECTOR3 vecAxis;
	D3DXVec3Cross(&vecAxis, &vecOrg, &vecTarget);

	// 内積で90度以上、未満を切り分け
	float temp = D3DXVec3Dot(&vecOrg, &vecTarget);

	float rot;
	if (temp > 0)
	{
		rot = asin(D3DXVec3Length(&vecAxis));
	}
	// 90度以上なら、角度を調節
	else
	{
		rot = D3DX_PI - asin(D3DXVec3Length(&vecAxis));
	}

	// 段階的に角度を変える
	rot *= (0.1f);

	// 回転軸と角度からクォータニオンを求める
	D3DXQUATERNION quaternion;
	D3DXQuaternionRotationAxis(&quaternion, &vecAxis, rot);

	// クォータニオンから回転行列を求める
	D3DXMatrixRotationQuaternion(&m_mtxRot, &quaternion);

	// ベクトルを行列で回転
	D3DXVec3TransformCoord(&vecOrg, &vecOrg, &m_mtxRot);

	m_velocity = vecOrg * HOMINGBULLET_SPEED;
	m_deltaRot += 0.006f;

	// モデルの向きの回転軸、角度の算出 /////////////////////////////////////

	// 軸の算出
	D3DXVECTOR3 vecTemp = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	D3DXVec3Cross(&m_axis, &vecTemp, &vecOrg);

	// 角度の算出

	// 内積で90度以上、未満を切り分け
	temp = D3DXVec3Dot(&vecOrg, &vecTarget);

	if (temp > 0)
	{
		m_rocalRot = asinf(D3DXVec3Length(&m_axis));
	}
	// 90度以上なら、角度を調節
	else
	{
		m_rocalRot = D3DX_PI - asinf(D3DXVec3Length(&m_axis));
	}
}

/*------------------------------------------------------------------------------
　描画処理
------------------------------------------------------------------------------*/
void CHomingBullet::Draw(void)
{
	if (!m_use) return;

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

	// 回転行列作成関数
	D3DXMatrixRotationAxis(&mtxRot,		   // 格納用
		&m_axis,
		m_rocalRot
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
CHomingBullet* CHomingBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 velocity, float rotThe, float rotFai, bool use, char* filePass)
{
	CHomingBullet* pHomingBullet = new CHomingBullet(CScene::PRIORITY_3D);

	// 初期化
	pHomingBullet->SetPos(pos);
	pHomingBullet->SetVelocity(velocity);
	pHomingBullet->SetDeltaRot(0.0f);
	pHomingBullet->SetRocalRot(0.0f);
	pHomingBullet->SetUse(use);

	// テクスチャIDの設定
	pHomingBullet->SetFilePass(filePass);
	pHomingBullet->Init();

	return pHomingBullet;
}

