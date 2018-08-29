/*==============================================================================

    billboardの処理 [billboard.cpp]
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
#include "textureManager.h"
#include "input.h"
#include "camera.h"
#include "light.h"
#include "billboard.h"
#include "manager.h"

/*------------------------------------------------------------------------------
  　マクロ定義
------------------------------------------------------------------------------*/
// セーフリリースマクロ
#define SAFE_RELEASE( x ) { if( x ) { ( x )->Release(); ( x ) = NULL; } }

#define BILLBOARD_TEXTURENAME "data/TEXTURE/weed001.png"
#define NUM_BILLBOARD (1)	// 数

/*------------------------------------------------------------------------------
  　静的メンバ変数
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
  　コンストラクタ
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
  　デストラクタ
------------------------------------------------------------------------------*/
CBillboard::~CBillboard()
{
}

/*------------------------------------------------------------------------------
  　初期化
------------------------------------------------------------------------------*/
HRESULT CBillboard::Init( void )
{
	// 初期化
	m_tex = D3DXVECTOR2(0.0f, 0.0f);
	m_texSize = D3DXVECTOR2(1.0f, 1.0f);

	// デバイスのポインタ取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// *** 頂点バッファの作成 ***
	if( FAILED( pDevice->CreateVertexBuffer( sizeof( VERTEX_3D ) * NUM_BILLBOARD * 4,			  // 作成したい頂点バッファの合計データサイズ
											 D3DUSAGE_WRITEONLY,						 	  // 頂点バッファの使用方法（書き込みのみ）
											 FVF_VERTEX_3D,								      // ？
											 D3DPOOL_MANAGED,								  // 頂点バッファの置き場となるメモリを指定（デバイスに委託）
											 &m_pVtxBuff,									  // 頂点バッファ管理インターフェースのポインタ（インターフェースの格納）
											 NULL ) ) )										  // 使わない
											 {
												 return E_FAIL;
											 }	

	// *** 頂点バッファの初期化 ***										

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
	
	// 頂点カラーの設定（ 0 ～ 255の整数値 )
	pVtx[ 0 ].color = D3DCOLOR_RGBA( 255, 255, 255, m_alpha );
	pVtx[ 1 ].color = D3DCOLOR_RGBA( 255, 255, 255, m_alpha );
	pVtx[ 2 ].color = D3DCOLOR_RGBA( 255, 255, 255, m_alpha );
	pVtx[ 3 ].color = D3DCOLOR_RGBA( 255, 255, 255, m_alpha );
	
	// 頂点データにUVデータを追加
	pVtx[0].tex = D3DXVECTOR2(m_tex.x, m_tex.y);
	pVtx[1].tex = D3DXVECTOR2(m_tex.x + m_texSize.x, m_tex.y);
	pVtx[2].tex = D3DXVECTOR2(m_tex.x, m_tex.y + m_texSize.y);
	pVtx[3].tex = D3DXVECTOR2(m_tex.x + m_texSize.x, m_tex.y + m_texSize.y);
	
	// 頂点座標
	pVtx[ 0 ].pos  = D3DXVECTOR3( 0.0f - m_size.x * 0.5f, 0.0f + m_size.y, 0.0f );
	pVtx[ 1 ].pos  = D3DXVECTOR3( 0.0f + m_size.x * 0.5f, 0.0f + m_size.y, 0.0f );
	pVtx[ 2 ].pos  = D3DXVECTOR3( 0.0f - m_size.x * 0.5f, 0.0f,			   0.0f );
	pVtx[ 3 ].pos  = D3DXVECTOR3( 0.0f + m_size.x * 0.5f, 0.0f,			   0.0f );

	// 頂点法線の設定
	pVtx[ 0 ].normal  = D3DXVECTOR3( 0.0f, 1.0f, 0.0f ); // コンストラクタによる頂点設定 ( x, y, z )
	pVtx[ 1 ].normal  = D3DXVECTOR3( 0.0f, 1.0f, 0.0f ); // コンストラクタによる頂点設定 ( x, y, z )
	pVtx[ 2 ].normal  = D3DXVECTOR3( 0.0f, 1.0f, 0.0f ); // コンストラクタによる頂点設定 ( x, y, z )
	pVtx[ 3 ].normal  = D3DXVECTOR3( 0.0f, 1.0f, 0.0f ); // コンストラクタによる頂点設定 ( x, y, z )
	
	// 頂点バッファのロックを解除
	( m_pVtxBuff )->Unlock();
			
	// 3D描画の準備
	Set3D();
	
	return S_OK;
}

/*------------------------------------------------------------------------------
  　終了処理
------------------------------------------------------------------------------*/
void CBillboard::Uninit( void )
{
	// 頂点バッファの破棄
	SAFE_RELEASE( m_pVtxBuff );
}

/*------------------------------------------------------------------------------
  　更新
------------------------------------------------------------------------------*/
void CBillboard::Update( void )
{
	VERTEX_3D* pVtx; // VRAMの仮想頂点アドレスを格納

					 // 頂点バッファをロックして、仮想頂点アドレスを取得する
	if (FAILED((m_pVtxBuff)->Lock(0,
		0,				// すべてをロック
		(void**)&pVtx,  // 仮想頂点アドレス用ポインタのアドレスを渡す
		0)))			// ロックフラグ？
	{
		return;
	}

	// 頂点データの設定

	// 頂点座標
	pVtx[0].pos = D3DXVECTOR3(0.0f - m_size.x * 0.5f, 0.0f + m_size.y * 0.5f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f + m_size.x * 0.5f, 0.0f + m_size.y * 0.5f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f - m_size.x * 0.5f, 0.0f - m_size.y * 0.5f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f + m_size.x * 0.5f, 0.0f - m_size.y * 0.5f, 0.0f);

	// 頂点データにUVデータを追加
	pVtx[0].tex = D3DXVECTOR2(m_tex.x, m_tex.y);
	pVtx[1].tex = D3DXVECTOR2(m_tex.x + m_texSize.x, m_tex.y);
	pVtx[2].tex = D3DXVECTOR2(m_tex.x, m_tex.y + m_texSize.y);
	pVtx[3].tex = D3DXVECTOR2(m_tex.x + m_texSize.x, m_tex.y + m_texSize.y);

	// 頂点カラーの設定（ 0 ～ 255の整数値 )
	pVtx[0].color = D3DCOLOR_RGBA(255, 255, 255, m_alpha);
	pVtx[1].color = D3DCOLOR_RGBA(255, 255, 255, m_alpha);
	pVtx[2].color = D3DCOLOR_RGBA(255, 255, 255, m_alpha);
	pVtx[3].color = D3DCOLOR_RGBA(255, 255, 255, m_alpha);

	// 頂点バッファのロックを解除
	(m_pVtxBuff)->Unlock();

	// 3D描画の準備
	Set3D();
}

/*------------------------------------------------------------------------------
  　描画
------------------------------------------------------------------------------*/
void CBillboard::Draw( void )
{	
	// デバイスのポインタ取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// ３Ｄ処理
	Set3D();

	// パイプライン（ストリーム）を設定
	pDevice->SetStreamSource( 0,						// パイプライン番号
							  m_pVtxBuff,				// パイプラインの元になる領域を指定
							  0,						// オフセット（単位はbyte）※ストリームの開始位置を指定できる
							  sizeof( VERTEX_3D ) );	// 流すデータの単位サイズ（ストライド量）

	// テクスチャの設定
	LPDIRECT3DTEXTURE9 temp = CTextureManager::BindTexture(m_TexID);
	pDevice->SetTexture( 0, temp );

	// 頂点フォーマットの設定
	pDevice->SetFVF( FVF_VERTEX_3D );

	for( int nCnt = 0; nCnt < NUM_BILLBOARD; nCnt++ )
	{
		// プリミティブ（ポリゴン）の描画
		pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP,	// プリミティブの種類
								nCnt * 4,				// オフセット
								NUM_BILLBOARD * 2		// プリミティブの数
								);
	}
}

/*------------------------------------------------------------------------------
  　３Ｄ描画準備
------------------------------------------------------------------------------*/
void CBillboard::Set3D( void )
{
	// デバイスのポインタ取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
	
	// --- ワールド座標変換行列の作成 ---
	D3DXMATRIX mtxWorld,	   // ワールド座標変換行列
			   mtxRotY,		   // 回転行列
			   mtxPos,		   // 平行移動行列
			   mtxView,        // ビュー行列
			   mtxViewInverse; // ビューの逆行列
	
	// 単位行列で初期化する
	D3DXMatrixIdentity( &mtxWorld );	
	
	// --- 拡大行列の反映 ---

	// --- 回転行列の反映 ---
	
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

	// --- ビルボード用ワールド行列の作成 ---

	// ビュー行列の取得
	pDevice->GetTransform( D3DTS_VIEW,  // 行列の種類
						   &mtxView		// 出力
						   );

	// 逆行列作成
	D3DXMatrixInverse( &mtxViewInverse, // 出力
					   NULL,
					   &mtxView         // 入力
					   );

	// 逆行列から平行移動成分をカット
	mtxViewInverse._41 = 0.0f;
	mtxViewInverse._42 = 0.0f;	
	mtxViewInverse._43 = 0.0f;

	// 行列の積算
	D3DXMatrixMultiply( &mtxWorld,		 // 出力
						&mtxViewInverse, // 左項
						&mtxWorld        // 右項
						);

	// デバイスに設定
	pDevice->SetTransform( D3DTS_WORLD,		 // ワールド座標
						   &mtxWorld	 // 
						   );				 
}