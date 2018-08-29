/*==============================================================================

    rendererの処理 [renderer.cpp]
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

LPDIRECT3D9 CRenderer::m_D3D = NULL;
LPDIRECT3DDEVICE9 CRenderer::m_D3DDevice = NULL;
LPD3DXFONT CRenderer::m_pFont = NULL;

//=============================================================================
// レンダラーの初期化処理
//=============================================================================
HRESULT CRenderer::Init( HINSTANCE hInstance, HWND hWnd, BOOL bWindow )
{
	D3DPRESENT_PARAMETERS d3dpp; // デバイスを作るための設定の格納
	D3DDISPLAYMODE d3ddm; // ディスプレイモードの格納

	// Direct3Dインターフェイスの取得
	m_D3D = Direct3DCreate9( D3D_SDK_VERSION );
	if( m_D3D == NULL )
	{
		return E_FAIL; // HRESULT型の戻り値はエラーの内容を示す
	}

	// ディスプレイモードの取得
	if( FAILED( m_D3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm ) ) ) // FAILEDマクロでくくると、BOOL型にキャストされる
	{
		return E_FAIL;
	}

	// デバイスのプレゼントパラメーターの設定（ デバイスを作るための設定の設定 )
	ZeroMemory( &d3dpp, sizeof( d3dpp ) ); // メモリ空間を0で埋める 

	// バックバッファの設定
	d3dpp.BackBufferWidth = SCREEN_WIDTH; // バックバッファの幅
	d3dpp.BackBufferHeight = SCREEN_HEIGHT; // バックバッファの高さ
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1; // バックバッファの数

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD; // スワップエフェクトの設定
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16; // ステンシルバッファを使うときに変更
	d3dpp.Windowed = bWindow; // フルスクリーンにするときはTRUEにする
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; // フルスクリーンにするときに適宜数値を入れる
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT; // 

	// Direct3Dデバイスの作成
	if( FAILED( m_D3D->CreateDevice( D3DADAPTER_DEFAULT, // グラフィックボードの選択
									  D3DDEVTYPE_HAL, // ハードウェアが描画
									  hWnd, // ウィンドウ指定
									  D3DCREATE_HARDWARE_VERTEXPROCESSING, // 描画、頂点処理はハードウェアに任せる
									  &d3dpp,
									  &m_D3DDevice ) ) ) // デバイスを格納
	{
		if( FAILED( m_D3D->CreateDevice( D3DADAPTER_DEFAULT, // グラフィックボードの選択
										  D3DDEVTYPE_HAL, // ハードウェアが描画
										  hWnd, // ウィンドウ指定
										  D3DCREATE_SOFTWARE_VERTEXPROCESSING, // 描画はハードウェア、頂点処理はCPUが行う
										  &d3dpp,
										  &m_D3DDevice ) ) ) // デバイスを格納
		{
			if( FAILED( m_D3D->CreateDevice( D3DADAPTER_DEFAULT, // グラフィックボードの選択
											  D3DDEVTYPE_REF, // ソフトウェア( CPU )が描画
											  hWnd, // ウィンドウ指定
											  D3DCREATE_SOFTWARE_VERTEXPROCESSING, // 描画はハードウェア、頂点処理はCPUが行う
											  &d3dpp,
											  &m_D3DDevice ) ) ) // デバイスを格納
			{
				return E_FAIL; // デバイス取得不可
			}
		}
	}

	// *** レンダーステート（デバイス設定）の設定 ***

	// カリング（片面描画）の設定 
	m_D3DDevice->SetRenderState( D3DRS_CULLMODE,						  // カリング設定
								  D3DCULL_CCW );						  // 左回りでカリング

	// ポリゴンの塗りつぶし設定
	m_D3DDevice->SetRenderState( D3DRS_FILLMODE,						  // 塗りつぶし設定
								  D3DFILL_SOLID );						  // 面を塗りつぶす

	// アルファブレンド（透明化）の設定
	m_D3DDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );		  // アルファブレンドが有効かどうか
	m_D3DDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );	  // 描画元（スプライト）のアルファブレンド設定
	m_D3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA); // 描画先（背景）のアルファブレンド設定

	// *** サンプラーステートの設定 ***

	m_D3DDevice->SetSamplerState( 0,
								   D3DSAMP_MINFILTER,    // 縮小時
								   D3DTEXF_LINEAR );     // リニアフィルターを指定
	
	m_D3DDevice->SetSamplerState( 0,
								   D3DSAMP_MAGFILTER,	 // 拡大時
								   D3DTEXF_LINEAR );	 // リニアフィルターを指定
	
	m_D3DDevice->SetSamplerState( 0,
								   D3DSAMP_ADDRESSU,	 // u軸（x軸）をアドレッシングモードに設定
								   D3DTADDRESS_WRAP );   // ラップモード

														 // *** サンプラーステートの設定 ***

	 // テクスチャブレンディングの設定
	m_D3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);   // 引数１,テクスチャのアルファ値
	m_D3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);   // 演算子,乗算
	m_D3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);   // 引数２,ディフューズ（ポリゴン）のアルファ値	

	// ライトの初期化 ////////////////////////////////////////////	

	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();	

	D3DLIGHT9 light;									  // ライトの構造体
	ZeroMemory( &light, sizeof( D3DLIGHT9 ) );			  // 構造体の初期化

	light.Type		   = D3DLIGHT_DIRECTIONAL;					// ライトのタイプ 
	light.Diffuse	   = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );   // ライト(平行光源）のカラー(1.0fが100%）
	light.Ambient	   = D3DXCOLOR( 0.8f, 0.8f, 0.8f, 1.0f );   // 環境光
	D3DXVECTOR3 vecDir = D3DXVECTOR3( 1.0f, -1.0f, 1.0f );		// ライト(平行光源）の向き

	// ライトベクトルを単位ベクトル化
	D3DXVec3Normalize( ( D3DXVECTOR3* )&light.Direction,   
					   &vecDir
					   );

	// デバイスにライトを設定
	pDevice->SetLight( 0, 
					   &light
					   );

	// ライトのスイッチ
	pDevice->LightEnable( 0,
						  TRUE
						  );

	// アンビエントライトの設定
	pDevice->SetRenderState( D3DRS_AMBIENT, 0x00202020 );


	return S_OK;

}

//=============================================================================
// レンダラーの終了処理
//=============================================================================
void CRenderer::Uninit( void )
{
	// デバイスの破棄
	if( m_D3DDevice != NULL ) // デバイスが使用中かどうかをチェック
	{
		m_D3DDevice->Release(); // Direct3Dデバイスの解放　
		m_D3DDevice = NULL; // デバイスが格納されていたアドレスを消去
	}

	// インターフェースの破棄
	if( m_D3D != NULL ) // インターフェースが使用中かチェック
	{
		m_D3D->Release(); // Direct3Dインターフェースの解放
		m_D3D = NULL; // インターフェースが格納されていたアドレスを消去
	}
}

//=============================================================================
// レンダラーの更新処理
//=============================================================================
void CRenderer::Update( void )
{
}

//=============================================================================
// レンダラーの描画開始
//=============================================================================
void CRenderer::DrawBegin( void )
{
	// 画面（バックバッファ）のクリア　
	m_D3DDevice->Clear( 0, 
					     NULL,
						 D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, // 
					     D3DCOLOR_RGBA( 0, 255, 255, 255 ),
						 1.0f,
						 0 );

	// 描画の開始
	m_D3DDevice->BeginScene(); // ここで描画のタスクを積み上げる	
}

//=============================================================================
// レンダラーの描画終了
//=============================================================================
void CRenderer::DrawEnd( void )
{
	// 描画の終了
	m_D3DDevice->EndScene();	

	m_D3DDevice->Present( NULL, NULL, NULL, NULL ); // バックバッファとフロントバッファの入れ替え　
	// ※溜め込んだタスクをここでまとめて処理する
}