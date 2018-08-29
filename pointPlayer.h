/*==============================================================================

pointPlayer�̃w�b�_�[ [pointPlayer.h]
�쐬�� : �����@�S��
�쐬�� :
--------------------------------------------------------------------------------
��Update :
==============================================================================*/
#ifndef _POINT_PLAYER_H_
#define _POINT_PLAYER_H_

/*------------------------------------------------------------------------------
�@�w�b�_�t�@�C��
 ------------------------------------------------------------------------------*/
#include "scene2D.h"
#include "textureManager.h"

 /*------------------------------------------------------------------------------
 �@�}�N����`
  ------------------------------------------------------------------------------*/
#define POINTPLAYER_TEXTURENAME "data/TEXTURE/fade00.png"

  /*------------------------------------------------------------------------------
  �@�N���X
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