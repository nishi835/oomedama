/*==============================================================================

reticle�̃w�b�_�[ [reticle.h]
�쐬�� : �����@�S��
�쐬�� :
--------------------------------------------------------------------------------
��Update :
==============================================================================*/
#ifndef _RETICLE_H_
#define _RETICLE_H_

//------------------------------------------------------------------------------
//  �w�b�_�t�@�C��
//------------------------------------------------------------------------------
#include "billboard.h"

//------------------------------------------------------------------------------
//  �}�N����`
//------------------------------------------------------------------------------
#define RETICLE001_TEXTURENAME "data/TEXTURE/reticle.png"
#define MAX_RETICLE (1)
#define RETICLE_SIZE_X (7.0f)
#define RETICLE_SIZE_Y (7.0f)
#define RETICLE_DISTANCE_FROM_PLAYER (150.0f)

//------------------------------------------------------------------------------
//  �N���X
//------------------------------------------------------------------------------
class CReticle : public CBillboard
{
public:
	CReticle(int Priority) : CBillboard(Priority) {};
	~CReticle();

	void Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �Q�b�^�[

	// �Z�b�^�[

	static CReticle* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, char* filePass);

private:
	int m_rockonID;

};

#endif
