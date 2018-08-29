/*==============================================================================

    modeTitle�̏��� [modeTitle.cpp]
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
#include "modeTitle.h"
#include "modeTutorial.h"
#include "textureManager.h"
#include  "filepassHeader.h"
#include "sound.h"
#include "background.h"
#include "cursorTitle.h"

/*------------------------------------------------------------------------------
�@�}�N��
------------------------------------------------------------------------------*/

//------------------------------------------------------------------------------
//�@�ÓI�����o�ϐ�
//------------------------------------------------------------------------------
// �I�u�W�F�N�g
CCursorTitle* CModeTitle::m_cursorTitle = NULL;
// ���̑�

/*------------------------------------------------------------------------------
  �@�f�X�g���N�^
------------------------------------------------------------------------------*/
CModeTitle::~CModeTitle()
{
}

/*------------------------------------------------------------------------------
  �@������
------------------------------------------------------------------------------*/
void CModeTitle::Init(void)
{
	// �e�N�X�`���ǂݍ��� //////////////////////////////////////////////
	
	// �C���X�^���X���� /////////////////////////////////////////////////

	// �I�u�W�F�N�g
	CBackground::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), 1.0f, TITLE001_TEXTURENAME);
	m_cursorTitle = CCursorTitle::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.63f, SCREEN_HEIGHT * 0.6f, 0.0f), D3DXVECTOR3(35.0f, 35.0f, 0.0f), 1.0f, CURSORTITLE_TEXTURENAME, CTextureManager::TEXTYPE_NONE);

	// ���̑�

	PlaySound(SOUND_LABEL_BGM000);
}

/*------------------------------------------------------------------------------
  �@�I������
------------------------------------------------------------------------------*/
void CModeTitle::Uninit( void )
{
	CScene::ReleaseAll();	

	StopSound(SOUND_LABEL_BGM000);
}

/*------------------------------------------------------------------------------
  �@�X�V
------------------------------------------------------------------------------*/
void CModeTitle::Update(void)
{
	// �J�[�\���ړ�
	if (CManager::GetInputKeyboard()->GetKeyTrigger(DIK_UP))
	{
		m_cursorTitle->AddPosition(-1);

		if (m_cursorTitle->GetPosition() < 0)
		{
			m_cursorTitle->SetPosition(1);
			m_cursorTitle->AddPos(D3DXVECTOR3(0.0f, 80.0f, 0.0f));
		}
		else
		{
			m_cursorTitle->AddPos(D3DXVECTOR3(0.0f, -80.0f, 0.0f));
		}
	}

	if (CManager::GetInputKeyboard()->GetKeyTrigger(DIK_DOWN))
	{
		m_cursorTitle->AddPosition(1);

		if (m_cursorTitle->GetPosition() > 1)
		{
			m_cursorTitle->SetPosition(0);
			m_cursorTitle->AddPos(D3DXVECTOR3(0.0f, -80.0f, 0.0f));
		}
		else 
		{
			m_cursorTitle->AddPos(D3DXVECTOR3(0.0f, 80.0f, 0.0f));
		}
	}
	
	// �Q�[�����[�h�ύX
	if (CManager::GetInputKeyboard()->GetKeyTrigger(DIK_SPACE))
	{
		if (m_cursorTitle->GetPosition() == 0)
		{
			CManager::Fade(new CModeGame);
		}
		else if (m_cursorTitle->GetPosition() == 1)
		{
			CManager::Fade(new CModeTutorial);
		}
	}
}

/*------------------------------------------------------------------------------
  �@�`�揈��
------------------------------------------------------------------------------*/
void CModeTitle::Draw( void )
{
}
