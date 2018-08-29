/*==============================================================================

    manager�̏��� [manager.cpp]
                                                       �쐬�� : �����@�S��
                                                       �쐬�� : 
--------------------------------------------------------------------------------
    ��Update : 
==============================================================================*/

/*------------------------------------------------------------------------------
  �@�w�b�_�t�@�C��
------------------------------------------------------------------------------*/
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "modeTitle.h"
#include "modeGame.h"
#include "textureManager.h"
#include "input.h"
#include "sound.h"
#include "debug.h"
#include "scene.h"
#include "scene2D.h"
#include "fade.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
// ���[�h
CMode* CManager::m_Mode = NULL;
CMode* CManager::m_modeNext = NULL;
CFade* CManager::m_Fade = NULL;
// �C���t���n
CTextureManager* CManager::m_TextureManager = NULL;
CInputKeyboard* CManager::m_InputKeyboard = NULL;
CInputMouse* CManager::m_InputMouse = NULL;

//=============================================================================
// ����������
//=============================================================================
void CManager::Init( HINSTANCE hInstance, HWND hWnd, BOOL bWindow )
{
	CRenderer::Init( hInstance, hWnd, TRUE );

	// �C���t���n
	m_TextureManager = new CTextureManager();
	m_TextureManager->Init();
	m_InputKeyboard = new CInputKeyboard();
	m_InputKeyboard->Init( hInstance, hWnd );
	m_InputMouse = new CInputMouse();
	m_InputMouse->Init( hInstance, hWnd );
	InitSound(hWnd);

	// ���[�h������
	m_Mode = new CModeTitle();
	m_Mode->Init();

#ifdef _DEBUG

	CDebug::Init();

#endif

}

//=============================================================================
// �I������
//=============================================================================
void CManager::Uninit( void )
{
	if( m_TextureManager != NULL )
	{
		m_TextureManager->Uninit();
		delete m_TextureManager;
		m_TextureManager = NULL;
	}

	if( m_InputKeyboard != NULL )
	{
		m_InputKeyboard->Uninit();
		delete m_InputKeyboard;
		m_InputKeyboard = NULL;
	}
	
	if( m_InputMouse != NULL )
	{
		m_InputMouse->Uninit();
		delete m_InputMouse;
		m_InputMouse = NULL;
	}

	CRenderer::Uninit();
	UninitSound();

#ifdef _DEBUG

	CDebug::Uninit();

#endif

}

//=============================================================================
// �X�V����
//=============================================================================
void CManager::Update(void)
{

#ifdef _DEBUG

	CDebug::ClearText();

#endif

	// �C���t���n�̍X�V
	if(m_InputKeyboard) m_InputKeyboard->Update();

	// �V�[���̍X�V
	CScene::UpdateAll();

	// �Q�[���̍X�V
	if(m_Mode) m_Mode->Update();

	// �t�F�[�h�̍X�V
	if (m_Fade)
	{
		m_Fade->Update();

		if (m_Fade->GetFadeMode() == CFade::FADE_OUTEND)
		{
			SetMode(m_modeNext);
			m_Fade->SetFadeMode(CFade::FADE_IN);
		}

		if (m_Fade->GetFadeMode() == CFade::FADE_END)
		{
			m_Fade->Uninit();
			delete m_Fade;
			m_Fade = NULL;
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CManager::Draw( void )
{
	// �`��J�n
	CRenderer::DrawBegin();
	
	// �V�[���̕`��	
	CScene::DrawAll();

	// �t�F�[�h�̕`��
	if (m_Fade) m_Fade->Draw();

#ifdef _DEBUG

	CDebug::Draw();

#endif

	// �`��I��
	CRenderer::DrawEnd();

	// �폜�`�F�b�N
	CScene::CheckRelease();
}

//=============================================================================
// ���[�h�ݒ�
//=============================================================================
void CManager::SetMode(CMode* modeNext)
{
	if (m_Mode != NULL)
	{
		m_Mode->Uninit();
		delete m_Mode;
	}

	m_Mode = modeNext;

	if (m_Mode != NULL)
	{
		m_Mode->Init();
	}
}

//=============================================================================
// �t�F�[�h
//=============================================================================
void CManager::Fade(CMode* modeNext)
{
	m_Fade = CFade::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), FADE_TEXTURENAME);

	m_modeNext = modeNext;
}