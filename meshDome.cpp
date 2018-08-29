/*==============================================================================

    メッシュスフィアの処理 [meshDome.cpp]
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
#include "meshDome.h"
#include "textureManager.h"
#include "input.h"
#include "camera.h"
#include "light.h"

/*------------------------------------------------------------------------------
  　マクロ定義
------------------------------------------------------------------------------*/
// セーフリリースマクロ
#define SAFE_RELEASE( x ) { if( x ) { ( x )->Release(); ( x ) = NULL; } }

#define SPHERE_TEXTURENAME "data/TEXTURE/skydome002.jpg"
#define NUM_VERTEX_WALL (28)	// 頂点数
#define NUM_INDEX_WALL (36)	// 頂点インデックス数

#define DELTA_U (0.001f) // UVのUの変化量

/*-----------------------------------------------------------t-------------------
  　グローバル変数
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
  　初期化
------------------------------------------------------------------------------*/
HRESULT CMeshDome::Init(void)
{
	// テクスチャの読み込み
	m_texID = CTextureManager::LoadTexture(SPHERE_TEXTURENAME, CTextureManager::TEXTYPE_NONE);

	// パラメータ設定
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_UV = D3DXVECTOR2(0.0f, 0.0f);
	m_numColumn    = 8;
	m_numRow	   = 8;
	m_radius	   = 200.0f;
	m_center       = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	m_numVertex    = ( m_numRow + 1 ) * ( m_numColumn + 1 );
	m_numIndex	   = ( 2 + m_numRow * 2 ) * m_numColumn + ( m_numColumn - 1 ) * 2;
	m_numPolygon   =  m_numIndex - 2;

	// デバイスのポインタ取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// *** 頂点バッファの作成 ***
	if( FAILED( pDevice->CreateVertexBuffer( sizeof( VERTEX_3D ) * m_numVertex * 1,	  // 作成したい頂点バッファの合計データサイズ
											 D3DUSAGE_WRITEONLY,						 	  // 頂点バッファの使用方法（書き込みのみ）
											 FVF_VERTEX_2D,								      // ？
											 D3DPOOL_MANAGED,								  // 頂点バッファの置き場となるメモリを指定（デバイスに委託）
											 &m_pVtxBuff,									  // 頂点バッファ管理インターフェースのポインタ（インターフェースの格納）
											 NULL ) ) )										  // 使わない
											 {
												 return E_FAIL;
											 }	

	// *** インデックスバッファの作成 *** 
	if( FAILED( pDevice->CreateIndexBuffer( sizeof( WORD ) * m_numIndex,	// データサイズ
											D3DUSAGE_WRITEONLY,					// 使用用途フラグ
											D3DFMT_INDEX16,						// インデックスデータのフォーマット ※頂点座標2byte以下の場合16、以上の場合32
											D3DPOOL_MANAGED,					// メモリ管理の方法
											&m_pIdxBuff,					// インデックスバッファインターフェースのポインタ
											NULL ) ) )							// 使わない
											{
												return E_FAIL;
											}			
		
	// --- 頂点バッファの初期化 --- //////////////////////////////////////////////										

	VERTEX_3D* pVtx; // VRAMの仮想頂点アドレスを格納

	// 頂点バッファをロックして、仮想頂点アドレスを取得する
	if( FAILED ( ( m_pVtxBuff )->Lock( 0,
										     0,				// すべてをロック
										     ( void** )&pVtx,  // 仮想頂点アドレス用ポインタのアドレスを渡す
										     0 ) ) )			// ロックフラグ？
										     {	
										  	    return E_FAIL;
										     }		

	// 頂点データの設定
	float fRotV    = 0.0f;							 // 中心に対する垂直平面上の角度
	float fRotDifV = D3DX_PI * 0.6f	/ m_numColumn;   // 垂直平面上の角度の変化量
	float fRotDifH = D3DX_PI * 2.0f / m_numRow;      // 水平平面上の角度の変化量

	for( int nCntY = 0; nCntY < m_numColumn + 1; nCntY++ )
	{
		// 垂直平面上の角度の更新
		fRotV = fRotDifV * nCntY;

		float fRotH = D3DX_PI * 0.5f; // 中心に対する水平平面上の角度
		
		for( int nCntX = 0; nCntX < m_numRow + 1; nCntX++ )
		{
			// 水平平面上の角度の更新
			fRotH = fRotDifH * nCntX;

			// 頂点カラーの設定（ 0 ～ 255の整数値 )
			pVtx[ 0 ].color = D3DCOLOR_RGBA( 255, 255, 255, 255 );
		
			// 頂点データにUVデータを追加
			pVtx[ 0 ].tex = D3DXVECTOR2((float)nCntX, (float)nCntY);
		
			// 頂点座標
			pVtx[ 0 ].pos = D3DXVECTOR3(m_center.x - sinf( fRotV ) * cosf( fRotH ) * m_radius,
										m_center.y + cosf( fRotV )				   * m_radius, 
										m_center.z + sinf( fRotV ) * sinf( fRotH ) * m_radius ); 

			// 頂点法線の設定
			pVtx[ 0 ].normal  = D3DXVECTOR3( 0.0f, 0.0f, -1.0f ); // コンストラクタによる頂点設定 ( x, y, z )
			
			pVtx += 1;	
		}
	}
	
	// 頂点バッファのロックを解除
	( m_pVtxBuff )->Unlock();

	// インデックスバッファの作成
	WORD* pIdx;
	
	// インデックスバッファをロックして、仮想頂点アドレスを取得する
	if( FAILED ( ( m_pIdxBuff )->Lock( 0,
									         0,				   // すべてをロック
									         ( void** )&pIdx,  // 仮想頂点アドレス用ポインタのアドレスを渡す
									         0 ) ) )		   // ロックフラグ？
									         {	
									           return E_FAIL;
									         }		

	// 頂点インデックスの設定
	for( int nCntY = 0; nCntY < m_numColumn; nCntY++ )
	{
		for( int nCntX = 0; nCntX < m_numRow + 1; nCntX++ )
		{
			// 縮退ポリゴン用頂点設定(1)
			if( nCntY != 0 && nCntX == 0 )
			{
				pIdx[ 0 ] = ( m_numRow + 1 ) * ( nCntY + 1 ); 	
					
				pIdx++;
			}

			// 頂点設定
			pIdx[ 0 ] = ( m_numRow + 1 ) * ( nCntY + 1 ) + nCntX; 
			pIdx[ 1 ] = ( m_numRow + 1 ) * nCntY + nCntX;	

			pIdx += 2;
		}

		// 縮退ポリゴン用頂点設定(2)
		if( nCntY != m_numColumn - 1 )
		{
			// 頂点座標
			pIdx[ 0 ] = ( pIdx - 2 )[ 1 ];
			pIdx++;
		}
	}
	
	// インデックスバッファのロックを解除
	( m_pIdxBuff )->Unlock();

	// 3D描画の準備
	Set3D();
	
	return S_OK;
}

/*------------------------------------------------------------------------------
  　終了処理
------------------------------------------------------------------------------*/
void CMeshDome::Uninit( void )
{
	// 終了処理
	if( m_pIdxBuff != NULL )
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

/*------------------------------------------------------------------------------
  　更新
------------------------------------------------------------------------------*/
void CMeshDome::Update(void)
{
	// UVの更新
	m_UV.x += DELTA_U;

	VERTEX_3D* pVtx; // VRAMの仮想頂点アドレスを格納

	// 頂点バッファをロックして、仮想頂点アドレスを取得する
	if (FAILED((m_pVtxBuff)->Lock(0,
		0,				// すべてをロック
		(void**)&pVtx,  // 仮想頂点アドレス用ポインタのアドレスを渡す
		0)))			// ロックフラグ？
	{
		return;
	}

	for (int nCntY = 0; nCntY < m_numColumn; nCntY++)
	{
		for (int nCntX = 0; nCntX < m_numRow + 1; nCntX++)
		{
			// 頂点データにUVデータを追加
			pVtx[0].tex = D3DXVECTOR2(m_UV.x + (float)nCntX / (float) m_numRow, (float)nCntY / (float)m_numColumn);

			pVtx += 1;
		}
	}

	// 頂点バッファのロックを解除
	(m_pVtxBuff)->Unlock();
}

/*------------------------------------------------------------------------------
  　描画処理
------------------------------------------------------------------------------*/
void CMeshDome::Draw( void )
{
	// 3D描画設定
	Set3D();

	// デバイスのポインタ取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// ライトのスイッチ
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// パイプライン（ストリーム）を設定
	pDevice->SetStreamSource( 0,						// パイプライン番号
							  m_pVtxBuff,				// パイプラインの元になる領域を指定
							  0,						// オフセット（単位はbyte）※ストリームの開始位置を指定できる
							  sizeof( VERTEX_3D ) );	// 流すデータの単位サイズ（ストライド量）

	// インデックスバッファの設定
	pDevice->SetIndices( m_pIdxBuff );
	
	// テクスチャの設定
	HRESULT hr = pDevice->SetTexture( 0, CTextureManager::BindTexture(m_texID));

	// 頂点フォーマットの設定
	pDevice->SetFVF( FVF_VERTEX_3D );

	// プリミティブ（ポリゴン）の描画
	pDevice->DrawIndexedPrimitive( D3DPT_TRIANGLESTRIP,		// プリミティブの種類
								   0,								// 最小のインデックスまでのオフセット
								   0,								// 最小の頂点インデックス
								   m_numVertex,				// 頂点数
								   0,								// スタートインデックス（読み始めの場所？)
								   m_numPolygon				// プリミティブの数
								   );

	// ライトのスイッチ
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

/*------------------------------------------------------------------------------
　作成
 ------------------------------------------------------------------------------*/
CMeshDome* CMeshDome::Create(void)
{
	CMeshDome* pDome = new CMeshDome(CScene::PRIORITY_3D);
	pDome->Init();
	return pDome;
}

/*------------------------------------------------------------------------------
  　３Ｄ描画準備
------------------------------------------------------------------------------*/
void CMeshDome::Set3D( void )
{
	// デバイスのポインタ取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// --- ワールド座標変換行列の作成 ---
	D3DXMATRIX mtxWorld,
			   mtxRotY,
			   mtxPos;	// ワールド座標変換行列

	// 単位行列で初期化する
	D3DXMatrixIdentity( &mtxWorld );

	// --- 回転行列 ---

	// 回転行列の作成
	 float fRadian = 0.0f;

	D3DXMatrixRotationYawPitchRoll( &mtxRotY,				  		   // 格納用
									fRadian, /*D3DXToRadian( 45 ),*/ // Y軸
									0.0f,						   	   // X軸
									0.0f							   // Y軸
									);

	// 行列の積算
	D3DXMatrixMultiply( &mtxWorld, // 出力
						&mtxWorld, // 左項
						&mtxRotY   // 右項
						);

	// --- 平行移動行列 ---

	// 平行移動行列作成関数
	D3DXMatrixTranslation(&mtxPos,	// 格納用
		0.0f,	// X移動量
		0.0f,	// Y移動量
		0.0f	// Z移動量
	);

	// 行列の積算
	D3DXMatrixMultiply(&mtxWorld, // 出力
		&mtxWorld, // 左項
		&mtxPos    // 右項
	);

	// デバイスに設定
	pDevice->SetTransform( D3DTS_WORLD, // ワールド座標
								&mtxWorld	 // 
							    );				 
}

































