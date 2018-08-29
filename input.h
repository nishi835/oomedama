/*==============================================================================

    input�̃w�b�_�[ [input.h]
                                                       �쐬�� : �����@�S��
                                                       �쐬�� : 2016/4/17
--------------------------------------------------------------------------------
    ��Update : 
==============================================================================*/
#ifndef _INPUT_H_
#define _INPUT_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	NUM_KEY_MAX	(256)	// �L�[�ő吔

/*------------------------------------------------------------------------------
  �@�w�b�_�t�@�C��
------------------------------------------------------------------------------*/
#include "main.h"

// ���N���X
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

// �L�[�{�[�h�N���X
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
	BYTE	m_aKeyState[NUM_KEY_MAX];			// �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
	BYTE	m_aKeyStateTrigger[NUM_KEY_MAX];	// �g���K�[���[�N
	BYTE	m_aKeyStateRelease[NUM_KEY_MAX];	// �����[�X���[�N
	BYTE	m_aKeyStateRepeat[NUM_KEY_MAX];		// ���s�[�g���[�N
	int		m_aKeyStateRepeatCnt[NUM_KEY_MAX];	// ���s�[�g�J�E���^
};

// �}�E�X�N���X
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
	
	// �O�̃t���[���Ƃ̍���������
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