/*==============================================================================

laserEmitter�̏��� [laserEmitter.cpp]
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
#include "laserEmitter.h"
#include "particle.h"
#include <stdio.h>

/*------------------------------------------------------------------------------
 �@�}�N����`
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
  �@������
------------------------------------------------------------------------------*/
void CLaserEmitter::Init(void)
{
}

/*------------------------------------------------------------------------------
�@�I������
------------------------------------------------------------------------------*/
void CLaserEmitter::Uninit(void)
{
	CScene::SetDelete();
}

/*------------------------------------------------------------------------------
�@�X�V
------------------------------------------------------------------------------*/
void CLaserEmitter::Update(void)
{
	// �ړ�
	m_pos += m_velocity;

	// �p�[�e�B�N���̍쐬
	CLaserParticle** pLaserParticle = CModeGame::GetLaserParticle();

	for (int j = 0; j < MAX_PARTICLE; j++)
	{
		if (pLaserParticle == NULL) break;

		if (pLaserParticle[j]->GetUse() == false)
		{
			pLaserParticle[j]->SetPos(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z));
			pLaserParticle[j]->SetSize(m_sizeParticle);
			pLaserParticle[j]->SetVelocity(D3DXVECTOR3(0.0f, 0.0f, 0.0f)/*m_velocityParticle*/);
			pLaserParticle[j]->SetColor(m_colorParticle);
			pLaserParticle[j]->SetLife(m_lifeParticle);
			pLaserParticle[j]->SetUse(true);

			break;
		}
	}

	m_life--;

	if (m_life <= 0)
	{
		SetDoUninit(true);
	}

	char str[128];
	sprintf(str, "LaserEmitter pos.x = %.5f\n", m_pos.x);
	CDebug::AddText(str);
}

/*------------------------------------------------------------------------------
�@�`�揈��
 ------------------------------------------------------------------------------*/
void CLaserEmitter::Draw(void)
{
}

/*------------------------------------------------------------------------------
�@�쐬
 ------------------------------------------------------------------------------*/
CLaserEmitter* CLaserEmitter::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& velocity, const D3DXVECTOR3& velocityParticle, const D3DXVECTOR3& sizeParticle, const D3DXCOLOR& colorParticle, const int& lifeParticle, const int& life, const char* filePass)
{
	CLaserEmitter* pLaserEmitter = new CLaserEmitter(CScene::PRIORITY_BILLBOARD);

	pLaserEmitter->SetPos(pos);
	pLaserEmitter->SetVelocity(velocity);
	pLaserEmitter->SetSizeParticle(sizeParticle);
	pLaserEmitter->SetColorParticle(colorParticle);
	pLaserEmitter->SetLifeParticle(lifeParticle);
	pLaserEmitter->SetLife(life);
	pLaserEmitter->SetDoUninit(false);

	pLaserEmitter->Init();

	return pLaserEmitter;
}
