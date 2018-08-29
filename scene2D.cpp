/*==============================================================================

    scene2Dの処理 [scene2D.cpp]
                                                       作成者 : 中西　祐介
                                                       作成日 : 2016/4/17
--------------------------------------------------------------------------------
    ■Update : 
==============================================================================*/

/*------------------------------------------------------------------------------
  　ヘッダファイル
------------------------------------------------------------------------------*/
#include "manager.h"
#include "scene.h"
#include "scene2D.h"
#include "renderer.h"
#include "main.h"
#include "textureManager.h"
#include <math.h>

/*------------------------------------------------------------------------------
  　マクロ
------------------------------------------------------------------------------*/
#define POLYGON_WIDTH (50)
#define POLYGON_HEIGHT (50)

//=============================================================================
// コンストラクタ
//=============================================================================

//=============================================================================
// デストラクタ
//=============================================================================
CScene2D::~CScene2D()
{
}

//=============================================================================
// 静的メンバ変数
//=============================================================================

//=============================================================================
// 初期化処理
//=============================================================================
void CScene2D::Init( void )
{
	m_pos			  = D3DXVECTOR3( m_pos.x, m_pos.y, m_pos.z );
	m_size			  = D3DXVECTOR3( m_size.x, m_size.y, m_size.z );
	m_leftup          = D3DXVECTOR2( m_pos.x - m_size.x * 0.5f, m_pos.y - m_size.y * 0.5f );
	m_rightup         = D3DXVECTOR2( m_pos.x + m_size.x * 0.5f, m_pos.y - m_size.y * 0.5f );
	m_leftdown        = D3DXVECTOR2( m_pos.x - m_size.x * 0.5f, m_pos.y + m_size.y * 0.5f );
	m_rightdown       = D3DXVECTOR2( m_pos.x + m_size.x * 0.5f, m_pos.y + m_size.y * 0.5f );
	m_tex             = D3DXVECTOR2( 0.0f, 0.0f );
	m_texsize         = D3DXVECTOR2( 1.0f, 1.0f );
	m_color			  = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_color.a);

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// 頂点バッファの作成
	if( FAILED( pDevice->CreateVertexBuffer( sizeof( VERTEX_2D ) * 4,  // 作成したい頂点バッファの合計データサイズ
											 D3DUSAGE_WRITEONLY,				// 頂点バッファの使用方法（書き込みのみ）
											 FVF_VERTEX_2D,						// ？
											 D3DPOOL_MANAGED,					// 頂点バッファの置き場となるメモリを指定（デバイスに委託）
											 &m_pVtxBuff,				// 頂点バッファ管理インターフェースを格納
											 NULL ) ) )							// 使わない
											 {
												 return;
											 }

	//頂点インデックス作成
	pDevice->CreateIndexBuffer(
							   sizeof( DWORD ) * 6,
							   0,
							   D3DFMT_INDEX32,
							   D3DPOOL_MANAGED,
							   &m_pIdxBuff,
							   NULL );

	//頂点のメモリを直でコピーする
	DWORD *vIndex;
	m_pIdxBuff->Lock( 0, 0, ( void** )&vIndex, 0 ); 
	
	// 左回りで三角形を二つ作る（トライアングルリスト）
	vIndex[ 0 ] = 0;  
	vIndex[ 1 ] = 1;
	vIndex[ 2 ] = 2;
	vIndex[ 3 ] = 2;
	vIndex[ 4 ] = 1;
	vIndex[ 5 ] = 3;

	m_pIdxBuff->Unlock();

	// 頂点の設定
	SetVertex();
}

//=============================================================================
// 終了処理
//=============================================================================
void CScene2D::Uninit( void )
{
	// 頂点バッファの破棄
	SAFE_RELEASE( m_pVtxBuff );

	// インデックスバッファの破棄
	SAFE_RELEASE( m_pIdxBuff );
}

//=============================================================================
// 更新処理
//=============================================================================
void CScene2D::Update( void )
{
	// 頂点の設定
	SetVertex();
}

//=============================================================================
// 描画処理
//=============================================================================
void CScene2D::Draw( void )
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
		
	// パイプライン（ストリーム）を設定
	pDevice->SetStreamSource( 0,						// パイプライン番号
							  m_pVtxBuff,				// パイプラインの元になる領域を指定
							  0,						// オフセット（単位はbyte）※ストリームの開始位置を指定できる
							  sizeof( VERTEX_2D ) );	// 流すデータの単位サイズ（ストライド量）インデックスの設定
	// インデックスの設定
	pDevice->SetIndices( m_pIdxBuff );

	// テクスチャの設定（テクスチャのステージへの割当て）
	pDevice->SetTexture( 0,									 // ステージ数 
		CTextureManager::BindTexture( m_TexID ) );			 //テクスチャインターフェース

	// 頂点フォーマットの設定
	pDevice->SetFVF( FVF_VERTEX_2D );

	// プリミティブ（ポリゴン）の描画
	pDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, // プリミティブの種類
								   0,				   // 描画開始位置のオフセット（頂点数）
								   0,				   // 最小インデックス番号
								   6,				   // 最大インデックス番号
								   0,				   // インデックス配列の読み取り位置
								   2 );				   // 描画するプリミティブの数
}

//=============================================================================
// 頂点の設定
//=============================================================================
void CScene2D::SetVertex( void )
{
	// 座標更新
	m_leftup = D3DXVECTOR2(m_pos.x - m_size.x * 0.5f, m_pos.y - m_size.y * 0.5f);
	m_rightup = D3DXVECTOR2(m_pos.x + m_size.x * 0.5f, m_pos.y - m_size.y * 0.5f);
	m_leftdown = D3DXVECTOR2(m_pos.x - m_size.x * 0.5f, m_pos.y + m_size.y * 0.5f);
	m_rightdown = D3DXVECTOR2(m_pos.x + m_size.x * 0.5f, m_pos.y + m_size.y * 0.5f);

	VERTEX_2D* pVtx; // VRAMの仮想アドレスを格納

	// 頂点バッファをロックして、仮想アドレスを取得する
	m_pVtxBuff->Lock( 0,
					  0,			   // すべてをロック
					  ( void** )&pVtx, // 仮想アドレス用ポインタのアドレスを渡す
					  0 );			   // ロックフラグ？
	
	// 頂点座標の設定( 2D座標は右回りに頂点を用意する )
	
	pVtx[ 0 ].pos = D3DXVECTOR3( m_leftup.x,    m_leftup.y,	   0.0f ); // コンストラクタによる頂点設定 ( x, y, z )
	pVtx[ 1 ].pos = D3DXVECTOR3( m_rightup.x,   m_rightup.y,   0.0f ); 
	pVtx[ 2 ].pos = D3DXVECTOR3( m_leftdown.x,  m_leftdown.y,  0.0f );
	pVtx[ 3 ].pos = D3DXVECTOR3( m_rightdown.x, m_rightdown.y, 0.0f ); 

	// rhwの設定（必ず1.0f）※手前か奥（バッファ）の情報？
	pVtx[ 0 ].rhw = 1.0f;
	pVtx[ 1 ].rhw = 1.0f;
	pVtx[ 2 ].rhw = 1.0f;
	pVtx[ 3 ].rhw = 1.0f;

	//// 頂点カラーの設定
	//pVtx[ 0 ].color = D3DXCOLOR( m_color.r, m_color.g, m_color.b, m_color.a );
	//pVtx[ 1 ].color = D3DXCOLOR( m_color.r, m_color.g, m_color.b, m_color.a ); 
	//pVtx[ 2 ].color = D3DXCOLOR( m_color.r, m_color.g, m_color.b, m_color.a );
	//pVtx[ 3 ].color = D3DXCOLOR( m_color.r, m_color.g, m_color.b, m_color.a );

	pVtx[ 0 ].color = m_color;
	pVtx[ 1 ].color = m_color; 
	pVtx[ 2 ].color = m_color;
	pVtx[ 3 ].color = m_color;

	// 頂点データにUVデータを追加
	pVtx[ 0 ].tex = D3DXVECTOR2( m_tex.x,			    m_tex.y );
	pVtx[ 1 ].tex = D3DXVECTOR2( m_tex.x + m_texsize.x, m_tex.y );
	pVtx[ 2 ].tex = D3DXVECTOR2( m_tex.x,				m_tex.y + m_texsize.y );
	pVtx[ 3 ].tex = D3DXVECTOR2( m_tex.x + m_texsize.x, m_tex.y + m_texsize.y );
	
	// 頂点バッファのロックを解除
	m_pVtxBuff->Unlock();
}
