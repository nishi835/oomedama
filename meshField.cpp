/*==============================================================================

    meshFieldの処理 [meshField.cpp]
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
#include "meshField.h"
#include "camera.h"
#include "light.h"

/*------------------------------------------------------------------------------
  　マクロ定義
------------------------------------------------------------------------------*/
// セーフリリースマクロ
#define SAFE_RELEASE( x ) { if( x ) { ( x )->Release(); ( x ) = NULL; } }

#define POLYGON_TEXTURENAME "data/TEXTURE/desert.jpg"
#define NUM_VERTEX_FIELD (36)

float g_FieldHeight[ 31 ][ 31 ] =
{
	{ 5.0f, 3.0f, 5.0f, 3.0f, 3.0f, 5.0f, 3.0f, 5.0f, 3.0f, 3.0f, 3.0f, 5.0f, 3.0f, 5.0f, 3.0f, 3.0f, 5.0f, 3.0f, 5.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 5.0f, 3.0f, 5.0f, 3.0f, 3.0f, 3.0f, 5.0f },
	{ 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 5.0f, 4.0f, 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 4.0f },
	{ 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 4.0f, 3.0f, 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 3.0f },
	{ 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 3.0f, 2.0f, 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 2.0f },
	{ 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 3.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 3.0f, 2.0f, 3.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 3.0f, 2.0f },
	{ 5.0f, 3.0f, 5.0f, 3.0f, 3.0f, 5.0f, 3.0f, 5.0f, 3.0f, 3.0f, 3.0f, 5.0f, 3.0f, 5.0f, 3.0f, 3.0f, 5.0f, 3.0f, 5.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 5.0f, 3.0f, 5.0f, 3.0f, 3.0f, 3.0f, 5.0f },
	{ 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 5.0f, 4.0f, 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 4.0f },
	{ 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 4.0f, 3.0f, 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 3.0f },
	{ 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 3.0f, 2.0f, 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 2.0f },
	{ 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 3.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 3.0f, 2.0f, 3.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 3.0f, 2.0f },
	{ 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 5.0f, 4.0f, 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 4.0f },
	{ 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 4.0f, 3.0f, 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 3.0f },
	{ 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 3.0f, 2.0f, 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 2.0f },
	{ 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 3.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 3.0f, 2.0f, 3.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 3.0f, 2.0f },
	{ 5.0f, 3.0f, 5.0f, 3.0f, 3.0f, 5.0f, 3.0f, 5.0f, 3.0f, 3.0f, 3.0f, 5.0f, 3.0f, 5.0f, 3.0f, 3.0f, 5.0f, 3.0f, 5.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 5.0f, 3.0f, 5.0f, 3.0f, 3.0f, 3.0f, 5.0f },
	{ 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 5.0f, 4.0f, 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 4.0f },
	{ 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 4.0f, 3.0f, 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 3.0f },
	{ 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 3.0f, 2.0f, 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 2.0f },
	{ 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 3.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 3.0f, 2.0f, 3.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 3.0f, 2.0f },
	{ 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 5.0f, 4.0f, 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 4.0f },
	{ 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 4.0f, 3.0f, 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 3.0f },
	{ 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 3.0f, 2.0f, 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 2.0f },
	{ 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 3.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 3.0f, 2.0f, 3.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 3.0f, 2.0f },
	{ 5.0f, 3.0f, 5.0f, 3.0f, 3.0f, 5.0f, 3.0f, 5.0f, 3.0f, 3.0f, 3.0f, 5.0f, 3.0f, 5.0f, 3.0f, 3.0f, 5.0f, 3.0f, 5.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 5.0f, 3.0f, 5.0f, 3.0f, 3.0f, 3.0f, 5.0f },
	{ 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 5.0f, 4.0f, 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 4.0f },
	{ 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 4.0f, 3.0f, 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 3.0f },
	{ 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 3.0f, 2.0f, 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 2.0f },
	{ 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 3.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 3.0f, 2.0f, 3.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 3.0f, 2.0f }
};

/*------------------------------------------------------------------------------
  　デストラクタ
------------------------------------------------------------------------------*/
CMeshField::~CMeshField()
{
}

/*------------------------------------------------------------------------------
  　初期化
------------------------------------------------------------------------------*/
void CMeshField::Init( void )
{
	// フィールドのパラメータ設定
	m_NumRow = FIELD_NUM_ROW;
	m_NumColumn = FIELD_NUM_COLUMN;
	m_SellHeight = FIELD_SELL_WIDTH;
	m_SellWidth = FIELD_SELL_HEIGHT;
	m_Center.x = 0.0f;
	m_Center.z = 0.0f;
	m_NumVertex = ( m_NumColumn + 1 ) * ( m_NumRow + 1 );
	m_NumIndex = ( m_NumColumn + 1 ) * ( m_NumRow + 1 ) + ( m_NumRow - 1 ) * ( m_NumColumn + 1 ) + ( m_NumRow - 1 ) * 2;
	m_NumPolygon =  m_NumIndex - 2;

	// フィールドの高さ読み込み
	Load();

	// デバイスのポインタ取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// *** 頂点バッファの作成 ***
	if( FAILED( pDevice->CreateVertexBuffer( sizeof( VERTEX_3D ) * m_NumVertex * 1,	  // 作成したい頂点バッファの合計データサイズ
											 D3DUSAGE_WRITEONLY,						 	  // 頂点バッファの使用方法（書き込みのみ）
											 FVF_VERTEX_2D,								      // ？
											 D3DPOOL_MANAGED,								  // 頂点バッファの置き場となるメモリを指定（デバイスに委託）
											 &m_pVtxBuffer,									  // 頂点バッファ管理インターフェースのポインタ（インターフェースの格納）
											 NULL ) ) )										  // 使わない
											 {
												 return;
											 }	

	// *** インデックスバッファの作成 *** 
	if( FAILED( pDevice->CreateIndexBuffer( sizeof( WORD ) * m_NumIndex,	// データサイズ
											D3DUSAGE_WRITEONLY,					// 使用用途フラグ
											D3DFMT_INDEX16,						// インデックスデータのフォーマット ※頂点座標2byte以下の場合16、以上の場合32
											D3DPOOL_MANAGED,					// メモリ管理の方法
											&m_pIdxBuffer,					// インデックスバッファインターフェースのポインタ
											NULL ) ) )							// 使わない
											{
												return;
											}			
		
	// *** 頂点バッファの初期化 ***										

	VERTEX_3D* pVtx;  // VRAMの仮想頂点アドレスを格納

	// 頂点バッファをロックして、仮想頂点アドレスを取得する
	if( FAILED ( ( m_pVtxBuffer )->Lock( 0,
									   0,				// すべてをロック
								       ( void** )&pVtx,  // 仮想頂点アドレス用ポインタのアドレスを渡す
									   0 ) ) )			// ロックフラグ？
								       {	
									 	  return;
									   }		

	// 頂点データの設定
	for( int nCntZ = 0; nCntZ < m_NumRow + 1; nCntZ++ )
	{
		for( int nCntX = 0; nCntX < m_NumColumn + 1; nCntX++ )
		{
			// 頂点カラーの設定（ 0 ～ 255の整数値 )
			pVtx[ 0 ].color = D3DCOLOR_RGBA( 255, 255, 0, 255 );
		
			// 頂点データにUVデータを追加
			pVtx[ 0 ].tex = D3DXVECTOR2( ( float )nCntX, ( float )nCntZ );
		
			// 頂点座標
			pVtx[ 0 ].pos  = D3DXVECTOR3( m_Center.x - m_SellWidth  * m_NumColumn * 0.5f + m_SellWidth  * nCntX,
										  m_FieldHeight[ nCntZ ][ nCntX ],
										  m_Center.z + m_SellHeight * m_NumRow * 0.5f - m_SellHeight * nCntZ ); 


			pVtx[ 0 ].normal  = D3DXVECTOR3( 0.0f, 1.0f, 0.0f ); // コンストラクタによる頂点設定 ( x, y, z )
			
			pVtx += 1;	
		}
	}

	// 頂点バッファのロックを解除
	( m_pVtxBuffer )->Unlock();	

	// 頂点バッファをロックして、仮想頂点アドレスを取得する
	if( FAILED ( ( m_pVtxBuffer )->Lock( 0,
									   0,				// すべてをロック
								       ( void** )&pVtx,  // 仮想頂点アドレス用ポインタのアドレスを渡す
									   0 ) ) )			// ロックフラグ？
								       {	
									 	  return;
									   }	
		
	// 頂点法線の設定
	D3DXVECTOR3 d1;
	D3DXVECTOR3 d2;
	int nCnt = 0;
	for( int nCntZ = 0; nCntZ < m_NumRow + 1; nCntZ++ )
	{
		for( int nCntX = 0; nCntX < m_NumColumn + 1; nCntX++ )
		{
			if( nCntX == m_NumColumn && nCntZ == m_NumRow )
			{
				// パターンほし
				d2 = pVtx[ nCnt - m_NumColumn - 1 ].pos - pVtx[ nCnt ].pos;
				d1 = pVtx[ nCnt - 1 ].pos - pVtx[ nCnt ].pos;
			}
			else if( nCntX == m_NumColumn )
			{			
				// パターンさんかく
				d1 = pVtx[ nCnt + m_NumColumn + 1 ].pos - pVtx[ nCnt ].pos;
				d2 = pVtx[ nCnt - 1 ].pos - pVtx[ nCnt ].pos;
			}
			else if( nCntZ == m_NumRow )
			{			
				// パターンしかく
				d1 = pVtx[ nCnt - m_NumColumn - 1 ].pos - pVtx[ nCnt ].pos;
				d2 = pVtx[ nCnt + 1 ].pos - pVtx[ nCnt ].pos;
			}
			else
			{
				// パターンまる
				d1 = pVtx[ nCnt + 1 ].pos - pVtx[ nCnt ].pos;
				d2 = pVtx[ nCnt + m_NumColumn + 1 ].pos - pVtx[ nCnt ].pos;
			}
			
			D3DXVec3Cross( &pVtx[ nCnt ].normal, &d1, &d2 );
			D3DXVec3Normalize( &pVtx[ nCnt ].normal, &pVtx[ nCnt ].normal );

			nCnt++;
		}
	}
	
	// 頂点バッファのロックを解除
	( m_pVtxBuffer )->Unlock();

	// インデックスバッファの作成
	WORD* pIdx;
	
	// インデックスバッファをロックして、仮想頂点アドレスを取得する
	if( FAILED ( ( m_pIdxBuffer )->Lock( 0,
									        0,				// すべてをロック
									        ( void** )&pIdx,  // 仮想頂点アドレス用ポインタのアドレスを渡す
									        0 ) ) )			// ロックフラグ？
									        {	
									       	  return;
									        }		

	// 頂点インデックスの設定
	for( int nCntZ = 0; nCntZ < m_NumRow; nCntZ++ )
	{
		for( int nCntX = 0; nCntX < m_NumColumn + 1; nCntX++ )
		{
			// 縮退ポリゴン用頂点設定(1)
			if( nCntZ != 0 && nCntX == 0 )
			{
				pIdx[ 0 ] = ( m_NumColumn + 1 ) * ( nCntZ + 1 ); 	
					
				pIdx++;
			}

			// 頂点設定
			pIdx[ 0 ] = ( m_NumColumn + 1 ) * ( nCntZ + 1 ) + nCntX; 
			pIdx[ 1 ] = ( m_NumColumn + 1 ) * nCntZ + nCntX;	

			pIdx += 2;
		}

		// 縮退ポリゴン用頂点設定(2)
		if( nCntZ != m_NumRow - 1 )
		{
			// 頂点座標
			pIdx[ 0 ] = ( pIdx - 2 )[ 1 ];
			pIdx++;
		}
	}
	
	// インデックスバッファのロックを解除
	( m_pIdxBuffer )->Unlock();

	// テクスチャの読み込み
	if( FAILED ( D3DXCreateTextureFromFile( pDevice, POLYGON_TEXTURENAME, &m_pTexture ) ) )
	{
		MessageBox( NULL, "読み込み失敗", "エラー", MB_OK ); 
	}
	
	// オブジェクトタイプの設定
	SetObjType( OBJTYPE_MESHFIELD );
}

/*------------------------------------------------------------------------------
  　終了処理
------------------------------------------------------------------------------*/
void CMeshField::Uninit( void )
{
	// 頂点バッファの破棄
	SAFE_RELEASE( m_pVtxBuffer );
	
	// テクスチャの破棄
	if( m_pTexture != NULL )
	{
		SAFE_RELEASE( m_pTexture );
	}
}

/*------------------------------------------------------------------------------
  　更新
------------------------------------------------------------------------------*/
void CMeshField::Update( void )
{
}

/*------------------------------------------------------------------------------
  　ポリゴン描画処理
------------------------------------------------------------------------------*/
void CMeshField::Draw( void )
{
	Set3D();

	// デバイスのポインタ取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// パイプライン（ストリーム）を設定
	pDevice->SetStreamSource( 0,						// パイプライン番号
							  m_pVtxBuffer,				// パイプラインの元になる領域を指定
							  0,						// オフセット（単位はbyte）※ストリームの開始位置を指定できる
							  sizeof( VERTEX_3D ) );	// 流すデータの単位サイズ（ストライド量）

	// インデックスバッファの設定
	pDevice->SetIndices( m_pIdxBuffer );
	
	// テクスチャの設定
	pDevice->SetTexture( 0, m_pTexture );

	// 頂点フォーマットの設定
	pDevice->SetFVF( FVF_VERTEX_3D );

	// プリミティブ（ポリゴン）の描画
	pDevice->DrawIndexedPrimitive( D3DPT_TRIANGLESTRIP,		// プリミティブの種類
								   0,								// 最小のインデックスまでのオフセット
								   0,								// 最小の頂点インデックス
								   m_NumVertex,				// 頂点数
								   0,								// スタートインデックス（読み始めの場所？)
								   m_NumPolygon				// プリミティブの数
								   );		
}

/*------------------------------------------------------------------------------
  　作成
------------------------------------------------------------------------------*/
CMeshField* CMeshField::Create( void )
{
	CMeshField* field = new CMeshField( 1 );
	field->Init();
	return field;
}

/*------------------------------------------------------------------------------
  　３Ｄ描画準備
------------------------------------------------------------------------------*/
void CMeshField::Set3D( void )
{
	// デバイスのポインタ取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// --- ワールド座標変換行列の作成 ---
	D3DXMATRIX mtxWorld,
			   mtxRotY,
			   mtxPos;	// ワールド座標変換行列
	
	// 単位行列で初期化する
	D3DXMatrixIdentity( &mtxWorld );

	// 回転行列の作成
	static float fRadian = 0.0f;
	//fRadian += 0.02f;

	D3DXMatrixRotationYawPitchRoll( &mtxRotY,				  		   // 格納用
									fRadian, /*D3DXToRadian( 45 ),*/ // Y軸
									0.0f,						   	   // X軸
									0.0f							   // Z軸
									);
	
	// 行列の積算
	D3DXMatrixMultiply( &mtxWorld, // 出力
						&mtxWorld, // 左項
						&mtxRotY   // 右項
						);

	// --- 平行移動行列の反映 ---

	// 平行移動行列作成関数
	D3DXMatrixTranslation( &mtxPos,			// 格納用
						   0.0f,	// X移動量
						   0.0f,	// Y移動量
						   0.0f		// Z移動量
						   );	

	// 行列の積算
	D3DXMatrixMultiply( &mtxWorld, // 出力
						&mtxWorld, // 左項
						&mtxPos   // 右項
						);

	// デバイスに設定
	pDevice->SetTransform( D3DTS_WORLD, // ワールド座標
								&mtxWorld	 // 
							    );				 
}

/*------------------------------------------------------------------------------
  　高さ取得
------------------------------------------------------------------------------*/
float CMeshField::GetHeight( D3DXVECTOR3 Position )
{
	VERTEX_3D* pVtx;  // VRAMの仮想頂点アドレスを格納

	// 頂点バッファをロックして、仮想頂点アドレスを取得する
	if( FAILED ( ( m_pVtxBuffer )->Lock( 0,
									     0,				// すべてをロック
								         ( void** )&pVtx,  // 仮想頂点アドレス用ポインタのアドレスを渡す
									     0 ) ) )			// ロックフラグ？
								         {	
									 	    return E_FAIL;
									     }

	// 左下ポリゴン
	for( int nCntZ = 0; nCntZ < m_NumRow; nCntZ++ )
	{
		for( int nCntX = 0; nCntX < m_NumColumn; nCntX++ )
		{
			D3DXVECTOR3 p0 = pVtx[ ( nCntZ + 1 ) * ( m_NumColumn + 1 ) + nCntX ].pos;
			D3DXVECTOR3 p1 = pVtx[ ( nCntZ )	 * ( m_NumColumn + 1 ) + nCntX ].pos;
			D3DXVECTOR3 p2 = pVtx[ ( nCntZ + 1 ) * ( m_NumColumn + 1 ) + nCntX + 1 ].pos;

			D3DXVECTOR3 v01 = p1 - p0;
			D3DXVECTOR3 v0p = Position - p0;
			D3DXVECTOR3 vc0; // 判定用ベクトル
			D3DXVec3Cross( &vc0, &v01, &v0p );

			if( vc0.y >= 0.0f )
			{
				D3DXVECTOR3 v12 = p2 - p1;
				D3DXVECTOR3 v1p = Position - p1;
				D3DXVECTOR3 vc1; // 判定用ベクトル
				D3DXVec3Cross( &vc1, &v12, &v1p );

				if( vc1.y >= 0.0f )
				{
					D3DXVECTOR3 v20 = p0 - p2;
					D3DXVECTOR3 v3p = Position - p2;
					D3DXVECTOR3 vc2; // 判定用ベクトル
					D3DXVec3Cross( &vc2, &v20, &v3p );

					if( vc2.y >= 0.0f )
					{
						D3DXVECTOR3 v02 = p2 - p0;
						D3DXVECTOR3 vn; // 面法線
						D3DXVec3Cross( &vn, &v01, &v02 );
						D3DXVec3Normalize( &vn, &vn );

						// 高さ計算
						Position.y = p0.y - ( ( Position.x - p0.x ) * vn.x + ( Position.z - p0.z ) * vn.z ) / vn.y;
					}
				}
			}
		}
	}
	
	// 右上ポリゴン
	for( int nCntZ = 0; nCntZ < m_NumRow; nCntZ++ )
	{
		for( int nCntX = 0; nCntX < m_NumColumn; nCntX++ )
		{
			D3DXVECTOR3 p0 = pVtx[ ( nCntZ )     * ( m_NumColumn + 1 ) + nCntX + 1 ].pos;
			D3DXVECTOR3 p2 = pVtx[ ( nCntZ )	 * ( m_NumColumn + 1 ) + nCntX ].pos;
			D3DXVECTOR3 p1 = pVtx[ ( nCntZ + 1 ) * ( m_NumColumn + 1 ) + nCntX + 1 ].pos;

			D3DXVECTOR3 v01 = p1 - p0;
			D3DXVECTOR3 v0p = Position - p0;
			D3DXVECTOR3 vc0; // 判定用ベクトル
			D3DXVec3Cross( &vc0, &v01, &v0p );

			if( vc0.y >= 0.0f )
			{
				D3DXVECTOR3 v12 = p2 - p1;
				D3DXVECTOR3 v1p = Position - p1;
				D3DXVECTOR3 vc1; // 判定用ベクトル
				D3DXVec3Cross( &vc1, &v12, &v1p );

				if( vc1.y >= 0.0f )
				{
					D3DXVECTOR3 v20 = p0 - p2;
					D3DXVECTOR3 v3p = Position - p2;
					D3DXVECTOR3 vc2; // 判定用ベクトル
					D3DXVec3Cross( &vc2, &v20, &v3p );

					if( vc2.y >= 0.0f )
					{
						D3DXVECTOR3 v02 = p2 - p0;
						D3DXVECTOR3 vn; // 面法線
						D3DXVec3Cross( &vn, &v01, &v02 );
						D3DXVec3Normalize( &vn, &vn );

						// 高さ計算
						Position.y = p0.y - ( ( Position.x - p0.x ) * vn.x + ( Position.z - p0.z ) * vn.z ) / vn.y;
					}
				}
			}
		}
	}
	
	// ロック解除
	m_pVtxBuffer->Unlock();

	return Position.y;
}

//------------------------------------------------------------------------------
//　ロード
//------------------------------------------------------------------------------
void CMeshField::Load(void)
{
	char temp[256] = {};
	sprintf(temp, "data\\stage.bin");
	FILE* fp;
	fp = fopen(temp, "rb");
	if (fp == NULL)
	{
		MessageBox(NULL, "バイナリファイルオープン失敗", "エラー", MB_OK);
		return;
	}

	fread(&m_FieldHeight[0], sizeof(float), (FIELD_NUM_COLUMN + 1) * (FIELD_NUM_ROW + 1), fp);

	fclose(fp);
}