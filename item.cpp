/*==============================================================================

weed�̏��� [weed.cpp]
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
#include "item.h"
#include "camera.h"
#include "light.h"

/*------------------------------------------------------------------------------
 �@�}�N����`
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
  �@�f�X�g���N�^
------------------------------------------------------------------------------*/
CItem::~CItem()
{
}

/*------------------------------------------------------------------------------
�@������
------------------------------------------------------------------------------*/
void CItem::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, float velY)
{
	// �p�����[�^�ݒ�
	m_size = size;
	m_pos = pos;
	m_velocityY = velY;

	// �r���{�[�h�̏�����
	CBillboard::Init();

	// �I�u�W�F�N�g�^�C�v�̐ݒ�
	SetObjType(OBJTYPE_MESHFIELD);
}

/*------------------------------------------------------------------------------
�@�I������
------------------------------------------------------------------------------*/
void CItem::Uninit(void)
{
	CBillboard::Uninit();
	CScene::SetDelete();
}

/*------------------------------------------------------------------------------
�@�X�V
------------------------------------------------------------------------------*/
void CItem::Update(void)
{
	// �ړ�
	m_velocityY -= 0.1f;
	m_pos.y += m_velocityY;

	// �����ݒ�	
	float tempH = CModeGame::GetMeshField()->GetHeight(m_pos);
	if (m_pos.y < tempH) { m_pos.y = tempH; }
}

/*------------------------------------------------------------------------------
�@�|���S���`�揈��
------------------------------------------------------------------------------*/
void CItem::Draw(void)
{
	CBillboard::Draw();
}

/*------------------------------------------------------------------------------
�@�쐬
------------------------------------------------------------------------------*/
CItem* CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float velY, float alpha, char* filePass, CTextureManager::TEXTYPE textype)
{
	CItem* pItem = new CItem(2);
	pItem->SetTexID(CTextureManager::LoadTexture(filePass, textype));
	pItem->Init(pos, size, velY);
	return pItem;
}
