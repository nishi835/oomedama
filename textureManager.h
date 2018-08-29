/*==============================================================================

    textureManagerのヘッダ [textureManager.h]
                                                       作成者 : 中西　祐介
                                                       作成日 : 
--------------------------------------------------------------------------------
    ■Update : 
==============================================================================*/
#ifndef _TEXTUREMANAGER_H_
#define _TEXTUREMANAGER_H_

/*------------------------------------------------------------------------------
    ヘッダファイル
------------------------------------------------------------------------------*/
#include "main.h"
#include "texture.h"

/*------------------------------------------------------------------------------
  　クラス
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

	// ゲッター
	static int GetTexID(TEXTYPE texttype) { return m_TexID[texttype]; }

private:	

	static CTexture* m_textureSlot[ 256 ];
	static int m_TexID[256];
};

#endif