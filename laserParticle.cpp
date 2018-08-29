/*==============================================================================

particle�̏��� [particle.cpp]
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
#include "renderer.h"
#include "laserParticle.h"
#include "camera.h"
#include "light.h"

/*------------------------------------------------------------------------------
 �@�}�N����`
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
  �f�X�g���N�^
------------------------------------------------------------------------------*/
CLaserParticle::~CLaserParticle()
{
}

/*------------------------------------------------------------------------------
�@������
------------------------------------------------------------------------------*/
void CLaserParticle::Init(void)
{
	// �r���{�[�h�̏�����
	CBillboard::Init();

	// �I�u�W�F�N�g�^�C�v�̐ݒ�
	SetObjType(OBJTYPE_NONE);
}

/*------------------------------------------------------------------------------
�@�I������
------------------------------------------------------------------------------*/
void CLaserParticle::Uninit(void)
{
	CBillboard::Uninit();
	CScene::SetDelete();
}

/*------------------------------------------------------------------------------
�@�X�V
------------------------------------------------------------------------------*/
void CLaserParticle::Update(void)
{
	if (m_use)
	{
		m_pos += m_velocity;
		CBillboard::Update();
	}

	m_life--;
	if (m_life <= 0)
	{
		SetUse(false);
	}
	
	char str[128];
	//sprintf(str, "LaserParticle size.x = %.5f\n", m_size.x);
	//CDebug::AddText(str);
}

/*------------------------------------------------------------------------------
�@�|���S���`�揈��
------------------------------------------------------------------------------*/
void CLaserParticle::Draw(void)
{
	if (m_use)
	{
		// �f�o�C�X�̃|�C���^�擾
		LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

		// ���Z�����ɐ؂�ւ�
		pDevice->SetRenderState(D3DRS_DESTBLEND,	// �ݒ薼(�C���f�b�N�X)	D3DRS_DESTBLEND�F�w�i�̃A���t�@�ݒ�
			D3DBLEND_ONE);		// �ݒ�l

		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);	// �y�o�b�t�@���I�t

		CBillboard::Draw();

		// ��Z�����ɐ؂�ւ�
		pDevice->SetRenderState(D3DRS_DESTBLEND,		// �ݒ薼(�C���f�b�N�X)	D3DRS_DESTBLEND�F�w�i�̃A���t�@�ݒ�
			D3DBLEND_INVSRCALPHA);	// �ݒ�l	D3DBLEND_INVSRCALPHA�F�P�|��

		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);	// �y�o�b�t�@�����ɖ߂�
	}
}

/*------------------------------------------------------------------------------
�@�쐬
------------------------------------------------------------------------------*/
CLaserParticle* CLaserParticle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 velocity, float alpha, int life, char* filePass, CTextureManager::TEXTYPE textype)
{
	CLaserParticle* pParticle = new CLaserParticle(CScene::PRIORITY_BILLBOARD);

	// ������
	pParticle->SetPos(pos);
	pParticle->SetSize(size);
	pParticle->SetAlpha(alpha);
	pParticle->SetLife(life);
	pParticle->SetUse(false);

	// �e�N�X�`��ID�̎擾
	pParticle->m_TexID = CTextureManager::GetTexID(textype);

	pParticle->Init();

	return pParticle;
}

