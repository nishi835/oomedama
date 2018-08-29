/*==============================================================================

homingBullet�̃w�b�_�[ [homingBullet.h]
�쐬�� : �����@�S��
�쐬�� :
--------------------------------------------------------------------------------
��Update :
==============================================================================*/
#ifndef _HOMING_BULLET_H_
#define _HOMING_BULLET_H_

/*------------------------------------------------------------------------------
�@�w�b�_�t�@�C��
------------------------------------------------------------------------------*/
#include "sceneModel.h"
#include "textureManager.h"

/*------------------------------------------------------------------------------
 �@�}�N����`
------------------------------------------------------------------------------*/
#define MAX_HOMING_BULLET (256)
#define HOMINGBULLET_FILENAME "data/XMODEL/bullet.x"
#define HOMINGBULLET_LIFE (300)
#define HOMINGBULLET_SPEED (0.75f)

/*------------------------------------------------------------------------------
  �@�N���X
------------------------------------------------------------------------------*/
class CHomingBullet : public CScene
{
public:
	CHomingBullet(int Priority) : CScene(Priority) {};
	~CHomingBullet();

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �Z�b�^�[
	void SetVelocity(D3DXVECTOR3 velocity) { m_velocity = velocity; }
	void SetTargetPos(D3DXVECTOR3 targetPos) { m_targetPos = targetPos; }
	void SetAxis(D3DXVECTOR3 axis) { m_axis = axis; }
	void SetUse(bool use) { m_use = use; }
	void SetDeltaRot(float deltaRot) { m_deltaRot = deltaRot; }
	void SetRocalRot(float rocalRot) { m_rocalRot = rocalRot; }
	void SetLife(float life) { m_life = life; }
	void SetRockonID(int rockonID) { m_rockonID = rockonID; }

	void AddDeltaRot(float value) { m_deltaRot += value; }
	void AddLife(float value) { m_life += value; }

	// �Q�b�^�[
	D3DXVECTOR3 GetVelocity(void) { return m_velocity; }
	D3DXVECTOR3 GetTargetPos(void) { return m_targetPos; }
	D3DXVECTOR3 GetAxis(void) { return m_axis; }
	D3DXMATRIX GetMtxRot(void) { return m_mtxRot; }
	bool GetUse(void) { return m_use; }
	float GetDeltaRot(void) { return m_deltaRot; }
	float GetRocalRot(void) { return m_rocalRot; }
	int GetLife(void) { return m_life; }
	int GetRockonID(void) { return m_rockonID; }

	// ���̑��̃��\�b�h
	static CHomingBullet* Create(D3DXVECTOR3 pos, D3DXVECTOR3 velocity, float rotThe, float rotFai, bool use, char* filePass);
	void SetFilePass(const char* filePass) { strcpy(m_FilePass, filePass); }

private:
	D3DXVECTOR3 m_velocity;
	D3DXVECTOR3 m_targetPos;
	D3DXVECTOR3 m_axis;
	D3DXMATRIX m_mtxRot;  // ��]�s��
	float m_deltaRot;
	float m_rocalRot;
	int m_life;
	int m_rockonID;
	bool m_use;

	char m_FilePass[256];

	LPD3DXMESH			m_pMeshModel;		// ���b�V�����C���^�[�t�F�[�X�̊i�[
	LPD3DXBUFFER		m_pBuffMatModel;    // �}�e���A�����������C���^�[�t�F�[�X�ւ̃|�C���^�̊i�[
	LPDIRECT3DTEXTURE9  m_pTextureModel;    // �e�N�X�`���C���^�[�t�F�[�X�̊i�[�p
	DWORD				m_nNumMatModel;		// �}�e���A���̐�
};

#endif