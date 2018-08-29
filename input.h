/*==============================================================================

    inputのヘッダー [input.h]
                                                       作成者 : 中西　祐介
                                                       作成日 : 2016/4/17
--------------------------------------------------------------------------------
    ■Update : 
==============================================================================*/
#ifndef _INPUT_H_
#define _INPUT_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	NUM_KEY_MAX	(256)	// キー最大数

/*------------------------------------------------------------------------------
  　ヘッダファイル
------------------------------------------------------------------------------*/
#include "main.h"

// 基底クラス
class CInput
{
public:
	CInput();
	virtual ~CInput();

	virtual HRESULT  Init( HINSTANCE hInstance, HWND hWnd );
	virtual void Uninit( void );
	virtual HRESULT Update( void ) = 0;

protected:
	static LPDIRECTINPUT8 m_pDInput;
	LPDIRECTINPUTDEVICE8  m_pDIDevice;
};

// キーボードクラス
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();	

	HRESULT  Init( HINSTANCE hInstance, HWND hWnd );
	void Uninit( void );
	HRESULT Update( void );

	BOOL GetKeyPress( int nKey );
	BOOL GetKeyTrigger(int nKey);
	BOOL GetKeyRelease(int nKey);
	BOOL GetKeyRepeat(int nKey);
	void FlushKeyTrigger(int nKey);	

private:
	BYTE	m_aKeyState[NUM_KEY_MAX];			// キーボードの状態を受け取るワーク
	BYTE	m_aKeyStateTrigger[NUM_KEY_MAX];	// トリガーワーク
	BYTE	m_aKeyStateRelease[NUM_KEY_MAX];	// リリースワーク
	BYTE	m_aKeyStateRepeat[NUM_KEY_MAX];		// リピートワーク
	int		m_aKeyStateRepeatCnt[NUM_KEY_MAX];	// リピートカウンタ
};

// マウスクラス
class CInputMouse : public CInput
{
public:
	CInputMouse(){}
	~CInputMouse(){}

	HRESULT Init( HINSTANCE hInst, HWND hWnd );
	void Uninit( void );
	HRESULT Update( void )override;

	BOOL GetLeftPress( void );
	BOOL GetLeftTrigger( void );
	BOOL GetLeftRelease( void );
	BOOL GetRightPress( void );
	BOOL GetRightTrigger( void );
	BOOL GetRightRelease( void );
	BOOL GetCenterPress( void );
	BOOL GetCenterTrigger( void );
	BOOL GetCenterRelease( void );
	
	// 前のフレームとの差分が取れる
	LONG GetAxisX( void );
	LONG GetAxisY( void );
	LONG GetWheel( void );
	const POINT& GetPosWorld( void ){ return m_posMouseWorld; }

private:
	DIMOUSESTATE2 m_mouseState;
	DIMOUSESTATE2 m_mouseStateTrigger;
	POINT         m_posMouseWorld;
};

#endif