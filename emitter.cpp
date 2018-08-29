/*==============================================================================

emitter�̏��� [emitter.cpp]
�쐬�� : �����@�S��
�쐬�� :
--------------------------------------------------------------------------------
��Update :
==============================================================================*/

/*------------------------------------------------------------------------------
�@�w�b�_�t�@�C��
------------------------------------------------------------------------------*/
#include "main.h"
#include "modeGame.h"
#include "textureManager.h"
#include "particle.h"
#include <time.h>

/*------------------------------------------------------------------------------
 �@�}�N����`
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
�@������
------------------------------------------------------------------------------*/
void CEmitter::Init(void)
{
	srand((unsigned)time(0));	// �����ݒ�
}

/*------------------------------------------------------------------------------
�@�I������
------------------------------------------------------------------------------*/
void CEmitter::Uninit(void)
{
}

/*------------------------------------------------------------------------------
�@�X�V
------------------------------------------------------------------------------*/
void CEmitter::Update(void)
{
	m_life--;

	if (m_life <= 0)
	{
		SetDoUninit(true);
	}
}

/*------------------------------------------------------------------------------
�@�|���S���`�揈��
------------------------------------------------------------------------------*/
void CEmitter::Draw(void)
{
}

/*------------------------------------------------------------------------------
�@�쐬
------------------------------------------------------------------------------*/
CEmitter* CEmitter::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& sizeParticle, const float& speedParticle, const D3DXCOLOR& colorParticle, const int& emitPerFrame, const int& lifeParticle, const int& life, const EMITTERTYPE& type)
{
	CEmitter* pEmitter = new CEmitter();

	pEmitter->SetPos(pos);
	pEmitter->SetSizeParticle(sizeParticle);
	pEmitter->SetSpeedParticle(speedParticle);
	pEmitter->SetColorParticle(colorParticle);
	pEmitter->SetEmitPerFrame(emitPerFrame);
	pEmitter->SetLifeParticle(lifeParticle);
	pEmitter->SetLife(life);
	pEmitter->SetType(type);
	pEmitter->SetDoUninit(false);

	pEmitter->Init();

	return pEmitter;
}
