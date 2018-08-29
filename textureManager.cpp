/*==============================================================================

    textureManagerの処理 [textureManager.cpp]
                                                       作成者 : 中西　祐介
                                                       作成日 :
--------------------------------------------------------------------------------
    ■Update : 
==============================================================================*/

/*------------------------------------------------------------------------------
  　ヘッダファイル
------------------------------------------------------------------------------*/
#include "textureManager.h"

/*------------------------------------------------------------------------------
  　マクロ
------------------------------------------------------------------------------*/
#define TEXSLOT_NUM (30) // テクスチャスロットの最大数

/*------------------------------------------------------------------------------
  　静的メンバ変数
------------------------------------------------------------------------------*/
CTexture* CTextureManager::m_textureSlot[ 256 ] = {};
int CTextureManager::m_TexID[256] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CTextureManager::CTextureManager( void )
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CTextureManager::~CTextureManager()
{
}

//=============================================================================
// 初期化
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
// 終了処理
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
// テクスチャのロード
//=============================================================================
int CTextureManager::LoadTexture( char* filepass, CTextureManager::TEXTYPE textype )
{
	if ( filepass == NULL ) return - 1;
	for ( int IDNum = 0; IDNum < TEXSLOT_NUM; IDNum++ )
	{
		if ( m_textureSlot[ IDNum ] != NULL ) // スロットがすでに使用されている場合
		{
			const char* slotFilepass = m_textureSlot[ IDNum ]->GetTexpass();   // ファイルパス取得
			int valueStrcmp = strcmp( slotFilepass, filepass );
			if ( valueStrcmp == 0 )
			{
				m_TexID[textype] = IDNum;
				return IDNum;
			}
			else continue;
		}

		if ( m_textureSlot[ IDNum ] == NULL ) // スロットに空があったらテクスチャを入れる
		{
			m_textureSlot[ IDNum ] = new CTexture( filepass );
			m_TexID[textype] = IDNum;
 			return IDNum;
		}
	}

	// 例外処理
	MessageBox( NULL, "使用できるテクスチャスロットがない", "エラー", MB_OK | MB_ICONHAND );
	return - 1;
}

//=============================================================================
// テクスチャのバインド
//=============================================================================
// IDによる指定
LPDIRECT3DTEXTURE9 CTextureManager::BindTexture( int IDNum )
{
	if ( IDNum == - 1 ) return NULL;
	if ( m_textureSlot[ IDNum ] == NULL ) return NULL;
	return m_textureSlot[ IDNum ]->GetTexPointer();
}

// タイプによる指定
LPDIRECT3DTEXTURE9 CTextureManager::BindTexture(CTextureManager::TEXTYPE textype)
{
	if (m_textureSlot[m_TexID[textype]] == NULL) return NULL;
	return m_textureSlot[m_TexID[textype]]->GetTexPointer();
}
