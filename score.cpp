/*==============================================================================

    scoreの処理 [score.cpp]
                                                       作成者 : 中西　祐介
                                                       作成日 : 
--------------------------------------------------------------------------------
    ■Update : 
==============================================================================*/

/*------------------------------------------------------------------------------
  　ヘッダファイル
------------------------------------------------------------------------------*/
#include "renderer.h"
#include "manager.h"
#include "score.h"

//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CScore::Init( int spritenum )
{	
	m_spriteNum = spritenum;
	m_leftup    = new D3DXVECTOR2[ m_spriteNum ];			// 左上の頂点XY
	m_rightup   = new D3DXVECTOR2[ m_spriteNum ];			// 右上の頂点XY
	m_leftdown  = new D3DXVECTOR2[ m_spriteNum ];			// 左下の頂点XY
	m_rightdown = new D3DXVECTOR2[ m_spriteNum ];			// 右下の頂点XY	
	m_tex	    = new D3DXVECTOR2[ m_spriteNum ];			// ポリゴンのUV値
	m_texsize   = new D3DXVECTOR2[ m_spriteNum ];			// ポリゴンのUV値の大きさ
	m_color     = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// 頂点バッファの作成
	if( FAILED( pDevice->CreateVertexBuffer( sizeof( VERTEX_2D ) * m_spriteNum * 4,  // 作成したい頂点バッファの合計データサイズ
											 D3DUSAGE_WRITEONLY,		  			 // 頂点バッファの使用方法（書き込みのみ）
											 FVF_VERTEX_2D,						 	 // ？
											 D3DPOOL_MANAGED,						 // 頂点バッファの置き場となるメモリを指定（デバイスに委託）
											 &m_pVtxBuff,							 // 頂点バッファ管理インターフェースを格納
											 NULL ) ) )								 // 使わない
											 {
												 return E_FAIL;
											 }

	// 頂点インデックス作成
	pDevice->CreateIndexBuffer( sizeof( DWORD ) * m_spriteNum * 6,
							    0,
							    D3DFMT_INDEX32,
							    D3DPOOL_MANAGED,
							    &m_pIdxBuff,
							    NULL );

	// 頂点のメモリを直でコピーする
	DWORD *vIndex;
	m_pIdxBuff->Lock( 0, 0, ( void** )&vIndex, 0 ); 

	for( int nCntSprite = 0; nCntSprite < m_spriteNum; nCntSprite++ )
	{
		// 左回りで三角形を二つ作る（トライアングルリスト）
		vIndex[ ( nCntSprite * 6 ) + 0 ] = ( nCntSprite * 4 ) + 0;  
		vIndex[ ( nCntSprite * 6 ) + 1 ] = ( nCntSprite * 4 ) + 1;
		vIndex[ ( nCntSprite * 6 ) + 2 ] = ( nCntSprite * 4 ) + 2;
		vIndex[ ( nCntSprite * 6 ) + 3 ] = ( nCntSprite * 4 ) + 2;
		vIndex[ ( nCntSprite * 6 ) + 4 ] = ( nCntSprite * 4 ) + 1;
		vIndex[ ( nCntSprite * 6 ) + 5 ] = ( nCntSprite * 4 ) + 3;
	}

	m_pIdxBuff->Unlock();

	// 頂点の設定
	SetVertex();

	// 初期化
	for (int nCntDigit = 0; nCntDigit < spritenum; nCntDigit++)
	{
		m_leftup[nCntDigit] = D3DXVECTOR2(m_pos.x + m_size.x * (-nCntDigit - 0.5f), m_pos.y - m_size.y * 0.5f);
		m_rightup[nCntDigit] = D3DXVECTOR2(m_pos.x + m_size.x * (-nCntDigit + 0.5f), m_pos.y - m_size.y * 0.5f);
		m_leftdown[nCntDigit] = D3DXVECTOR2(m_pos.x + m_size.x * (-nCntDigit - 0.5f), m_pos.y + m_size.y * 0.5f);
		m_rightdown[nCntDigit] = D3DXVECTOR2(m_pos.x + m_size.x * (-nCntDigit + 0.5f), m_pos.y + m_size.y * 0.5f);
		m_tex[nCntDigit] = D3DXVECTOR2(0.0f, 0.0f);
		m_texsize[nCntDigit] = D3DXVECTOR2(0.1f, 1.0f);
	}

	m_pos = D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z);
	m_size = D3DXVECTOR3(m_size.x, m_size.y, m_size.z);
	m_length = sqrt(m_size.x * m_size.x + m_size.y * m_size.y) / 2.0f;					// 対角線の長さの算出
	m_angle = atan2(m_size.y, m_size.y);															// 対角線の角度の算出

	return S_OK;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CScore::Uninit( void )
{
	// 頂点バッファの破棄
	SAFE_RELEASE( m_pVtxBuff );
	
	// 座標配列ポインタの破棄
	delete[] m_leftup;			// 左上の頂点XY
	delete[] m_rightup;			// 右上の頂点XY
	delete[] m_leftdown;		// 左下の頂点XY
	delete[] m_rightdown;		// 右下の頂点XY	
	delete[] m_tex;				// ポリゴンのUV値
	delete[] m_texsize;			// ポリゴンのUV値の大きさ

	// 終了処理
	//Release();
	CScene::SetDelete();
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CScore::Update( void )
{
	int nValue = m_score;			// 表示するスコア
	int nNum = 0;					// 表示する桁の値

	for (int nNumDigit = 0; nNumDigit < m_spriteNum; nNumDigit++)
	{
		nNum = nValue % 10;
		nValue /= 10;
		m_tex[nNumDigit] = D3DXVECTOR2(nNum * 0.1f, 0.0f);
	}

	// 頂点の設定
	SetVertex();
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CScore::Draw( void )
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
	pDevice->SetTexture( 0,	CTextureManager::BindTexture(m_TexID));			

	// 頂点フォーマットの設定
	pDevice->SetFVF( FVF_VERTEX_2D );

	// プリミティブ（ポリゴン）の描画
	pDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, // プリミティブの種類
								   0,				   // 描画開始位置のオフセット（頂点数）
								   0,				   // 最小インデックス番号
								   m_spriteNum * 6,	   // 最大インデックス番号
								   0,				   // インデックス配列の読み取り位置
								   m_spriteNum * 2 );  // 描画するプリミティブの数
}

//=============================================================================
// 頂点の設定
//=============================================================================
void CScore::SetVertex( void )
{	
	VERTEX_2D* pVtx; // VRAMの仮想アドレスを格納

	// 頂点バッファをロックして、仮想アドレスを取得する
	m_pVtxBuff->Lock( 0,
					  0,			   // すべてをロック
					  ( void** )&pVtx, // 仮想アドレス用ポインタのアドレスを渡す
					  0 );			   // ロックフラグ？
	
	// 頂点座標の設定( 2D座標は右回りに頂点を用意する )
	for( int nCntSprite = 0; nCntSprite < m_spriteNum; nCntSprite++ )
	{
		pVtx[ 0 ].pos = D3DXVECTOR3( m_leftup[ nCntSprite ].x,    m_leftup[ nCntSprite ].y,	   0.0f ); // コンストラクタによる頂点設定 ( x, y, z )
		pVtx[ 1 ].pos = D3DXVECTOR3( m_rightup[ nCntSprite ].x,   m_rightup[ nCntSprite ].y,   0.0f ); 
		pVtx[ 2 ].pos = D3DXVECTOR3( m_leftdown[ nCntSprite ].x,  m_leftdown[ nCntSprite ].y,  0.0f );
		pVtx[ 3 ].pos = D3DXVECTOR3( m_rightdown[ nCntSprite ].x, m_rightdown[ nCntSprite ].y, 0.0f ); 

		// rhwの設定（必ず1.0f）※手前か奥（バッファ）の情報？
		pVtx[ 0 ].rhw = 1.0f;
		pVtx[ 1 ].rhw = 1.0f;
		pVtx[ 2 ].rhw = 1.0f;
		pVtx[ 3 ].rhw = 1.0f;

		// 頂点カラーの設定（ 0 ～ 255の整数値 )
		pVtx[ 0 ].color = D3DXCOLOR( m_color.r, m_color.g, m_color.b, m_color.a );
		pVtx[ 1 ].color = D3DXCOLOR( m_color.r, m_color.g, m_color.b, m_color.a ); 
		pVtx[ 2 ].color = D3DXCOLOR( m_color.r, m_color.g, m_color.b, m_color.a );
		pVtx[ 3 ].color = D3DXCOLOR( m_color.r, m_color.g, m_color.b, m_color.a );

		// 頂点データにUVデータを追加
		pVtx[ 0 ].tex = D3DXVECTOR2( m_tex[ nCntSprite ].x,							    m_tex[ nCntSprite ].y );
		pVtx[ 1 ].tex = D3DXVECTOR2( m_tex[ nCntSprite ].x + m_texsize[ nCntSprite ].x, m_tex[ nCntSprite ].y );
		pVtx[ 2 ].tex = D3DXVECTOR2( m_tex[ nCntSprite ].x,								m_tex[ nCntSprite ].y + m_texsize[ nCntSprite ].y );
		pVtx[ 3 ].tex = D3DXVECTOR2( m_tex[ nCntSprite ].x + m_texsize[ nCntSprite ].x, m_tex[ nCntSprite ].y + m_texsize[ nCntSprite ].y );

		pVtx += 4;
	}

	// 頂点バッファのロックを解除
	m_pVtxBuff->Unlock();
}

//=============================================================================
// 作成
//=============================================================================
CScore* CScore::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int spriteNum, char* filePass)
{
	CScore* pScore = new CScore(CScene::PRIORITY_2D);
	pScore->SetPos(pos);
	pScore->SetSize(size);
	pScore->SetScore(0);
	pScore->SetTexID(CTextureManager::LoadTexture(filePass, CTextureManager::TEXTYPE_NONE));
	pScore->Init(spriteNum);

	return pScore;
}