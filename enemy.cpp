/*==============================================================================

    enemy�̏��� [enemy.cpp]
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
#include <time.h>

/*------------------------------------------------------------------------------
  �@�}�N����`
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
  �@�f�X�g���N�^
------------------------------------------------------------------------------*/
CEnemy::~CEnemy()
{
}

/*------------------------------------------------------------------------------
  �@������
------------------------------------------------------------------------------*/
void CEnemy::Init()
{	
	// ������
	m_rockon = false;
	m_timer = 0;
	m_velocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotX = 0.0f;
	m_moveCount = 0.0f;
	m_sign = 1.0f;

	// ����������
	srand(unsigned(time(0)));

	// �r���{�[�h�̏�����
	CBillboard::Init();

	// �I�u�W�F�N�g�^�C�v�̐ݒ�
	SetObjType( OBJTYPE_MESHFIELD );
}

/*------------------------------------------------------------------------------
  �@�I������
------------------------------------------------------------------------------*/
void CEnemy::Uninit( void )
{
	CBillboard::Uninit();
	CScene::SetDelete();
}

/*------------------------------------------------------------------------------
  �@�X�V
------------------------------------------------------------------------------*/
void CEnemy::Update( void )
{
	m_timer++;

	// �n�ʂ̍����擾
	int height = CModeGame::GetMeshField()->GetHeight(m_pos);

	// �ړ�
	switch (m_moveType)
	{
	case ENEMYMOVETYPE_UPDOWN:
		if ((m_pos.y > 50.0f) || (m_pos.y <= height))
		{
			m_sign *= -1.0f;
		}
		m_velocity.y = ENEMY_MOVE_SPEED * m_sign;
		
		break;

	case ENEMYMOVETYPE_CIRCLE:
		m_rotX += 0.01f;
		m_velocity.x = cosf(m_rotX) * ENEMY_MOVE_SPEED;
		m_velocity.z = sinf(m_rotX) * ENEMY_MOVE_SPEED;
		break;

	case ENEMYMOVETYPE_RANDOM:
		if (m_moveCount == 0.0f)
		{
			m_velocity.x = rand() % 10 - 5;
			m_velocity.y = rand() % 10 - 5;
			m_velocity.z = rand() % 10 - 5;

			D3DXVec3Normalize(&m_velocity, &m_velocity);
		}

		m_moveCount += D3DXVec3Length(&m_velocity);

		if (m_moveCount > 50.0f)
		{
			m_moveCount = 0.0f;
		}

		break;

	case ENEMYMOVETYPE_HOMING:
		D3DXVECTOR3 vecPE = CModeGame::GetPlayer()->GetPos() - m_pos;
		D3DXVec3Normalize(&vecPE, &vecPE);

		m_velocity = vecPE * ENEMY_MOVE_SPEED * 0.5f;

		break;
	}

	// �ړ�
	m_pos += m_velocity;

	// ��������
	if (m_pos.y < height)
	{
		m_pos.y = height;
	}
}

/*------------------------------------------------------------------------------
  �@�`�揈��
------------------------------------------------------------------------------*/
void CEnemy::Draw( void )
{		
	CBillboard::Draw();
}

/*------------------------------------------------------------------------------
  �@�쐬
------------------------------------------------------------------------------*/
CEnemy* CEnemy::Create( D3DXVECTOR3 pos, D3DXVECTOR3 size, ENEMYTYPE type, ENEMYMOVETYPE moveType, char* filePass)
{
	CEnemy* pEnemy = new CEnemy(CScene::PRIORITY_BILLBOARD);

	pEnemy->SetPos(pos);
	pEnemy->SetSize(size);
	pEnemy->SetType(type);
	pEnemy->SetMoveType(moveType);

	// �e�N�X�`���̃��[�h
	pEnemy->SetTexID(CTextureManager::LoadTexture(filePass, CTextureManager::TEXTYPE_NONE));
	pEnemy->Init();

	return pEnemy;
}

