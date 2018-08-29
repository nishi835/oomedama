/*==============================================================================

    managerのヘッダ [manager.h]
                                                       作成者 : 中西　祐介
                                                       作成日 : 
--------------------------------------------------------------------------------
    ■Update : 
==============================================================================*/
#ifndef _MANAGER_H_
#define _MANAGER_H_

/*------------------------------------------------------------------------------
    ヘッダファイル
------------------------------------------------------------------------------*/
#include "main.h"
#include "mode.h"
#include "modeGame.h"
#include "textureManager.h"
#include "input.h"
#include "debug.h"
#include "fade.h"

// 前方宣言

/*------------------------------------------------------------------------------
  　クラス
------------------------------------------------------------------------------*/
class CManager
{
public:
	static void Init( HINSTANCE hInstance, HWND hWnd, BOOL bWindow );
	static void Uninit( void );
	static void Update( void);
	static void Draw( void );

	// ゲッター
	static CInputKeyboard* GetInputKeyboard( void ){ return m_InputKeyboard; }

	// その他
	static void SetMode(CMode* modeNext);
	static void Fade(CMode* modeNext);

private:
	// モード
	static CMode* m_Mode;
	static CMode* m_modeNext;
	static CFade* m_Fade;

	// インフラ系
	static CTextureManager* m_TextureManager;
	static CInputKeyboard* m_InputKeyboard;
	static CInputMouse* m_InputMouse;
};

#endif