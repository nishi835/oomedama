/*==============================================================================

pointPlayerのヘッダー [pointPlayer.h]
作成者 : 中西　祐介
作成日 :
--------------------------------------------------------------------------------
■Update :
==============================================================================*/
#ifndef _POINT_PLAYER_H_
#define _POINT_PLAYER_H_

/*------------------------------------------------------------------------------
　ヘッダファイル
 ------------------------------------------------------------------------------*/
#include "scene2D.h"
#include "textureManager.h"

 /*------------------------------------------------------------------------------
 　マクロ定義
  ------------------------------------------------------------------------------*/
#define POINTPLAYER_TEXTURENAME "data/TEXTURE/fade00.png"

  /*------------------------------------------------------------------------------
  　クラス
   ------------------------------------------------------------------------------*/
class CPointPlayer : public CScene2D
{
public:
	CPointPlayer(int Priority) : CScene2D(Priority) {};
	~CPointPlayer();

	void Init(void);
	void Uninit(void)override;
	void Update(void)override;
	void Draw(void)override;

	static CPointPlayer* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float alpha, char* filePass, CTextureManager::TEXTYPE textype);

private:

};

#endif