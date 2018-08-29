/*==============================================================================

bullet�̏��� [bullet.cpp]
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
#include "bullet.h"
#include "camera.h"
#include "light.h"

/*------------------------------------------------------------------------------
�@�}�N����`
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
�@�f�X�g���N�^
------------------------------------------------------------------------------*/
CBullet::~CBullet()
{
}

/*------------------------------------------------------------------------------
�@������
------------------------------------------------------------------------------*/
void CBullet::Init(void)
{
	// �r���{�[�h�̏�����
	CBillboard::Init();

	// �I�u�W�F�N�g�^�C�v�̐ݒ�
	SetObjType(OBJTYPE_NONE);
}

/*------------------------------------------------------------------------------
�@�I������
------------------------------------------------------------------------------*/
void CBullet::Uninit(void)
{
	CBillboard::Uninit();
	CScene::SetDelete();
}

/*------------------------------------------------------------------------------
�@�X�V
 ------------------------------------------------------------------------------*/
void CBullet::Update(void)
{
	if (m_use)
	{
		m_pos += m_velocity;
	}
}

/*------------------------------------------------------------------------------
�@�|���S���`�揈��
 ------------------------------------------------------------------------------*/
void CBullet::Draw(void)
{
	if (m_use)
	{
		CBillboard::Draw();
	}
}

/*------------------------------------------------------------------------------
�@�쐬
 ------------------------------------------------------------------------------*/
CBullet* CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 velocity, bool use,  char* filePass,  CTextureManager::TEXTYPE textype)
{
	CBullet* pBullet = new CBullet(CScene::PRIORITY_BILLBOARD);

	// ������
	pBullet->SetPos(pos);
	pBullet->SetSize(size);
	pBullet->SetVelocity(velocity);
	pBullet->SetDeltaRot(0.0f);
	pBullet->SetUse(use);

	// �e�N�X�`��ID�̐ݒ�
	pBullet->m_TexID = CTextureManager::GetTexID(textype);
	pBullet->Init();

	return pBullet;
}
