/*==============================================================================

    textureManager�̏��� [textureManager.cpp]
                                                       �쐬�� : �����@�S��
                                                       �쐬�� :
--------------------------------------------------------------------------------
    ��Update : 
==============================================================================*/

/*------------------------------------------------------------------------------
  �@�w�b�_�t�@�C��
------------------------------------------------------------------------------*/
#include "textureManager.h"

/*------------------------------------------------------------------------------
  �@�}�N��
------------------------------------------------------------------------------*/
#define TEXSLOT_NUM (30) // �e�N�X�`���X���b�g�̍ő吔

/*------------------------------------------------------------------------------
  �@�ÓI�����o�ϐ�
------------------------------------------------------------------------------*/
CTexture* CTextureManager::m_textureSlot[ 256 ] = {};
int CTextureManager::m_TexID[256] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTextureManager::CTextureManager( void )
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTextureManager::~CTextureManager()
{
}

//=============================================================================
// ������
//=============================================================================
void CTextureManager::Init( void )
{
	for ( int nCnt = 0; nCnt < TEXSLOT_NUM; nCnt++ )
	{
		if ( m_textureSlot[ nCnt ] != NULL )
		{
			m_textureSlot[ nCnt ]->Uninit();
			delete m_textureSlot[ nCnt ];
			m_textureSlot[ nCnt ] = NULL;
		}

		m_textureSlot[ nCnt ] = NULL;
	}
}

//=============================================================================
// �I������
//=============================================================================
void CTextureManager::Uninit( void )
{
	for ( int nCnt = 0; nCnt < TEXSLOT_NUM; nCnt++ )
	{
		if ( m_textureSlot[ nCnt ] != NULL )
		{
			m_textureSlot[ nCnt ]->Uninit();
			delete m_textureSlot[ nCnt ];
			m_textureSlot[ nCnt ] = NULL;
		}
	}
}

//=============================================================================
// �e�N�X�`���̃��[�h
//=============================================================================
int CTextureManager::LoadTexture( char* filepass, CTextureManager::TEXTYPE textype )
{
	if ( filepass == NULL ) return - 1;
	for ( int IDNum = 0; IDNum < TEXSLOT_NUM; IDNum++ )
	{
		if ( m_textureSlot[ IDNum ] != NULL ) // �X���b�g�����łɎg�p����Ă���ꍇ
		{
			const char* slotFilepass = m_textureSlot[ IDNum ]->GetTexpass();   // �t�@�C���p�X�擾
			int valueStrcmp = strcmp( slotFilepass, filepass );
			if ( valueStrcmp == 0 )
			{
				m_TexID[textype] = IDNum;
				return IDNum;
			}
			else continue;
		}

		if ( m_textureSlot[ IDNum ] == NULL ) // �X���b�g�ɋ󂪂�������e�N�X�`��������
		{
			m_textureSlot[ IDNum ] = new CTexture( filepass );
			m_TexID[textype] = IDNum;
 			return IDNum;
		}
	}

	// ��O����
	MessageBox( NULL, "�g�p�ł���e�N�X�`���X���b�g���Ȃ�", "�G���[", MB_OK | MB_ICONHAND );
	return - 1;
}

//=============================================================================
// �e�N�X�`���̃o�C���h
//=============================================================================
// ID�ɂ��w��
LPDIRECT3DTEXTURE9 CTextureManager::BindTexture( int IDNum )
{
	if ( IDNum == - 1 ) return NULL;
	if ( m_textureSlot[ IDNum ] == NULL ) return NULL;
	return m_textureSlot[ IDNum ]->GetTexPointer();
}

// �^�C�v�ɂ��w��
LPDIRECT3DTEXTURE9 CTextureManager::BindTexture(CTextureManager::TEXTYPE textype)
{
	if (m_textureSlot[m_TexID[textype]] == NULL) return NULL;
	return m_textureSlot[m_TexID[textype]]->GetTexPointer();
}
