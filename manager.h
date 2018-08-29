/*==============================================================================

    manager�̃w�b�_ [manager.h]
                                                       �쐬�� : �����@�S��
                                                       �쐬�� : 
--------------------------------------------------------------------------------
    ��Update : 
==============================================================================*/
#ifndef _MANAGER_H_
#define _MANAGER_H_

/*------------------------------------------------------------------------------
    �w�b�_�t�@�C��
------------------------------------------------------------------------------*/
#include "main.h"
#include "mode.h"
#include "modeGame.h"
#include "textureManager.h"
#include "input.h"
#include "debug.h"
#include "fade.h"

// �O���錾

/*------------------------------------------------------------------------------
  �@�N���X
------------------------------------------------------------------------------*/
class CManager
{
public:
	static void Init( HINSTANCE hInstance, HWND hWnd, BOOL bWindow );
	static void Uninit( void );
	static void Update( void);
	static void Draw( void );

	// �Q�b�^�[
	static CInputKeyboard* GetInputKeyboard( void ){ return m_InputKeyboard; }

	// ���̑�
	static void SetMode(CMode* modeNext);
	static void Fade(CMode* modeNext);

private:
	// ���[�h
	static CMode* m_Mode;
	static CMode* m_modeNext;
	static CFade* m_Fade;

	// �C���t���n
	static CTextureManager* m_TextureManager;
	static CInputKeyboard* m_InputKeyboard;
	static CInputMouse* m_InputMouse;
};

#endif