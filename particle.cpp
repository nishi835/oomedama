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
#include "particle.h"
#include "camera.h"
#include "light.h"

/*------------------------------------------------------------------------------
 �@�}�N����`
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
  �@�f�X�g���N�^
------------------------------------------------------------------------------*/
CParticle::~CParticle()
{
}

/*------------------------------------------------------------------------------
�@������
------------------------------------------------------------------------------*/
void CParticle::Init(void)
{
	// �p�����[�^������
	m_acceleration = 1.0f;
	m_alphaDecay = 1.0f;

	// �r���{�[�h�̏�����
	CBillboard::Init();

	// �I�u�W�F�N�g�^�C�v�̐ݒ�
	SetObjType(OBJTYPE_NONE);
}

/*------------------------------------------------------------------------------
�@�I������
------------------------------------------------------------------------------*/
void CParticle::Uninit(void)
{
	CBillboard::Uninit();
	//CScene::Release();
	CScene::SetDelete();
}

/*------------------------------------------------------------------------------
�@�X�V
------------------------------------------------------------------------------*/
void CParticle::Update(void)
{
	if (m_use)
	{
		m_velocity *= m_acceleration;
		m_color.a *= m_alphaDecay;
		m_alpha = m_color.a;
		m_pos += m_velocity;
	}

	m_life--;
	if (m_life <= 0)
	{
		SetUse(false);
	}

	CBillboard::Update();
}

/*------------------------------------------------------------------------------
�@�|���S���`�揈��
------------------------------------------------------------------------------*/
void CParticle::Draw(void)
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
CParticle* CParticle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 velocity, D3DXCOLOR color, int life, CTextureManager::TEXTYPE textype)
{
	CParticle* pParticle = new CParticle(CScene::PRIORITY_BILLBOARD);

	// ������
	pParticle->SetPos(pos);
	pParticle->SetSize(size);
	pParticle->SetVelocity(velocity);
	pParticle->SetColor(D3DXCOLOR(255, 255, 255, 128));
	pParticle->SetLife(life);
	pParticle->SetUse(false);

	// �e�N�X�`��ID�̎擾
	pParticle->m_TexID = CTextureManager::GetTexID(textype);

	pParticle->Init();

	return pParticle;
}

