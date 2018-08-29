/*==============================================================================

    gangのヘッダー [gang.h]
                                                       作成者 : 中西　祐介
                                                       作成日 : 
--------------------------------------------------------------------------------
    ■Update : 
==============================================================================*/
#ifndef _GANG_H_
#define _GANG_H_

/*------------------------------------------------------------------------------
  　ヘッダファイル
------------------------------------------------------------------------------*/
#include "scene2D.h"

/*------------------------------------------------------------------------------
  　マクロ定義
------------------------------------------------------------------------------*/
#define GANG_TEXTURENAME "data/TEXTURE/gang02.png"

/*------------------------------------------------------------------------------
  　クラス
------------------------------------------------------------------------------*/
class CGang : public CScene2D
{
public:
	CGang( int Priority ) : CScene2D( Priority ){};
	~CGang();
	
	void Init( D3DXVECTOR3 pos, D3DXVECTOR3 size, char* filepass );
	void Uninit( void );
	void Update( void );
	void Draw( void );

	static CGang* Create( D3DXVECTOR3 pos, D3DXVECTOR3 size, char* filepass);

private:

};

#endif