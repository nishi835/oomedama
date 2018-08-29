
/*==============================================================================

    mainの処理 [main.cpp]
                                                       作成者 : 中西　祐介
                                                       作成日 : 
--------------------------------------------------------------------------------
    ■Update : 
==============================================================================*/

/*------------------------------------------------------------------------------
  　ヘッダーファイル
------------------------------------------------------------------------------*/
#include "main.h"
#include "manager.h"
#include "scene.h"    // 継承クラスのインクルードの前に、基底クラスをインクルードする
#include "scene2D.h"
#include "scene3D.h"
#include "sceneModel.h"

/*------------------------------------------------------------------------------
  　マクロ定義
------------------------------------------------------------------------------*/
#define CLASS_NAME	"hoge"		 //ウィンドウクラス名
#define WINDOW_NAME	"タイトル名" //ウィンドウタイトル

#define NUM_VERTEX ( 4 )  // 頂点の数
#define NUM_POLYGON ( 2 ) // ポリゴンの枚数

/*------------------------------------------------------------------------------
  　グローバル変数
------------------------------------------------------------------------------*/
LPDIRECT3D9 g_pD3D = NULL; // Direct3Dインターフェース ( DXのバージョンを取得する )　※LP～はポインタ型！
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL; // Direct3Dデバイスへのポインタ ( グラフィックボードにアクセスするためのポインタ ) ※最重要

HWND g_hWnd; //ウィンドウハンドル（ポインタ）

/*------------------------------------------------------------------------------
  　メイン関数
------------------------------------------------------------------------------*/
int APIENTRY WinMain( HINSTANCE hInstance,
					  HINSTANCE hPrevInstance,
					  LPSTR lpCmdLine,
					  int nCmdShow )
{
	UNREFERENCED_PARAMETER( hPrevInstance );
	UNREFERENCED_PARAMETER( lpCmdLine );

	WNDCLASSEX wcex; //ウィンドウクラス構造体

	wcex.cbSize			= sizeof( WNDCLASSEX ); //構造体のサイズ
	wcex.style			= CS_CLASSDC; //ウィンドウクラスのスタイルを設定
	wcex.lpfnWndProc	= WndProc; //ウィンドウプロシージャの関数ポインタ（アドレス）を指定
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance; //WinMainのパラメータのインスタンスハンドルを指定
	wcex.hIcon			= NULL; //ウィンドウアイコンの指定
	wcex.hCursor		= LoadCursor( NULL, IDC_ARROW ); //マウスカーソルの指定
	wcex.hbrBackground  = ( HBRUSH )( COLOR_WINDOW + 1 ); //ウィンドウのクライアント領域の背景色の指定
	wcex.lpszMenuName   = NULL; //ウィンドウメニューの指定
	wcex.lpszClassName  = CLASS_NAME; //このウィンドウクラスの名前
	wcex.hIconSm	    = NULL; //ミニアイコンの指定

	//ウィンドウクラスの登録
	RegisterClassEx( &wcex );

	MSG msg;

	//ウィンドウを作成
	RECT cr = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	DWORD style = WS_OVERLAPPEDWINDOW;
	AdjustWindowRect( &cr, style, FALSE );
	int ww = cr.right - cr.left;
	int wh = cr.bottom - cr.top;
	
	// デスクトップの矩形を取得
	RECT dr;
	GetWindowRect( GetDesktopWindow(), &dr );
	int dw = dr.right - dr.left;
	int dh = dr.bottom - dr.top;

	// ウィンドウの初期位置を画面中央に設定
	int wx = ww > dw ? 0 : ( dw / 2 ) - ( ww / 2 );
	int wy = wh > dh ? 0 : ( dh / 2 ) - ( wh / 2 );

	g_hWnd = CreateWindowEx( 0, //拡張ウィンドウスタイル
			 		       CLASS_NAME, //ウィンドウクラスの名前
					   	   WINDOW_NAME, //ウィンドウの名前
						   style ^ ( WS_MAXIMIZEBOX | WS_THICKFRAME ), //ウィンドウのスタイル（タイプ）※重要
						   wx, //ウィンドウの初期X座標
						   wy, //ウィンドウの初期Y座標
						   ww, //ウィンドウの幅（ウィンドウのフレームも含む）
						   wh, //ウィンドウの高さ（ウィンドウのフレームも含む）
						   NULL, //親ウィンドウのハンドル
						   NULL, //メニューバーのハンドル又は子ウィンドウID
						   hInstance, //インスタンス
						   NULL ); //ウィンドウ作成データ
	
	//ウィンドウの表示
	ShowWindow( g_hWnd, nCmdShow ); //ウィンドウの呼び出し
	UpdateWindow( g_hWnd );
	
	// Managerの初期化
	CManager::Init( hInstance, g_hWnd, TRUE );
	
	//メッセージループ
	//第１引数：メッセージ情報
	//第２引数：ウィンドウのハンドル
	//※メッセージを取得するまで動作が止まる仕様なので、ゲームループにするにはこのあたりをいじる必要がある
	for( ;; )  //( GetMessage( &msg, NULL, 0, 0 ) ) //GetMessage関数で、ウィンドウをコントロールする
	{
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) != 0)
		{
			// Windowsの処理
			if( msg.message == WM_QUIT )
			{
				break;
			}
			else
			{
				//メッセージの翻訳と送出
				TranslateMessage( &msg ); 
				DispatchMessage( &msg ); //ウィンドウプロシージャにメッセージを送出
			}
		}
		else
		{
			//DirectXの処理
			CManager::Update();
			CManager::Draw();
		}
	}

	// DirectXの終了処理
	CManager::Uninit();

	//ウィンドウクラスの登録解除（ウィンドウの終了処理）※本来は自動的にやってくれる
	UnregisterClass( CLASS_NAME, wcex.hInstance );
	
	return ( int )msg.wParam;
}

/*------------------------------------------------------------------------------
　  ウィンドウプロシージャ
    (CALLBACK : Win32API関数を呼び出すときの規約
    g_hWnd :ウィンドウのハンドル
    uMsg :メッセージの識別子
    wParam : メッセージの最初のパラメータ(補足情報) ※ポインタ型だが、用途は何でもよい
　  lParam : メッセージの２番目のパラメータ(補足情報) ※ポインタ型だが、用途は何でもよい
------------------------------------------------------------------------------*/
LRESULT CALLBACK WndProc( HWND g_hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	HDC hDC; // デバイスコンテキスト用変数
	PAINTSTRUCT ps;
	const RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	switch( uMsg )
	{
	case WM_DESTROY:
		DestroyWindow( g_hWnd );
		PostQuitMessage( 0 );
		break;

	case WM_KEYDOWN:
		switch( wParam )
		{
		// 終了処理
		case VK_ESCAPE:
			UINT nID = MessageBox( NULL, "終了しますか?",  "終了", MB_YESNO );
			if( nID == IDYES )
			{
				DestroyWindow( g_hWnd );
			}
		}
		break;

	// ウィンドウが作られたとき
	case WM_CREATE:
		break;

	// ボタンが押されたとき
	case WM_COMMAND:
		break;

	// 描画メッセージの受信
	case WM_PAINT:
		break;

	case WM_TIMER:
		//InvalidateRect( g_hWnd, NULL, TRUE );
		break;

	default:
		break;
	}

	return DefWindowProc( g_hWnd, uMsg, wParam, lParam );
}

/*------------------------------------------------------------------------------
　ゲッター
 ------------------------------------------------------------------------------*/
HWND GethWnd(void)
{
	return g_hWnd;
}