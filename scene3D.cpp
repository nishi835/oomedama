/*==============================================================================

    scene3Dの処理 [scene2D.cpp]
                                                       作成者 : 中西　祐介
                                                       作成日 : 2016/4/17
--------------------------------------------------------------------------------
    ■Update : 
==============================================================================*/

/*------------------------------------------------------------------------------
  　ヘッダファイル
------------------------------------------------------------------------------*/
#include "main.h"
#include "renderer.h"
#include "scene3D.h"

#define SHADOW_TEXTURENAME "data/TEXTURE/gang02.png"

//=============================================================================
// コンストラクタ
//=============================================================================
CScene3D::CScene3D()
{
	m_pVtxBuff = NULL;
	m_pTexture = NULL;
}

//=============================================================================
// デストラクタ
//=============================================================================
CScene3D::~CScene3D()
{
}

//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
void CScene3D::Init( void )
{		
	// デバイスのポインタ取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// *** 頂点バッファの作成 ***
	if( FAILED( pDevice->CreateVertexBuffer( sizeof( VERTEX_3D ) * 4,			  // 作成したい頂点バッファの合計データサイズ
											 D3DUSAGE_WRITEONLY,						 	  // 頂点バッファの使用方法（書き込みのみ）
											 FVF_VERTEX_3D,								      // ？
											 D3DPOOL_MANAGED,								  // 頂点バッファの置き場となるメモリを指定（デバイスに委託）
											 &m_pVtxBuff,									  // 頂点バッファ管理インターフェースのポインタ（インターフェースの格納）
											 NULL ) ) )										  // 使わない
											 {
												 return;
											 }	

	// *** 頂点バッファの初期化 ***										

	VERTEX_3D* pVtx; // VRAMの仮想頂点アドレスを格納

	// 頂点バッファをロックして、仮想頂点アドレスを取得する
	if( FAILED ( (m_pVtxBuff)->Lock( 0,
									0,				// すべてをロック
									( void** )&pVtx,  // 仮想頂点アドレス用ポインタのアドレスを渡す
									0 ) ) )			// ロックフラグ？
									{	
									 return;
									}		
	// 頂点データの設定

	// 頂点カラーの設定（ 0 ～ 255の整数値 )
	pVtx[ 0 ].color = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	pVtx[ 1 ].color = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	pVtx[ 2 ].color = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	pVtx[ 3 ].color = D3DCOLOR_RGBA( 255, 255, 255, 255 );
		
	// 頂点データにUVデータを追加
	pVtx[ 0 ].tex = D3DXVECTOR2( 0.0f, 0.0f );
	pVtx[ 1 ].tex = D3DXVECTOR2( 1.0f, 0.0f );
	pVtx[ 2 ].tex = D3DXVECTOR2( 0.0f, 1.0f );
	pVtx[ 3 ].tex = D3DXVECTOR2( 1.0f, 1.0f );
		
	// 頂点座標
	pVtx[ 0 ].pos = D3DXVECTOR3( 0.0f - m_size.x * 0.5f, 0.0f,  m_size.y * 0.5f );
	pVtx[ 1 ].pos = D3DXVECTOR3( 0.0f + m_size.x * 0.5f, 0.0f,  m_size.y * 0.5f );
	pVtx[ 2 ].pos = D3DXVECTOR3( 0.0f - m_size.x * 0.5f, 0.0f, -m_size.y * 0.5f );
	pVtx[ 3 ].pos = D3DXVECTOR3( 0.0f + m_size.x * 0.5f, 0.0f, -m_size.y * 0.5f );

	// 頂点法線の設定
	pVtx[ 0 ].normal = D3DXVECTOR3( 0.0f, 0.0f, -1.0f ); // コンストラクタによる頂点設定 ( x, y, z )
	pVtx[ 1 ].normal = D3DXVECTOR3( 0.0f, 0.0f, -1.0f ); // コンストラクタによる頂点設定 ( x, y, z )
	pVtx[ 2 ].normal = D3DXVECTOR3( 0.0f, 0.0f, -1.0f ); // コンストラクタによる頂点設定 ( x, y, z )
	pVtx[ 3 ].normal = D3DXVECTOR3( 0.0f, 0.0f, -1.0f ); // コンストラクタによる頂点設定 ( x, y, z )
		
	// 頂点バッファのロックを解除
	( m_pVtxBuff )->Unlock();
		
	// テクスチャの読み込み
	if( FAILED ( D3DXCreateTextureFromFile( pDevice, SHADOW_TEXTURENAME, &m_pTexture ) ) )
	{
		MessageBox( NULL, "読み込み失敗", "エラー", MB_OK ); 
	}
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CScene3D::Uninit( void )
{
	// 頂点バッファの破棄
	SAFE_RELEASE( m_pVtxBuff );
	
	// インデックスバッファの破棄
	SAFE_RELEASE( m_pIdxBuff );
	
	// テクスチャの破棄
	if( m_pTexture != NULL )
	{
		SAFE_RELEASE( m_pTexture );
	}
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CScene3D::Update( void )
{
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CScene3D::Draw( void )
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// パイプライン（ストリーム）を設定
	pDevice->SetStreamSource( 0,						// パイプライン番号
							  m_pVtxBuff,				// パイプラインの元になる領域を指定
							  0,						// オフセット（単位はbyte）※ストリームの開始位置を指定できる
							  sizeof( VERTEX_3D ) );	// 流すデータの単位サイズ（ストライド量）

	// テクスチャの設定
	pDevice->SetTexture( 0, m_pTexture );

	// 頂点フォーマットの設定
	pDevice->SetFVF( FVF_VERTEX_3D );

	// 3D処理
	Set3D();

	// プリミティブ（ポリゴン）の描画
	pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP,	// プリミティブの種類
							0,						// オフセット
							2						// プリミティブの数
							);
	
}

/*------------------------------------------------------------------------------
  　３Ｄ描画準備
------------------------------------------------------------------------------*/
void CScene3D::Set3D( void )
{
	// デバイスのポインタ取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// --- ワールド座標変換行列の作成 ---
	D3DXMATRIX mtxWorld,
			   mtxPos,
			   mtxRotY;	 // ワールド座標変換行列

	// 単位行列で初期化する
	D3DXMatrixIdentity( &mtxWorld );

	// --- 平行移動行列の反映 ---

	// 平行移動行列作成関数
	D3DXMatrixTranslation( &mtxPos,	// 格納用
						   m_pos.x,	// X移動量
						   m_pos.y,	// Y移動量
						   m_pos.z	// Z移動量
  						   );		
	
	// 行列の積算
	D3DXMatrixMultiply( &mtxWorld, // 出力
						&mtxWorld, // 左項
						&mtxPos    // 右項
						);

	// デバイスに設定
	pDevice->SetTransform( D3DTS_WORLD, // ワールド座標
						   &mtxWorld	// 
						   );
}

//=============================================================================
// オブジェクトの作成
//=============================================================================
CScene3D* CScene3D::Create( void )
{
	CScene3D* scene3D;
	scene3D = new CScene3D();
	scene3D->Init();

	return scene3D;
}