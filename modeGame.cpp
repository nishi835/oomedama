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
#include "sound.h"
#include "textureManager.h"
#include "renderer.h"
#include "filepassHeader.h"
#include "modeGame.h"
#include "modeResult.h"
#include "camera.h"
#include "light.h"
#include "score.h"
#include "collision.h"
#include "emitter.h"
#include "particle.h"
#include "sceneModel.h"
#include "player.h"
#include "meshField.h"
#include "meshDome.h"
#include "weed.h"
#include "enemy.h"
#include "gang.h"
#include "debug.h"
#include "textBox.h"
#include "textBox3D.h"
#include "pointPlayer.h"
#include "energyGauge.h"
#include "hitpointGauge.h"
#include "item.h"
#include "tombstone.h"
#include "reticle.h"
#include <vector>
#include <algorithm>
#include <math.h>
#include <time.h>
#include <stdio.h>

/*------------------------------------------------------------------------------
  �@�ÓI�����o�ϐ�
------------------------------------------------------------------------------*/
// �C���t���n
CLight* CModeGame::m_Light = NULL;
CCamera* CModeGame::m_Camera = NULL;
CDebug* CModeGame::m_Debug = NULL;
// �I�u�W�F�N�g
CMeshField* CModeGame::m_MeshField = NULL;
CMeshDome* CModeGame::m_MeshDome = NULL;
CPlayer* CModeGame::m_Player = NULL;
CWeed* CModeGame::m_Weed[MAX_WEED] = {};
CEnemy* CModeGame::m_Enemy[MAX_ENEMY] = {};
CBullet* CModeGame::m_Bullet[MAX_BULLET] = {};
CBullet* CModeGame::m_EnemyBullet[MAX_ENEMY_BULLET] = {};
CHomingBullet* CModeGame::m_HomingBullet[MAX_HOMING_BULLET] = {};
CItem* CModeGame::m_Item[MAX_ITEM] = {};
CTombstone* CModeGame::m_Tombstone[MAX_TOMBSTONE] = {};
std::vector<CRockon*> CModeGame::m_Rockon = {};
std::vector<CMediator*> CModeGame::m_Mediator = {};
// UI
CScore* CModeGame::m_Score = NULL;
CScore* CModeGame::m_Timer = NULL;
CTextBox* CModeGame::m_StartText = NULL;
CTextBox* CModeGame::m_ClearText = NULL;
CTextBox* CModeGame::m_GameOverText = NULL;
CTextBox3D* CModeGame::m_Nirvana[MAX_NIRVANA] = {};
// ���̑�
CParticle* CModeGame::m_Particle[MAX_PARTICLE] = {};
CParticle* CModeGame::m_HitParticle[MAX_PARTICLE] = {};
CEmitter* CModeGame::m_Emitter[MAX_EMITTER] = {};
CLaserEmitter* CModeGame::m_LaserEmitter = NULL;
CLaserParticle* CModeGame::m_LaserParticle[MAX_PARTICLE] = {};
POINT CModeGame::m_cursorPos;

/*------------------------------------------------------------------------------
  �@�f�X�g���N�^
------------------------------------------------------------------------------*/
CModeGame::~CModeGame()
{
}

/*------------------------------------------------------------------------------
  �@������
------------------------------------------------------------------------------*/
void CModeGame::Init(void)
{
	// ����������
	srand((unsigned)time(0));

	// �ϐ�������
	m_timer = 0;
	m_gameTimer = 0;
	m_step = STEP_1;

	// �e�N�X�`���ǂݍ��� 

	CTextureManager::LoadTexture(PARTICLE001_TEXTURENAME, CTextureManager::TEXTYPE_PARTICLE);
	CTextureManager::LoadTexture(BULLET001_TEXTURENAME, CTextureManager::TEXTYPE_BULLET);
	CTextureManager::LoadTexture(ENEMYBULLET_TEXTURENAME, CTextureManager::TEXTYPE_ENEMY_BULLET);
	CTextureManager::LoadTexture(ENEMYBULLET_TEXTURENAME, CTextureManager::TEXTYPE_PLAYER_PARTICLE);

	// �C���X�^���X���� 

	// �C���t���n //////////////////////////////////////////////////

	// �J����
	m_Camera = CCamera::Create();

	// ���C�g
	m_Light = CLight::Create();

	// �I�u�W�F�N�g /////////////////////////////////////////////////////

	// �t�B�[���h
	m_MeshField = CMeshField::Create();
	m_MeshDome  = CMeshDome::Create();

	// ��
	CWeed::Create(D3DXVECTOR3(3.0f, 0.0f, -3.0f), D3DXVECTOR3(8.0f, 32.0f, 0.0f), 0);

	// �v���C���[
	m_Player  = CPlayer::Create(D3DXVECTOR3(30.0f, 10.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 100, 100, PLAYER_FILE_NAME);
	
	// �Ə�
	CReticle::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(RETICLE_SIZE_X, RETICLE_SIZE_Y, 0.0f), RETICLE001_TEXTURENAME);

	// �G�l�~�[
	m_Enemy[0] = CEnemy::Create(D3DXVECTOR3(0.0f, 5.0f, 0.0f),    D3DXVECTOR3(ENEMY_SIZE_MIDDLE_X, ENEMY_SIZE_MIDDLE_Y, 0.0f), CEnemy::ENEMYTYPE_MIDDLE, CEnemy::ENEMYMOVETYPE_UPDOWN, ENEMY001_TEXTURENAME);
	m_Enemy[1] = CEnemy::Create(D3DXVECTOR3(20.0f, 15.0f, 80.0f), D3DXVECTOR3(ENEMY_SIZE_LARGE_X, ENEMY_SIZE_LARGE_Y, 0.0f), CEnemy::ENEMYTYPE_LARGE, CEnemy::ENEMYMOVETYPE_CIRCLE, ENEMY001_TEXTURENAME);
	m_Enemy[2] = CEnemy::Create(D3DXVECTOR3(40.0f, 25.0f, 60.0f), D3DXVECTOR3(ENEMY_SIZE_MIDDLE_X, ENEMY_SIZE_MIDDLE_Y, 0.0f), CEnemy::ENEMYTYPE_MIDDLE, CEnemy::ENEMYMOVETYPE_RANDOM, ENEMY001_TEXTURENAME);
	m_Enemy[3] = CEnemy::Create(D3DXVECTOR3(60.0f, 15.0f, 40.0f), D3DXVECTOR3(ENEMY_SIZE_SMALL_X, ENEMY_SIZE_SMALL_Y, 0.0f), CEnemy::ENEMYTYPE_SMALL, CEnemy::ENEMYMOVETYPE_HOMING, ENEMY001_TEXTURENAME);
	m_Enemy[4] = CEnemy::Create(D3DXVECTOR3(80.0f, 25.0f, 20.0f), D3DXVECTOR3(ENEMY_SIZE_SMALL_X, ENEMY_SIZE_SMALL_Y, 0.0f), CEnemy::ENEMYTYPE_SMALL, CEnemy::ENEMYMOVETYPE_HOMING, ENEMY001_TEXTURENAME);

	// �ʏ�e
	for (int i = 0; i < MAX_BULLET; i++)
	{
		m_Bullet[i] = CBullet::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(5.0f, 5.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), false, BULLET001_TEXTURENAME, CTextureManager::TEXTYPE_BULLET);
	}

	// �G�ʏ�e
	for (int i = 0; i < MAX_ENEMY_BULLET; i++)
	{
		m_EnemyBullet[i] = CBullet::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(5.0f, 5.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), false, ENEMYBULLET_TEXTURENAME, CTextureManager::TEXTYPE_ENEMY_BULLET);
	}

	// �U���e
	for (int i = 0; i < MAX_HOMING_BULLET; i++)
	{
		m_HomingBullet[i] = CHomingBullet::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, false, HOMINGBULLET_FILENAME);
	}

	// �p�[�e�B�N��
	for (int i = 0; i < MAX_PARTICLE; i++)
	{
		m_Particle[i] = CParticle::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(255, 255, 255, 255), 60, CTextureManager::TEXTYPE_PARTICLE);
	}

	// �v���C���[��e�p�[�e�B�N��
	for (int i = 0; i < MAX_PARTICLE; i++)
	{
		m_HitParticle[i] = CParticle::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(255, 255, 255, 255), 60, CTextureManager::TEXTYPE_ENEMY_BULLET);
	}

	// ���[�U�[�p�[�e�B�N��
	for (int i = 0; i < MAX_PARTICLE; i++)
	{
		m_LaserParticle[i] = CLaserParticle::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(5.0f, 5.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 255, 0, PARTICLE001_TEXTURENAME, CTextureManager::TEXTYPE_PARTICLE);
	}

	// �G���S���b�Z�[�W
	for (int i = 0; i < MAX_NIRVANA; i++)
	{
		m_Nirvana[i] = CTextBox3D::Create(m_Bullet[i]->GetPos(), D3DXVECTOR3(10.0f, 7.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 60, 255, HITMESSAGE_TEXTURENAME, CTextureManager::TEXTYPE_NONE);
		m_Nirvana[i]->SetUse(false);
	}

	// UI ////////////////////////////////////////////////////////////////

	// �X�R�A
	m_Score = CScore::Create(D3DXVECTOR3(120.0f, 50.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), SCORE_DIGIT, SCORE_TEX_NAME);
	CTextBox::Create(D3DXVECTOR3(220.0f, 50.0f, 0.0f), D3DXVECTOR3(120.0f, 70.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f, NIRVANA_TEXTURENAME, CTextureManager::TEXTYPE_NONE);

	// �^�C�}�[
	m_Timer = CScore::Create(D3DXVECTOR3(120.0f, 110.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), SCORE_DIGIT, SCORE_TEX_NAME);
	m_Timer->SetScore(TIMER_LIMIT);
	CTextBox::Create(D3DXVECTOR3(220.0f, 110.0f, 0.0f), D3DXVECTOR3(120.0f, 70.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f, TIME_TEXTURENAME, CTextureManager::TEXTYPE_NONE);

	// �@��
	CEnergyGauge::Create(D3DXVECTOR3(470.0f, 560.0f, 0.0f), D3DXVECTOR3(700.0f, 65.0f, 0.0f), 0.7f, ENEGYGAUGE_TEXTURENAME, CTextureManager::TEXTYPE_NONE);
	CTextBox::Create(D3DXVECTOR3(60.0f, 560.0f, 0.0f), D3DXVECTOR3(120.0f, 70.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f, ENEGY_TEXTURENAME, CTextureManager::TEXTYPE_NONE);

	// �̗�
	CHitpointGauge::Create(D3DXVECTOR3(470.0f, 490.0f, 0.0f), D3DXVECTOR3(700.0f, 65.0f, 0.0f), 0.7f, ENEGYGAUGE_TEXTURENAME, CTextureManager::TEXTYPE_NONE);
	CTextBox::Create(D3DXVECTOR3(60.0f, 490.0f, 0.0f), D3DXVECTOR3(120.0f, 70.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f, HITPOINT_TEXTURENAME, CTextureManager::TEXTYPE_NONE);

	// �J�n���b�Z�[�W
	m_StartText = CTextBox::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(600.0f, 200.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f, STARTTEXT_TEXTURENAME, CTextureManager::TEXTYPE_NONE);
	CPointPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 2.0f), 1.0f, POINTPLAYER_TEXTURENAME, CTextureManager::TEXTYPE_NONE);

	// ���̑� ///////////////////////////////////////////////////////////

	// ���[�h
	Load();

	PlaySound(SOUND_LABEL_BGM001);
}

/*------------------------------------------------------------------------------
  �@�I������
------------------------------------------------------------------------------*/
void CModeGame::Uninit( void )
{
	CScene::ReleaseAll();

	if (m_Camera != NULL)
	{
		m_Camera->Uninit();
		delete m_Camera;
		m_Camera = NULL;
	}

	if (m_Light != NULL)
	{
		m_Light->Uninit();
		delete m_Light;
		m_Light = NULL;
	}

	if (m_Debug != NULL)
	{
		m_Debug->Uninit();
		delete m_Light;
		m_Debug = NULL;
	}

	if (m_Score != NULL)
	{
		m_Score = NULL;
	}

	if (m_Timer != NULL)
	{
		m_Timer = NULL;
	}

	if (m_MeshField != NULL)
	{
		m_MeshField = NULL;
	}

	if (m_MeshDome != NULL)
	{
		m_MeshDome = NULL;
	}

	if (m_Player != NULL)
	{
		m_Player = NULL;
	}
	
	for (int i = 0; i < MAX_WEED; i++)
	{
		if (m_Weed[i] != NULL)
		{
			m_Weed[i] = NULL;
		}
	}

	if (m_LaserEmitter != NULL)
	{
		m_LaserEmitter = NULL;
	}

	for (int i = 0; i < MAX_EMITTER; i++)
	{
		if (m_Emitter[i] != NULL)
		{
			delete m_Emitter[i];
			m_Emitter[i] = NULL;
		}
	}

	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
	{
		if (m_Bullet[nCnt] != NULL)
		{
			m_Bullet[nCnt] = NULL;
		}
	}

	for (int nCnt = 0; nCnt < MAX_HOMING_BULLET; nCnt++)
	{
		if (m_HomingBullet[nCnt] != NULL)
		{
			m_HomingBullet[nCnt] = NULL;
		}
	}

	for (int i = 0; i < MAX_PARTICLE; i++)
	{
		if (m_Particle[i] != NULL)
		{
			m_Particle[i] = NULL;
		}
	}

	for (int i = 0; i < MAX_PARTICLE; i++)
	{
		if (m_LaserParticle[i] != NULL)
		{
			m_LaserParticle[i] = NULL;
		}
	}

	for (int i = 0; i < MAX_ENEMY; i++)
	{
		if (m_Enemy[i] != NULL)
		{
			m_Enemy[i] = NULL;
		}
	}

	for (int i = 0; i < MAX_ITEM; i++)
	{
		if (m_Item[i] != NULL)
		{
			m_Item[i] = NULL;
		}
	}

	for (int i = 0; i < MAX_TOMBSTONE; i++)
	{
		if (m_Tombstone[i] != NULL)
		{
			m_Tombstone[i] = NULL;
		}
	}

	for (int i = 0; i < MAX_NIRVANA; i++)
	{
		if (m_Nirvana[i] != NULL)
		{
			m_Nirvana[i] = NULL;
		}
	}

	for (auto it = m_Rockon.begin(); it != m_Rockon.end(); ++it)
	{
		if (*it != nullptr)
		{
			*it = nullptr;
		}
	}

	StopSound(SOUND_LABEL_BGM001);
}

/*------------------------------------------------------------------------------
  �@�X�V
------------------------------------------------------------------------------*/
void CModeGame::Update(void)
{
	switch (m_step)
	{
	case STEP_1:
		if (m_timer > 120)
		{
			m_StartText->SetDoUninit(true);
			m_StartText = NULL;
			m_timer = 0;
			m_step = STEP_2;
		}

		m_timer++;
		break;
	case STEP_2:
		if (m_Score->GetScore() >= GAME_CLEAR_SCORE)
		{
			m_step = STEP_3;
			m_ClearText = CTextBox::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(2400.0f, 800.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(600.0f, 200.0f, 0.0f), 0.0f, CLEARTEXT_TEXTURENAME, CTextureManager::TEXTYPE_NONE);
			m_ClearText->SetDeltaSize((m_ClearText->GetEndSize() - m_ClearText->GetSize()) * 0.01f);
		}

		if (m_Timer->GetScore() <= 0)
		{
			m_step = STEP_4;
			m_GameOverText = CTextBox::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(2400.0f, 800.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(600.0f, 200.0f, 0.0f), 0.0f, GAMEOVERTEXT_TEXTURENAME, CTextureManager::TEXTYPE_NONE);
			m_GameOverText->SetDeltaSize((m_GameOverText->GetEndSize() - m_GameOverText->GetSize()) * 0.01f);
		}

		break;
	case STEP_3:
		m_ClearText->AddAlpha(0.02f);
 		m_ClearText->AddSize(m_ClearText->GetDeltaSize());
		if (m_ClearText->GetSize().x < m_ClearText->GetEndSize().x)
		{
			m_ClearText->SetSize(m_ClearText->GetEndSize());
		}

		if (m_timer > 300)
		{
			CManager::Fade(new CModeResult);
			m_timer = 0;
		}

		m_timer++;
		break;
	case STEP_4:
		m_GameOverText->AddAlpha(0.02f);
		m_GameOverText->AddSize(m_GameOverText->GetDeltaSize());
		if (m_GameOverText->GetSize().x < m_GameOverText->GetEndSize().x)
		{
			m_GameOverText->SetSize(m_GameOverText->GetEndSize());
		}

		if (m_timer > 300)
		{
			CManager::Fade(new CModeResult);
			m_timer = 0;
		}

		m_timer++;
		break;
	}

	// �J�[�\�����W�̎擾
	GetCursorPos(&m_cursorPos);
	ScreenToClient(GethWnd(), &m_cursorPos);

	// �J�����̍X�V
	CameraFollowPlayer();
	RotationCamera();
	m_Camera->Update();

	// �����蔻��
	CollisionBulletAndEnemy();
	CollisionHomingBulletAndEnemy();
	CollisionLaserAndEnemy();
	CollisionPlayerAndItem();
	CollisionPlayerAndBullet();

	// �v���C���[�̑���
	OperationPlayer();
	OperationEnemy();

	// �G�~�b�^�[�̍X�V
	UpdateEmitter();

	// ���b�Z�[�W�̍X�V
	UpdateText();
	
	// �^�C�}�[�̍X�V
	UpdateTimer();

	// �e�̍X�V
	UpdateBullet();

	// ���f�B�G�[�^�[�̍X�V
	for (auto it = m_Mediator.begin(); it != m_Mediator.end(); ++it)
	{
		(*it)->Update();
	}

	// �r���{�[�h�̃\�[�g
	//CScene::SortBillboard();

	// �I�������`�F�b�N
	CheckUninit();
}

/*------------------------------------------------------------------------------
  �@�`�揈��
------------------------------------------------------------------------------*/
void CModeGame::Draw( void )
{

}

//------------------------------------------------------------------------------
//�@�|�C���^��Null�ɂ���
//------------------------------------------------------------------------------
void CModeGame::DoNullPointer(void)
{
	for (int i = 0; i < MAX_ITEM; i++)
	{
		if (m_Item[i] == nullptr) continue;

		if (m_Item[i]->GetDoUninit())
		{
			m_Item[i] = nullptr;
		}
	}

	for (int i = 0; i < MAX_ITEM; i++)
	{
		if (m_Enemy[i] == nullptr) continue;

		if (m_Item[i]->GetDoUninit())
		{
			m_Item[i] = nullptr;
		}
	}
}

/*------------------------------------------------------------------------------
�@�I�������̃`�F�b�N
------------------------------------------------------------------------------*/
void CModeGame::CheckUninit(void)
{
	CScene::CheckUninit();
	
	// �G�~�b�^�[�̏I�������`�F�b�N
	for (int i = 0; i < MAX_EMITTER; i++)
	{
		if (m_Emitter[i] == NULL) continue;

		if (m_Emitter[i]->GetDoUninit())
		{
			delete m_Emitter[i];
			m_Emitter[i] = NULL;
		}
	}

	// ���b�N�I���̏I�������`�F�b�N
	m_Rockon.erase(std::remove_if(m_Rockon.begin(), m_Rockon.end(), [](CRockon* p) {if (p->GetDoUninit()) { return true; }return false; }), m_Rockon.end());
}

/*------------------------------------------------------------------------------
�@�J�������v���C���[�ɒǏ]
------------------------------------------------------------------------------*/
void CModeGame::CameraFollowPlayer(void)
{
	D3DXVECTOR3 temp = m_Player->GetVelocity();
	D3DXVec3Normalize(&temp, &temp);
		
	m_Camera->SetPosAtTarget(m_Player->GetPos());
	m_Camera->SetPosEyeTarget(m_Player->GetPos() - D3DXVECTOR3(temp) * 15.0f);

	m_Camera->AddPosAt((m_Camera->GetPosAtTarget() - m_Camera->GetPosAt()) * 0.1f);
	m_Camera->AddPosEye((m_Camera->GetPosEyeTarget() - m_Camera->GetPosEye()) * 0.1f);
}

/*------------------------------------------------------------------------------
�@�e�ƓG�̓����蔻��
------------------------------------------------------------------------------*/
void CModeGame::CollisionBulletAndEnemy(void)
{
	for (int i = 0; i < MAX_BULLET; i++)
	{
		if (m_Bullet[i]->GetUse() == false || m_Bullet[i]->GetType() == CBullet::BULLETTYPE_ENEMY_NORMAL) continue;

 		for (int j = 0; j < MAX_ENEMY; j++)
		{
			if (m_Enemy[j] == NULL) continue;

			if (CCollision::Sphere(m_Bullet[i]->GetPos(), m_Enemy[j]->GetPos(), m_Bullet[i]->GetSize().x * 0.5f, m_Enemy[j]->GetSize().x * 0.5f))
			{
				// �G�~�b�^�[�̐���
				for (int k = 0; k < MAX_EMITTER; k++)
				{
					if (m_Emitter[k] != NULL) continue;

					m_Emitter[k] = CEmitter::Create(m_Bullet[i]->GetPos(), D3DXVECTOR3(ENEMY_EXPLOSION_SIZE, ENEMY_EXPLOSION_SIZE, 0.0f), 0.50f, D3DXCOLOR(255, 255, 255, 255), 128, 30, 1, CEmitter::EMITTERTYPE_ENEMY);
					break;
				}

				// �G�̏��Ń��b�Z�[�W
				for (int l = 0; l < MAX_NIRVANA; l++)
				{
					if (m_Nirvana[l]->GetUse()) continue;

					m_Nirvana[l]->SetPos(m_Bullet[i]->GetPos());
					m_Nirvana[l]->SetUse(true);

					if (m_Enemy[j]->GetType() == CEnemy::ENEMYTYPE_SMALL)
					{
						m_Nirvana[l]->SetSize(D3DXVECTOR3(10.0f, 7.0f, 0.0f));
						m_Nirvana[l]->SetTex(D3DXVECTOR2(0.0f, 0.0f));
						m_Nirvana[l]->SetTexSize(D3DXVECTOR2(1.0f, 0.5f));
					}
					else if (m_Enemy[j]->GetType() == CEnemy::ENEMYTYPE_MIDDLE)
					{
						m_Nirvana[l]->SetSize(D3DXVECTOR3(15.0f, 10.0f, 0.0f));
						m_Nirvana[l]->SetTex(D3DXVECTOR2(0.0f, 0.5f));
						m_Nirvana[l]->SetTexSize(D3DXVECTOR2(1.0f, 0.5f));
					}
					else if (m_Enemy[j]->GetType() == CEnemy::ENEMYTYPE_LARGE)
					{
						m_Nirvana[l]->SetSize(D3DXVECTOR3(23.0f, 15.0f, 0.0f));
						m_Nirvana[l]->SetTex(D3DXVECTOR2(0.0f, 0.5f));
						m_Nirvana[l]->SetTexSize(D3DXVECTOR2(1.0f, 0.5f));
					}

					break;
				}

				// �G�̕���
				if (m_Enemy[j]->GetType() != CEnemy::ENEMYTYPE_SMALL)
				{
					DivisionEnemy(m_Enemy[j]->GetPos(), m_Enemy[j]->GetType(), m_Enemy[j]->GetMoveType());
				}
				
				// �A�C�e���̐���
				for (int k = 0; k < MAX_ITEM; k++)
				{
					if (m_Item[k] != NULL) continue;

					m_Item[k] = CItem::Create(m_Enemy[j]->GetPos(), D3DXVECTOR3(ITEM_SIZE_X, ITEM_SIZE_Y, 0.0f), 2.0f, 1.0f, ITEM_TEXTURENAME, CTextureManager::TEXTYPE_NONE);
					break;
				}

				// �e�ƓG�̏I���t���O
				m_Bullet[i]->SetDeltaRot(0.0f);
				m_Bullet[i]->SetUse(false);
				m_Enemy[j]->SetDoUninit(true);
				m_Enemy[j] = NULL;

				// �X�R�A���Z
				m_Score->AddScore(1);

				PlaySound(SOUND_LABEL_SE_EXPLOSION);
				break;
			}
		}
	}
}

/*------------------------------------------------------------------------------
�@�z�[�~���O�e�ƓG�̓����蔻��
------------------------------------------------------------------------------*/
void CModeGame::CollisionHomingBulletAndEnemy(void)
{
	for (int i = 0; i < MAX_BULLET; i++)
	{
		if (m_HomingBullet[i]->GetUse() == false) continue;

		for (int j = 0; j < MAX_ENEMY; j++)
		{
			if (m_Enemy[j] == NULL) continue;

			if (CCollision::Sphere(m_HomingBullet[i]->GetPos(), m_Enemy[j]->GetPos(), m_HomingBullet[i]->GetSize().x * 0.5f, m_Enemy[j]->GetSize().x * 0.5f))
			{
				// �G�~�b�^�[�̐���
				for (int k = 0; k < MAX_EMITTER; k++)
				{
					if (m_Emitter[k] != NULL) continue;

					m_Emitter[k] = CEmitter::Create(m_HomingBullet[i]->GetPos(), D3DXVECTOR3(ENEMY_EXPLOSION_SIZE, ENEMY_EXPLOSION_SIZE, 0.0f), 0.50f, D3DXCOLOR(255, 255, 255, 255), 128, 30, 1, CEmitter::EMITTERTYPE_ENEMY);
					break;
				}

				// �G�̏��Ń��b�Z�[�W
				for (int l = 0; l < MAX_NIRVANA; l++)
				{
					if (m_Nirvana[l]->GetUse()) continue;

					m_Nirvana[l]->SetPos(m_HomingBullet[i]->GetPos());
					m_Nirvana[l]->SetUse(true);

					if (m_Enemy[j]->GetType() == CEnemy::ENEMYTYPE_SMALL)
					{
						m_Nirvana[l]->SetSize(D3DXVECTOR3(10.0f, 7.0f, 0.0f));
						m_Nirvana[l]->SetTex(D3DXVECTOR2(0.0f, 0.0f));
						m_Nirvana[l]->SetTexSize(D3DXVECTOR2(1.0f, 0.5f));
					}
					else if (m_Enemy[j]->GetType() == CEnemy::ENEMYTYPE_MIDDLE)
					{
						m_Nirvana[l]->SetSize(D3DXVECTOR3(15.0f, 10.0f, 0.0f));
						m_Nirvana[l]->SetTex(D3DXVECTOR2(0.0f, 0.5f));
						m_Nirvana[l]->SetTexSize(D3DXVECTOR2(1.0f, 0.5f));
					}
					else if (m_Enemy[j]->GetType() == CEnemy::ENEMYTYPE_LARGE)
					{
						m_Nirvana[l]->SetSize(D3DXVECTOR3(23.0f, 15.0f, 0.0f));
						m_Nirvana[l]->SetTex(D3DXVECTOR2(0.0f, 0.5f));
						m_Nirvana[l]->SetTexSize(D3DXVECTOR2(1.0f, 0.5f));
					}

					break;
				}

				// �G�̕���
				if (m_Enemy[j]->GetType() != CEnemy::ENEMYTYPE_SMALL)
				{
					DivisionEnemy(m_Enemy[j]->GetPos(), m_Enemy[j]->GetType(), m_Enemy[j]->GetMoveType());
				}

				// �e�E�G�E���b�N�I���̏I���t���O
				m_HomingBullet[i]->SetUse(false);
				m_Enemy[j]->SetDoUninit(true);

				// �X�R�A���Z
				m_Score->AddScore(1);

				PlaySound(SOUND_LABEL_SE_EXPLOSION);
				break;
			}
		}
	}
}

/*------------------------------------------------------------------------------
�@���[�U�[�ƓG�̓����蔻��
------------------------------------------------------------------------------*/
void CModeGame::CollisionLaserAndEnemy(void)
{
	for (int i = 0; i < MAX_PARTICLE; i++)
	{
		if (m_LaserParticle[i]->GetUse() == false) continue;

		for (int j = 0; j < MAX_ENEMY; j++)
		{
			if (m_Enemy[j] == NULL) continue;

			if (CCollision::Sphere(m_LaserParticle[i]->GetPos(), m_Enemy[j]->GetPos(), m_LaserParticle[i]->GetSize().x * 0.8f, m_Enemy[j]->GetSize().x * 0.8f))
			{
				// �G�~�b�^�[�̐���
				for (int k = 0; k < MAX_EMITTER; k++)
				{
					if (m_Emitter[k] != NULL) continue;

					m_Emitter[k] = CEmitter::Create(m_LaserParticle[i]->GetPos(), D3DXVECTOR3(ENEMY_EXPLOSION_SIZE, ENEMY_EXPLOSION_SIZE, 0.0f), 0.50f, D3DXCOLOR(255, 255, 255, 255), 128, 30, 1, CEmitter::EMITTERTYPE_ENEMY);
					break;
				}

				// �G�̏��Ń��b�Z�[�W
				for (int l = 0; l < MAX_NIRVANA; l++)
				{
					if (m_Nirvana[l]->GetUse()) continue;

					m_Nirvana[l]->SetPos(m_LaserParticle[i]->GetPos());
					m_Nirvana[l]->SetUse(true);

					if (m_Enemy[j]->GetType() == CEnemy::ENEMYTYPE_SMALL)
					{
						m_Nirvana[l]->SetSize(D3DXVECTOR3(10.0f, 7.0f, 0.0f));
						m_Nirvana[l]->SetTex(D3DXVECTOR2(0.0f, 0.0f));
						m_Nirvana[l]->SetTexSize(D3DXVECTOR2(1.0f, 0.5f));
					}
					else if (m_Enemy[j]->GetType() == CEnemy::ENEMYTYPE_MIDDLE)
					{
						m_Nirvana[l]->SetSize(D3DXVECTOR3(15.0f, 10.0f, 0.0f));
						m_Nirvana[l]->SetTex(D3DXVECTOR2(0.0f, 0.5f));
						m_Nirvana[l]->SetTexSize(D3DXVECTOR2(1.0f, 0.5f));
					}
					else if (m_Enemy[j]->GetType() == CEnemy::ENEMYTYPE_LARGE)
					{
						m_Nirvana[l]->SetSize(D3DXVECTOR3(23.0f, 15.0f, 0.0f));
						m_Nirvana[l]->SetTex(D3DXVECTOR2(0.0f, 0.5f));
						m_Nirvana[l]->SetTexSize(D3DXVECTOR2(1.0f, 0.5f));
					}

					break;
				}

				// �G�̕���
				if (m_Enemy[j]->GetType() != CEnemy::ENEMYTYPE_SMALL)
				{
					DivisionEnemy(m_Enemy[j]->GetPos(), m_Enemy[j]->GetType(), m_Enemy[j]->GetMoveType());
				}

				// �G�̏I���t���O
				m_Enemy[j]->SetDoUninit(true);
				m_Enemy[j] = NULL;

				// �X�R�A���Z
				m_Score->AddScore(1);

				PlaySound(SOUND_LABEL_SE_EXPLOSION);
				break;
			}
		}
	}
}

/*------------------------------------------------------------------------------
�@�v���C���[�ƃA�C�e���̓����蔻��
------------------------------------------------------------------------------*/
void CModeGame::CollisionPlayerAndItem(void)
{
	for (int i = 0; i < MAX_ITEM; i++)
	{
		if (m_Item[i] == NULL) continue;

		if (CCollision::Sphere(m_Player->GetPos(), m_Item[i]->GetPos(), m_Player->GetRadius(), m_Item[i]->GetSize().x * 0.5f))
		{
			m_Player->AddEnergy(ITEM_VALUE_ENERGY);
			m_Item[i]->SetDoUninit(true);
			break;
		}
	}
}

//------------------------------------------------------------------------------
// �v���C���[�ƓG�e�̓����蔻��
//------------------------------------------------------------------------------
void CModeGame::CollisionPlayerAndBullet(void)
{
	if (m_Player->GetDoDraw() == false) return;

	for (int i = 0; i < MAX_ENEMY_BULLET; i++)
	{
		if (m_EnemyBullet[i]->GetUse() == false || m_EnemyBullet[i]->GetType() != CBullet::BULLETTYPE_ENEMY_NORMAL) continue;

		if (CCollision::Sphere(m_EnemyBullet[i]->GetPos(), m_Player->GetPos(), m_EnemyBullet[i]->GetSize().x * 0.5f, m_Player->GetRadius()) && m_Player->GetHit() == false)
		{
			for (int j = 0; j < MAX_EMITTER; j++)
			{
				if (m_Emitter[j] != NULL) continue;

				m_Emitter[j] = CEmitter::Create(m_Player->GetPos(), D3DXVECTOR3(PLAYER_HITEFFECT_SIZE, PLAYER_HITEFFECT_SIZE, 0.0f), 0.50f, D3DXCOLOR(255, 255, 255, 255), 128, 25, 1, CEmitter::EMITTERTYPE_PLAYER);
				break;
			}

			m_EnemyBullet[i]->SetUse(false);
			m_Player->AddHitpoint(-1);
			m_Player->SetHit(true);

			// ���S����
			if (m_Player->GetHitpoint() <= 0)
			{
				// ���S�G�t�F�N�g
				for (int j = 0; j < MAX_EMITTER; j++)
				{
					if (m_Emitter[j] != NULL) continue;

					m_Emitter[j] = CEmitter::Create(m_Player->GetPos(), D3DXVECTOR3(PLAYER_DEADEFFECT_SIZE, PLAYER_DEADEFFECT_SIZE, 0.0f), 0.50f, D3DXCOLOR(255, 255, 255, 255), 128, 35, 2, CEmitter::EMITTERTYPE_ENEMY);
					break;
				}

				// �`��t���O���I�t��
				m_Player->SetDoDraw(false);
			}
		}
	}
}

/*------------------------------------------------------------------------------
 �@�v���C���[�̑���
------------------------------------------------------------------------------*/
void CModeGame::OperationPlayer(void)
{
	// �e�̔���
	if (CManager::GetInputKeyboard()->GetKeyTrigger(DIK_SPACE))
	{
		for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
		{
			if (m_Bullet[nCnt]->GetUse() == true) continue;

			m_Bullet[nCnt]->SetPos(D3DXVECTOR3(m_Player->GetPos().x, m_Player->GetPos().y - m_Bullet[nCnt]->GetSize().y * 0.5, m_Player->GetPos().z));
			m_Bullet[nCnt]->SetSize(D3DXVECTOR3(5.0f, 5.0f, 0.0f));
			D3DXVECTOR3 temp = m_Player->GetVelocity();
			D3DXVec3Normalize(&temp, &temp);
			m_Bullet[nCnt]->SetVelocity(temp * 2.0f);
			m_Bullet[nCnt]->SetType(CBullet::BULLETTYPE_NORMAL);
			m_Bullet[nCnt]->SetUse(true);

			PlaySound(SOUND_LABEL_SE_SHOT);
			break;
		}
	}

	// ���[�U�[�̔���
	if (CManager::GetInputKeyboard()->GetKeyTrigger(DIK_L) &&  m_Player->GetEnergy() >= ENERGY_CONSUMPTION_LASER)
	{
		m_LaserEmitter = CLaserEmitter::Create(m_Player->GetPos(), m_Player->GetVelocity() * LASEREMITTER_SPEED, D3DXVECTOR3(5.0f, 5.0f, 0.0f), D3DXVECTOR3(5.0f, 5.0f, 0.0f)/*m_Player->GetVelocity() * 2.0f*/, D3DXCOLOR(255, 255, 255, 255), 120, 30, PARTICLE_TEXTURENAME);
		m_Player->AddEnergy(-ENERGY_CONSUMPTION_LASER);

		PlaySound(SOUND_LABEL_SE_LASER);
	} 

	// ���b�N�I���̃\�[�g
	std::sort(m_Rockon.begin(), m_Rockon.end(), [](CRockon* a, CRockon* b) {return a->GetTimer() > b->GetTimer(); });

	// �z�[�~���O�e�̔���
	if (CManager::GetInputKeyboard()->GetKeyTrigger(DIK_H) && m_Player->GetEnergy() >= ENERGY_CONSUMPTION_HOMING)
	{
		for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
		{
			if (m_HomingBullet[nCnt]->GetUse() == true) continue;

			for (auto it = m_Rockon.begin(); it != m_Rockon.end(); ++it)
			{
				if (*it == nullptr) continue;

				if ((*it)->GetUse() == false || it == m_Rockon.end() - 1)
				{
					m_HomingBullet[nCnt]->SetTargetPos((*it)->GetPos());
					m_HomingBullet[nCnt]->SetRockonID((*it)->GetRockonID());
					(*it)->SetUse(true);
					break;
				}
			}

			m_HomingBullet[nCnt]->SetPos(D3DXVECTOR3(m_Player->GetPos().x, m_Player->GetPos().y - m_Bullet[nCnt]->GetSize().y * 0.5, m_Player->GetPos().z));
			m_HomingBullet[nCnt]->SetSize(D3DXVECTOR3(5.0f, 5.0f, 0.0f));
			m_HomingBullet[nCnt]->SetVelocity(m_Player->GetVelocity() * HOMINGBULLET_SPEED);
			m_HomingBullet[nCnt]->SetUse(true);

			// �G�~�b�^�[�̐���
			for (int k = 0; k < MAX_EMITTER; k++)
			{
				if (m_Emitter[k] != NULL) continue;

				m_Emitter[k] = CEmitter::Create(m_HomingBullet[nCnt]->GetPos(), D3DXVECTOR3(HOMING_PARTICLE_SIZE, HOMING_PARTICLE_SIZE, 0.0f), 0.50f, D3DXCOLOR(255, 255, 255, 255), 1, 30, HOMINGBULLET_LIFE, CEmitter::EMITTERTYPE_HOMING);
				m_Emitter[k]->SetHomingBulletID(nCnt);
				break;
			}
			break;
		}

		m_Player->AddEnergy(-ENERGY_CONSUMPTION_HOMING);
		PlaySound(SOUND_LABEL_SE_MISSILE);
	}

	// �v���C���[�̌����ύX
	if (CManager::GetInputKeyboard()->GetKeyPress(DIK_D))
	{
		m_Player->AddRotThe(PLAYER_ROT_VARIATION);
	}

	if (CManager::GetInputKeyboard()->GetKeyPress(DIK_A))
	{
		m_Player->AddRotThe(- PLAYER_ROT_VARIATION);
	}

	if (CManager::GetInputKeyboard()->GetKeyPress(DIK_W))
	{
		m_Player->AddRotFai(PLAYER_ROT_VARIATION);
	}

	if (CManager::GetInputKeyboard()->GetKeyPress(DIK_S))
	{
		m_Player->AddRotFai(- PLAYER_ROT_VARIATION);
	}

	// �v���C���[�̈ړ��X�s�[�h�ύX
	if (CManager::GetInputKeyboard()->GetKeyPress(DIK_UP))
	{
		m_Player->AddSpeed(0.05f);
	}

	if (CManager::GetInputKeyboard()->GetKeyPress(DIK_DOWN))
	{
		m_Player->AddSpeed(-0.05f);
	}

	// �v���C���[�̕��s�ړ�
	D3DXVECTOR3 vecP = m_Player->GetVelocity();
	D3DXVECTOR3 vecUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	if (CManager::GetInputKeyboard()->GetKeyPress(DIK_RIGHT))
	{
		D3DXVec3Cross(&vecP, &vecUp, &vecP);
		D3DXVec3Normalize(&vecP, &vecP);
		m_Player->SetParallelVec(vecP);
		m_Camera->AddPosAt(vecP);		
	}

	if (CManager::GetInputKeyboard()->GetKeyPress(DIK_LEFT))
	{
		D3DXVec3Cross(&vecP, &vecP, &vecUp);
		D3DXVec3Normalize(&vecP, &vecP);
		m_Player->SetParallelVec(vecP);
		m_Camera->AddPosAt(vecP);
	}

	// �v���C���[�̒�~
	if (CManager::GetInputKeyboard()->GetKeyPress(DIK_Z))
	{
		m_Player->SetMove(false);
	}
}

//------------------------------------------------------------------------------
//�@�G�̑���
//------------------------------------------------------------------------------
void CModeGame::OperationEnemy(void)
{
	// �e�̔���
	for (int j = 0; j < MAX_ENEMY; j++)
	{
		if (m_Enemy[j] == nullptr) continue;
		if (rand() % 120 != 0) continue;

		for (int i = 0; i < MAX_ENEMY_BULLET; i++)
		{
			if (m_EnemyBullet[i]->GetUse()) continue;

			m_EnemyBullet[i]->SetPos(D3DXVECTOR3(m_Enemy[j]->GetPos()/*.x, m_Enemy[j]->GetPos().y - m_Enemy[j]->GetSize().y * 0.5, m_Enemy[j]->GetPos().z)*/));
			m_EnemyBullet[i]->SetSize(D3DXVECTOR3(5.0f, 5.0f, 0.0f));
			D3DXVECTOR3 vec = m_Player->GetPos() - m_Enemy[j]->GetPos();
			D3DXVec3Normalize(&vec, &vec);
			m_EnemyBullet[i]->SetVelocity(vec * 1.0f);
			m_EnemyBullet[i]->SetType(CBullet::BULLETTYPE_ENEMY_NORMAL);
			m_EnemyBullet[i]->SetUse(true);

			break;
		}
	}
}

/*------------------------------------------------------------------------------
�@�J�����̉�]
------------------------------------------------------------------------------*/
void CModeGame::RotationCamera(void)
{
	D3DXVECTOR3 vec = m_Camera->GetPosEye() - m_Player->GetPos();
	D3DXMATRIX rotMtx;
	D3DXMatrixRotationYawPitchRoll(&rotMtx,  m_Camera->GetRotXY(), m_Camera->GetRotXZ(), 0.0f);
	D3DXVec3TransformCoord(&vec, &vec, &rotMtx);
	m_Camera->SetPosEye(vec + m_Player->GetPos());
}

/*------------------------------------------------------------------------------
�@���b�Z�[�W�̍X�V
------------------------------------------------------------------------------*/
void CModeGame::UpdateText(void)
{
	for (int i = 0; i < MAX_NIRVANA; i++)
	{
		if (m_Nirvana[i]->GetUse() == false) continue;

		m_Nirvana[i]->AddPos(D3DXVECTOR3(0.0f, 0.1f, 0.0f));
		m_Nirvana[i]->AddAlpha(-6);
		m_Nirvana[i]->AddLife(-1);

		if (m_Nirvana[i]->GetAlpha() <= 0)
		{
			m_Nirvana[i]->SetAlpha(0);
		}

		if (m_Nirvana[i]->GetLife() <= 0)
		{
 			m_Nirvana[i]->SetUse(false);
			m_Nirvana[i]->Reset();
		}
	}
}

/*------------------------------------------------------------------------------
�@�^�C�}�[�̍X�V
------------------------------------------------------------------------------*/
void CModeGame::UpdateTimer(void)
{
	m_gameTimer++;

	if (m_gameTimer % 60 == 0 && m_Timer->GetScore() > 0)
	{
		m_Timer->AddScore(-1);
	}
}

//------------------------------------------------------------------------------
//�@�G�~�b�^�[�̍X�V
//------------------------------------------------------------------------------
void CModeGame::UpdateEmitter(void)
{
	for (int i = 0; i < MAX_EMITTER; i++)
	{
		if (m_Emitter[i] == NULL) continue;

		if (m_Emitter[i]->GetType() == CEmitter::EMITTERTYPE_HOMING)
		{
			int ID = m_Emitter[i]->GetHomingBulletID(); 
			m_Emitter[i]->SetPos(m_HomingBullet[ID]->GetPos());
		}

		D3DXVECTOR3 vec = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		for (int j = 0; j < m_Emitter[i]->GetEmitPerFrame(); j++)
		{
			//	�z�[�~���O�e�̃G�~�b�^�[�̍X�V
			if (m_Emitter[i]->GetType() == CEmitter::EMITTERTYPE_HOMING)
			{
				vec.x = ((rand() % 100) - 50) * 0.01f;
				vec.y = ((rand() % 100) - 50) * 0.01f;
				D3DXVec3Normalize(&vec, &vec);
				vec *= 0.1f;
				D3DXMATRIX temp = m_HomingBullet[m_Emitter[i]->GetHomingBulletID()]->GetMtxRot();
				D3DXVec3TransformCoord(&vec, &vec, &temp);
			}
			else
			{
				// �����G�~�b�^�[�̍X�V
				float rotThe = (rand() % 628) * 0.01f;
				float rotFai = (rand() % 628) * 0.01f;
				vec.x = sinf(rotThe) * sinf(rotFai) * m_Emitter[i]->GetSpeedParticle();
				vec.y = cosf(rotThe) * m_Emitter[i]->GetSpeedParticle();
				vec.z = sinf(rotThe) * cosf(rotFai) * m_Emitter[i]->GetSpeedParticle();
			}

			// �p�[�e�B�N���̐ݒ�
			if (m_Emitter[i]->GetType() != CEmitter::EMITTERTYPE_PLAYER)
			{
				for (int k = 0; k < MAX_PARTICLE; k++)
				{
					if (m_Particle == NULL) break;

					if (m_Particle[k]->GetUse() == false)
					{
						m_Particle[k]->SetPos(m_Emitter[i]->GetPos());
						m_Particle[k]->SetSize(m_Emitter[i]->GetSizeParticle());
						m_Particle[k]->SetVelocity(vec);
						m_Particle[k]->SetColor(D3DXCOLOR(255, 255, 255, 128));
						m_Particle[k]->SetLife(m_Emitter[i]->GetLifeParticle());
						m_Particle[k]->SetUse(true);

						break;
					}
				}
			}
			// �v���C���[��e�p�[�e�B�N���̐ݒ�
			else
			{
				for (int l = 0; l < MAX_PARTICLE; l++)
				{
					if (m_HitParticle == NULL) break;

					if (m_HitParticle[l]->GetUse() == false)
					{
						m_HitParticle[l]->SetPos(m_Emitter[i]->GetPos());
						m_HitParticle[l]->SetSize(m_Emitter[i]->GetSizeParticle());
						m_HitParticle[l]->SetVelocity(vec);
						m_HitParticle[l]->SetAcceleration(0.9f);
						m_HitParticle[l]->SetAlphaDecay(0.95f);
						m_HitParticle[l]->SetColor(D3DXCOLOR(255, 255, 255, 128));
						m_HitParticle[l]->SetLife(rand() % m_Emitter[i]->GetLifeParticle());
						m_HitParticle[l]->SetUse(true);

						break;
					}
				}
			}
		}

		m_Emitter[i]->Update();
	}
}

//------------------------------------------------------------------------------
//�@�e�̍X�V
//------------------------------------------------------------------------------
void CModeGame::UpdateBullet(void)
{
	// �z�[�~���O�e�̖ڕW���W�X�V
	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
	{
		if (m_HomingBullet[nCnt]->GetUse() != true) continue;

		for (auto it = m_Rockon.begin(); it != m_Rockon.end(); ++it)
		{
			if (*it == nullptr) continue;

			if ((*it)->GetRockonID() == m_HomingBullet[nCnt]->GetRockonID())
			{
				m_HomingBullet[nCnt]->SetTargetPos((*it)->GetPos());
				break;
			}
		}
	}
}

/*------------------------------------------------------------------------------
�@�G�̕���
------------------------------------------------------------------------------*/
void CModeGame::DivisionEnemy(D3DXVECTOR3 pos, CEnemy::ENEMYTYPE type, CEnemy::ENEMYMOVETYPE moveType)
{
	switch (type)
	{
	case CEnemy::ENEMYTYPE_MIDDLE:
		for (int i = 0; i < MAX_ENEMY; i++)
		{
			if (m_Enemy[i] != NULL) continue;

			m_Enemy[i] = CEnemy::Create(D3DXVECTOR3(pos.x + 10.0f, pos.y, pos.z), D3DXVECTOR3(ENEMY_SIZE_SMALL_X, ENEMY_SIZE_SMALL_Y, 0.0f), CEnemy::ENEMYTYPE_SMALL, moveType, ENEMY001_TEXTURENAME);
			break;
		}

		for (int i = 0; i < MAX_ENEMY; i++)
		{
			if (m_Enemy[i] != NULL) continue;

			m_Enemy[i] = CEnemy::Create(D3DXVECTOR3(pos.x - 10.0f, pos.y, pos.z), D3DXVECTOR3(ENEMY_SIZE_SMALL_X, ENEMY_SIZE_SMALL_Y, 0.0f), CEnemy::ENEMYTYPE_SMALL, moveType, ENEMY001_TEXTURENAME);
			break;
		}
		
		break;

	case CEnemy::ENEMYTYPE_LARGE:
		for (int i = 0; i < MAX_ENEMY; i++)
		{
			if (m_Enemy[i] != NULL) continue;

			m_Enemy[i] = CEnemy::Create(D3DXVECTOR3(pos.x + 20.0f, pos.y, pos.z), D3DXVECTOR3(ENEMY_SIZE_MIDDLE_X, ENEMY_SIZE_MIDDLE_Y, 0.0f), CEnemy::ENEMYTYPE_MIDDLE, moveType, ENEMY001_TEXTURENAME);
			break;
		}

		for (int i = 0; i < MAX_ENEMY; i++)
		{
			if (m_Enemy[i] != NULL) continue;

			m_Enemy[i] = CEnemy::Create(D3DXVECTOR3(pos.x - 20.0f, pos.y, pos.z), D3DXVECTOR3(ENEMY_SIZE_MIDDLE_X, ENEMY_SIZE_MIDDLE_Y, 0.0f), CEnemy::ENEMYTYPE_MIDDLE, moveType, ENEMY001_TEXTURENAME);
			break;
		}

		break;

	default:
		break;
	}
}

//------------------------------------------------------------------------------
// ���[�h
//------------------------------------------------------------------------------
void CModeGame::Load(void)
{
	// ��΂̃��[�h
	char temp[256] = {};
	sprintf(temp, "data\\tombstone.bin");
	FILE* fp;
	fp = fopen(temp, "rb");
	if (fp == NULL)
	{
		MessageBox(NULL, "�o�C�i���t�@�C���I�[�v�����s", "�G���[", MB_OK);
		return;
	}

	D3DXVECTOR3 pos;
	for (int i = 0; i < MAX_TOMBSTONE; i++)
	{
		fread(&pos, sizeof(pos), 1, fp);

		if (m_Tombstone[i] != nullptr) continue;

		m_Tombstone[i] = CTombstone::Create(pos, 0.0f, 0.0f, TOMBSTONE_MODELNAME);
	}

	fclose(fp);

	// ���̃��[�h
	sprintf(temp, "data\\weed.bin");
	fp = fopen(temp, "rb");
	if (fp == NULL)
	{
		MessageBox(NULL, "�o�C�i���t�@�C���I�[�v�����s", "�G���[", MB_OK);
		return;
	}

	int type;
	for (int i = 0; i < MAX_TOMBSTONE; i++)
	{
		fread(&pos, sizeof(pos), 1, fp);
		fread(&type, sizeof(type), 1, fp);

		if (m_Weed[i] != nullptr) continue;

		m_Weed[i] = CWeed::Create(pos, D3DXVECTOR3(5.0f, 5.0f, 0.0f), type);
	}

	fclose(fp);
}