/*==============================================================================

    player�̏��� [player.cpp]
                                                       �쐬�� : �����@�S��
                                                       �쐬�� : 
--------------------------------------------------------------------------------
    ��Update : 
==============================================================================*/

/*------------------------------------------------------------------------------
  �@�w�b�_�t�@�C��
------------------------------------------------------------------------------*/
#include "main.h"
#include "manager.h"
#include "modeGame.h"
#include "renderer.h"
#include "camera.h"
#include "light.h"
#include "player.h"
#include "bullet.h"
#include "sceneModel.h"
#include "collision.h"

/*------------------------------------------------------------------------------
  �@�}�N����`
------------------------------------------------------------------------------*/
#define PLAYER_ACCELERATION (0.15f)  // �ړ��̉����x
#define PLAYER_NUM_TEX (2)

/*------------------------------------------------------------------------------
  �@�f�X�g���N�^
------------------------------------------------------------------------------*/
CPlayer::~CPlayer()
{
}

/*------------------------------------------------------------------------------
  �@������
------------------------------------------------------------------------------*/
void CPlayer::Init(void)
{
	// �p�����[�^������
	m_timer = 0; 
	m_parallelVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_speed = PLAYER_SPEED;
	m_hit = false;
	m_doDraw = true;

	// �V�[�����f���̏�����
	CSceneModel::Init();

	// �ړ��x�N�g���̐ݒ�
	m_velocity.x = cosf(m_rotFai) * PLAYER_ACCELERATION * sinf(m_rotThe);
	m_velocity.y = sinf(m_rotFai) * PLAYER_ACCELERATION;
	m_velocity.z = cosf(m_rotFai) * PLAYER_ACCELERATION * cosf(m_rotThe);

	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	LPD3DXMESH pCloneMesh;
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;
	VERTEX_3D* pVertex;

	// ���b�V���̎擾
	m_pMeshModel->CloneMeshFVF(D3DXMESH_MANAGED, FVF_VERTEX_3D, pDevice, &pCloneMesh);

	// ���_���̃J�E���g
	int count = pCloneMesh->GetNumVertices();

	// ���_�o�b�t�@�擾
	pCloneMesh->GetVertexBuffer(&pVtxBuff);
	
	// ���_�o�b�t�@�����b�N
	VERTEX_3D* vertex;
	pVtxBuff->Lock(0, 0, (void**)&vertex, 0);

	// ���a�̎擾
	D3DXVECTOR3 temp;
	float len = 0;
	m_radius = 0;
	for (int i = 0; i < count; i++)
	{
		temp = vertex[i].pos;
		len = D3DXVec3Length(&temp);
		m_radius = max(len, m_radius);
	}

	// �I�u�W�F�N�g�^�C�v�̐ݒ�
	SetObjType( OBJTYPE_PLAYER );
}

/*------------------------------------------------------------------------------
  �@�I������
------------------------------------------------------------------------------*/
void CPlayer::Uninit( void )
{
	CScene::Uninit();
}

/*------------------------------------------------------------------------------
  �@�X�V
------------------------------------------------------------------------------*/
void CPlayer::Update(void)
{
	// �ړ��X�s�[�h����
	if (m_speed > 1.5f)
	{
		m_speed = 1.5f;
	}

	if (m_speed < 0.0001f)
	{
		m_speed = 0.0001f;
		m_move = false;
	}

	// �ړ��x�N�g���̐ݒ�
	m_velocity.x = cosf(m_rotFai) * m_speed * sinf(m_rotThe);
	m_velocity.y = sinf(m_rotFai) * m_speed;
	m_velocity.z = cosf(m_rotFai) * m_speed * cosf(m_rotThe);
	
	// �ړ�
	if (m_move) 
	{
		m_pos += m_velocity; 
		m_pos += m_parallelVec;
	}

	m_parallelVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = true;

	// �����ݒ�	
	float tempH = CModeGame::GetMeshField()->GetHeight(m_pos);
	if (m_pos.y < tempH) { m_pos.y = tempH; }

	if (m_timer > 60)
	{
		m_hit = false;
	}

	// �^�C�}�[�X�V
	m_timer++;

	// �f�o�b�O�\��
	char str[128];
	sprintf(str, "Player pos.x = %.5f\n", m_pos.x);
	CDebug::AddText(str);
}

/*------------------------------------------------------------------------------
  �@�|���S���`�揈��
------------------------------------------------------------------------------*/
void CPlayer::Draw( void )
{	
	if (m_doDraw == false) return;

	CSceneModel::Draw();
}

/*------------------------------------------------------------------------------
  �@�쐬
------------------------------------------------------------------------------*/
CPlayer* CPlayer::Create( D3DXVECTOR3 pos,  D3DXVECTOR3 velocity, float rotThe, float rotFai, int energy, int hitpoint, char* filePass)
{
	CPlayer* pPlayer = new CPlayer(CScene::PRIORITY_3D);

	pPlayer->SetPos(pos);
	pPlayer->SetVelocity(velocity);
	pPlayer->SetRotThe(rotThe);
	pPlayer->SetRotFai(rotFai);	
	pPlayer->SetEnergy(energy);
	pPlayer->SetHitpoint(hitpoint);
	pPlayer->SetFilePass(filePass);

	pPlayer->Init();
	return pPlayer;
}

