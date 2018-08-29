/*==============================================================================

    player�̃w�b�_�[ [player.h]
                                                       �쐬�� : �����@�S��
                                                       �쐬�� : 
--------------------------------------------------------------------------------
    ��Update : 
==============================================================================*/
#ifndef _PLAYER_H_
#define _PLAYER_H_

/*------------------------------------------------------------------------------
  �@�w�b�_�t�@�C��
------------------------------------------------------------------------------*/
#include "sceneModel.h"
#include "scene2D.h"

/*------------------------------------------------------------------------------
  �@�}�N����`
------------------------------------------------------------------------------*/
#define PLAYER_FILE_NAME		"data/XMODEL/oyaji.x"
#define PLAYER_ROT_VARIATION (0.02f)					    // �p�x�̕ω���
#define PLAYER_ENERGY (100) // �v���C���[�̏����@�́i�G�l���M�[�j
#define PLAYER_SPEED (0.15f) // �v���C���[�̏������x
#define ENERGY_CONSUMPTION_LASER (10)
#define ENERGY_CONSUMPTION_HOMING (5)
#define PLAYER_HITEFFECT_SIZE (2.5f)
#define PLAYER_DEADEFFECT_SIZE (3.5f)

/*------------------------------------------------------------------------------
  �@�N���X
------------------------------------------------------------------------------*/
class CPlayer : public CSceneModel
{
public:
	CPlayer( int Priority ) : CSceneModel( Priority ){};
	~CPlayer() ;
	
	void Init( void);
	void Uninit( void );
	void Update( void );
	void Draw( void );
	
	// �Z�b�^�[
	void SetDoDraw(bool doDraw) { m_doDraw = doDraw; }
	void SetMove(bool move) { m_move = move; }
	void SetEnergy(int energy) { m_energy = energy; }
	void SetHitpoint(int hitpoint) { m_hitpoint = hitpoint; }
	void SetHit(bool hit) { m_hit = hit; }
	void SetTimer(int timer) { m_timer = timer; }
	void SetSpeed(float speed) { m_speed = speed; }
	void SetParallelVec(D3DXVECTOR3 parallelVec) { m_parallelVec = parallelVec; }
	void AddSpeed(float value) 
	{ 
		m_speed += value; 
	}

	void AddEnergy(int value)
	{
		m_energy += value; 
		m_energy = max(m_energy, 0);
		m_energy = min(m_energy, 100);
	}

	void AddHitpoint(int value)
	{
		m_hitpoint += value;
		m_hitpoint = max(m_hitpoint, 0);
		m_hitpoint = min(m_hitpoint, 100);
	}

	// �Q�b�^�[
	bool GetDoDraw(void) { return m_doDraw; }
	int GetEnergy(void) { return m_energy; }
	int GetHitpoint(void) { return m_hitpoint; }
	bool GetHit(void) { return m_hit; }

	// ���̑�
	static CPlayer* Create(D3DXVECTOR3 pos, D3DXVECTOR3 velocity, float rotThe, float rotFai, int energy, int hitpoint, char* filePass);

private:
	D3DXVECTOR3 m_parallelVec;
	float m_speed;
	int m_energy;
	int m_hitpoint;
	int m_timer;
	bool m_doDraw; // �`��t���O
	bool m_move;
	bool m_hit;
};

#endif