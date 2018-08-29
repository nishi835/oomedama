/*==============================================================================

    textureManager�̃w�b�_ [textureManager.h]
                                                       �쐬�� : �����@�S��
                                                       �쐬�� : 
--------------------------------------------------------------------------------
    ��Update : 
==============================================================================*/
#ifndef _TEXTUREMANAGER_H_
#define _TEXTUREMANAGER_H_

/*------------------------------------------------------------------------------
    �w�b�_�t�@�C��
------------------------------------------------------------------------------*/
#include "main.h"
#include "texture.h"

/*------------------------------------------------------------------------------
  �@�N���X
------------------------------------------------------------------------------*/
class CTextureManager
{
public:
	typedef enum
	{
		TEXTYPE_NONE = 0,
		TEXTYPE_PARTICLE,
		TEXTYPE_PLAYER_PARTICLE,
		TEXTYPE_BULLET,
		TEXTYPE_ENEMY_BULLET
	}TEXTYPE;

	CTextureManager();
	~CTextureManager();

	void Init( void );
	void Uninit( void );

	static int LoadTexture( char* filepass, TEXTYPE textype);
	static LPDIRECT3DTEXTURE9 BindTexture( int texID );
	static LPDIRECT3DTEXTURE9 BindTexture(TEXTYPE textype);

	// �Q�b�^�[
	static int GetTexID(TEXTYPE texttype) { return m_TexID[texttype]; }

private:	

	static CTexture* m_textureSlot[ 256 ];
	static int m_TexID[256];
};

#endif