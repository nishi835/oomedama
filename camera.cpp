/*==============================================================================

    cameraの処理 [camera.cpp]
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
#include "camera.h"
#include "input.h"

#define CAMERA_ROTATION_RADIUS ( 0.01f ) // カメラの回転半径
#define CAMERA_MOVE_COEFFICIENT (0.1f)  // 移動係数

//=============================================================================
// コンストラクタ
//=============================================================================
CCamera::CCamera()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CCamera::~CCamera()
{
}

//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
void CCamera::Init( void )
{
	// デバイスのポインタ取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// カメラの初期化
	m_posEye = D3DXVECTOR3( 0.0f, 10.0f, -30.0f );
	m_posAt  = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	m_posEyeTarget = D3DXVECTOR3(0.0f, 10.0f, -30.0f);
	m_posAtTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotXZ  = 0.0f;
	m_rotXY = 0.0f;
	m_vecUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_distance = 10.0f;

	// 真横ベクトルの初期化
	D3DXVECTOR3 temp = m_posAt - m_posEye;
	D3DXVec3Cross(&m_flatLine, &temp, &m_vecUp);
	D3DXVec3Normalize(&m_flatLine, &m_flatLine);

	// --- ビュー変換行列の作成 ---
	D3DXMATRIX  mtxView;									  // ビュー座標変換行列
	D3DXVECTOR3 posEye( m_posEye.x, m_posEye.y, m_posEye.z ); // カメラの座標
	D3DXVECTOR3 posAt( 0.0f, 0.0f, 0.0f );					  // カメラの注視点
	D3DXVECTOR3 vecUp( 0.0f, 1.0f, 0.0f );					  // カメラの上情報
	
	// ビュー行列の作成
	D3DXMatrixLookAtLH( &mtxView,					 // 行列の格納
						&posEye, &posAt, &vecUp
						);	 // 必要な情報

	// デバイスに設定
	pDevice->SetTransform( D3DTS_VIEW,
						   &mtxView
						  );

	// --- プロジェクション変換行列の作成 ---
	D3DXMATRIX mtxProj; // プロジェクション変換行列を格納
	
	//
	D3DXMatrixPerspectiveFovLH( &mtxProj,								// 行列の格納
								D3DX_PI / 3.0f,							// 画角（視野角）
								( float )SCREEN_WIDTH / SCREEN_HEIGHT,  // アスペクト比
								1.0f,									// near（0.0f < near ※0.0fはダメ）
								10000.0f									// far
							    );
	
	// デバイスに設定
	pDevice->SetTransform( D3DTS_PROJECTION,
						   &mtxProj
						  );
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CCamera::Uninit( void )
{
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CCamera::Update(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
	CInputKeyboard* pInputKeyboard = CManager::GetInputKeyboard();

	// パラメータ更新
	
	// --- カメラの回転 ---

	if (pInputKeyboard->GetKeyPress(DIK_1))
	{
		m_rotXY += CAMERA_ROTATION_RADIUS;
	}

	if (pInputKeyboard->GetKeyPress(DIK_2))
	{
		m_rotXY -= CAMERA_ROTATION_RADIUS;
	}

	if (pInputKeyboard->GetKeyPress(DIK_3))
	{
		m_rotXZ += CAMERA_ROTATION_RADIUS;
	}

	if (pInputKeyboard->GetKeyPress(DIK_4))
	{
		m_rotXZ -= CAMERA_ROTATION_RADIUS;
	}

	if (pInputKeyboard->GetKeyPress(DIK_Z))
	{
	}

	if (pInputKeyboard->GetKeyPress(DIK_O))
	{
	}

	// カメラの移動
	
	D3DXMATRIX	mtxRot;  // 回転行列格納

	// --- カメラの回転 ---

	// 回転行列作成関数
	//D3DXMatrixRotationAxis(&mtxRot,		   // 格納用

	//	m_rotXY     // Y軸
	//);

//	D3DXVec3TransformCoord(&m_posEye, &m_posEye, &mtxRot); // 回転行列から座標を取得

	// --- 注視点の回転 ---

	// --- カメラの平行移動 ---

	// --- ビュー変換行列の作成 ---

	D3DXMATRIX mtxView;						 // ビュー座標変換行列

	// ビュー行列の作成
	D3DXMatrixLookAtLH( &mtxView,					 // 行列の格納
						&m_posEye,			 // カメラの座標
						&m_posAt,				 // カメラの注視点
						&m_vecUp						 // カメラの上情報
						);	 

	// デバイスに設定
	pDevice->SetTransform( D3DTS_VIEW,
								&mtxView
							  );

	// --- プロジェクション変換行列の作成 ---
	D3DXMATRIX mtxProj; // プロジェクション変換行列を格納
	
	//
	D3DXMatrixPerspectiveFovLH( &mtxProj,								// 行列の格納
								D3DX_PI / 3.0f,							// 画角（視野角）
								( float )SCREEN_WIDTH / SCREEN_HEIGHT,  // アスペクト比
								1.0f,									// near（0.0f < near ※0.0fはダメ）
								10000.0f									// far
							  );
	
	// デバイスに設定
	pDevice->SetTransform( D3DTS_PROJECTION,
								&mtxProj
							  );	

}

//=============================================================================
// 作成
//=============================================================================
CCamera* CCamera::Create(void)
{
	CCamera* pCamera = new CCamera();
	pCamera->Init();

	return pCamera;
}