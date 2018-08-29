/*==============================================================================

background�̃w�b�_�[ [background.h]
�쐬�� : �����@�S��
�쐬�� :
--------------------------------------------------------------------------------
��Update :
==============================================================================*/
#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

/*------------------------------------------------------------------------------
�@�w�b�_�t�@�C��
------------------------------------------------------------------------------*/
#include "scene2D.h"
#include "textureManager.h"

/*------------------------------------------------------------------------------
  �}�N����`
------------------------------------------------------------------------------*/
#define TITLE001_TEXTURENAME "data/TEXTURE/title.png"
#define RESULT_TEXTURENAME "data/TEXTURE/result.png"

/*------------------------------------------------------------------------------
�@�N���X
------------------------------------------------------------------------------*/
class CBackground : public CScene2D
{
public:
	CBackground(int Priority) : CScene2D(Priority) {};
	~CBackground() {};

	void Init(void);
	void Uninit(void)override;
	void Update(void)override;
	void Draw(void)override;

	// �Z�b�^�[

	// �Q�b�^�[

	// ���̑��̃��\�b�h
	static CBackground* CBackground::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float alpha, char* filePass);

private:
};

#endif