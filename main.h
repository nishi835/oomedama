/*==============================================================================

    mainのヘッダー [main.h]
                                                       作成者 : 中西　祐介
                                                       作成日 : 2016/4/17
--------------------------------------------------------------------------------
    ■Update : 
==============================================================================*/
#ifndef _MAIN_H_
#define _MAIN_H_

/*------------------------------------------------------------------------------
  　ヘッダファイル
------------------------------------------------------------------------------*/
#include <Windows.h>
#include <d3dx9.h>
#define DIRECTINPUT_VERSION ( 0x0800 )
#include <dinput.h>						// ※順番を必ず守る
#include <stdio.h>

// ライブラリのリンク
#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )
#pragma comment( lib, "dxguid.lib" )
#pragma comment( lib, "dinput8.lib" )   // DirectInput8のリンク

/*------------------------------------------------------------------------------
  　マクロ定義
------------------------------------------------------------------------------*/
#define SCREEN_WIDTH ( 800 ) //ウィンドウの幅
#define SCREEN_HEIGHT ( 600 ) //ウィンドウの高さ
#define TEXTURENAME "data/TEXTURE/gang02.png"

// 頂点フォーマット
#define FVF_VERTEX_2D ( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 )  // ( 座標変換済み頂点座標 | 頂点カラー | テクスチャ座標 )
#define FVF_VERTEX_3D ( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 )  // ( 座標変換済み頂点座標 | 法線 | 頂点カラー | テクスチャ )

// セーフリリースマクロ
#define SAFE_RELEASE( x ) { if( x ) { ( x )->Release(); ( x ) = NULL; } }

/*------------------------------------------------------------------------------
  　構造体の宣言
------------------------------------------------------------------------------*/
// 頂点情報構造体( 上の頂点フォーマットと構造を合わせること )
typedef struct 
{
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR color;
	D3DXVECTOR2 tex;	// ＵＶ座標の構造体　※必ず構造体の最後に宣言する
}VERTEX_2D;

// 頂点座標構造体( 上の頂点フォーマットと構造を合わせること )
typedef struct 
{
	D3DXVECTOR3 pos; // 頂点座標の構造体
	D3DXVECTOR3 normal;
	D3DCOLOR	color; // 頂点カラーの構造体
	D3DXVECTOR2 tex; // ＵＶ座標の構造体　※必ず構造体の最後に宣言する
}VERTEX_3D;

/*------------------------------------------------------------------------------
  　プロトタイプ宣言
------------------------------------------------------------------------------*/
LRESULT CALLBACK WndProc( HWND hWnd, //ウィンドウの番号
						UINT uMsg,	 //ウィンドウメッセージ
						WPARAM wParam,
						LPARAM lParam );

HWND GethWnd(void);

#endif