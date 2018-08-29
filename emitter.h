/*==============================================================================

emitter�̃w�b�_�[ [emitter.h]
�쐬�� : �����@�S��
�쐬�� :
--------------------------------------------------------------------------------
��Update :
==============================================================================*/
#ifndef _EMITTER_H_
#define _EMITTER_H_

/*------------------------------------------------------------------------------
�@�w�b�_�t�@�C��
------------------------------------------------------------------------------*/
#include "billboard.h"
#include <string.h>

/*------------------------------------------------------------------------------
 �@�}�N����`
------------------------------------------------------------------------------*/
#define MAX_EMITTER (8)

/*------------------------------------------------------------------------------
  �@�N���X
------------------------------------------------------------------------------*/
class CEmitter
{
public:
	typedef enum
	{
		EMITTERTYPE_ENEMY = 0,
		EMITTERTYPE_PLAYER,
		EMITTERTYPE_HOMING
	}EMITTERTYPE;

	CEmitter() {};
	~CEmitter() {};

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �Z�b�^�[
	void SetPos(const D3DXVECTOR3& pos) { m_pos = pos; }
	void SetSizeParticle(const D3DXVECTOR3& sizeParticle) { m_sizeParticle = sizeParticle; }
	void SetSpeedParticle(const float& speedParticle) { m_speedParticle = speedParticle; }
	void SetColorParticle(const D3DXCOLOR& colorParticle) { m_colorParticle = colorParticle; }
	void SetLifeParticle(const int& lifeParticle) { m_lifeParticle = lifeParticle; }
	void SetLife(const int& life) { m_life = life; }
	void SetAngleRange(const float& angleRange) { m_angleRange = angleRange; }
	void SetEmitPerFrame(const int& emitPerFrame) { m_emitPerFrame = emitPerFrame; }
	void SetFilePass(const char* filePass) { strcpy(m_filePass, filePass); }
	void SetDoUninit(const bool doUninit) { m_doUninit = doUninit; }
	void SetType(const EMITTERTYPE& type) { m_type = type; }
	void SetHomingBulletID(const int& homingBulletID) { m_homingBulletID = homingBulletID; }

	// �Q�b�^�[
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetSizeParticle(void) { return m_sizeParticle; }
	int GetLifeParticle(void) { return m_lifeParticle; }
	int GetEmitPerFrame(void) { return m_emitPerFrame; }
	float GetAngleRange(void) { return m_angleRange; }
	float GetSpeedParticle(void) { return m_speedParticle; }
	bool GetDoUninit(void) { return m_doUninit; }
	EMITTERTYPE GetType(void) { return m_type; }
	int GetHomingBulletID(void) { return m_homingBulletID; }

	static CEmitter* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& sizeParticle, const float& speedParticle, const D3DXCOLOR& colorParticle, const int& emitPerFrame, const int& lifeParticle, const int& life, const EMITTERTYPE& type);

private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_sizeParticle;
	D3DXCOLOR m_colorParticle;
	float m_speedParticle;
	float m_angleRange;
	int m_life;
	int m_lifeParticle;
	int m_emitPerFrame; // 1�t���[���Ƀp�[�e�B�N���𔭐������鐔
	int m_homingBulletID; // �z�[�~���O�e�ɕR�t�����邽�߂�ID
	bool m_doUninit;
	char m_filePass[256];
	EMITTERTYPE m_type;

};

#endif
