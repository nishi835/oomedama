/*==============================================================================

laserParticle�̃w�b�_�[ [laserParticle.h]
�쐬�� : �����@�S��
�쐬�� :
--------------------------------------------------------------------------------
��Update :
==============================================================================*/
#ifndef _LASER_PARTICLE_H_
#define _LASER_PARTICLE_H_

/*------------------------------------------------------------------------------
�@�w�b�_�t�@�C��
------------------------------------------------------------------------------*/
#include "laserEmitter.h"
#include "textureManager.h"

/*------------------------------------------------------------------------------
 �@�}�N����`
------------------------------------------------------------------------------*/
#define MAX_PARTICLE (5120)
#define PARTICLE_TEXTURENAME "data/TEXTURE/bullet.png"

/*------------------------------------------------------------------------------
  �@�N���X
------------------------------------------------------------------------------*/
class CLaserParticle : public CBillboard
{
public:
	CLaserParticle(int Priority) : CBillboard(Priority) {};
	~CLaserParticle();

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �Z�b�^�[
	void SetVelocity(D3DXVECTOR3 velocity) { m_velocity = velocity; }
	void SetColor(D3DXCOLOR color) { m_color = color; }
	void SetLife(int life) { m_life = life; }
	void SetUse(bool use) { m_use = use; }

	// �Q�b�^�[
	D3DXVECTOR3 GetVelocity(void) { return m_velocity; }
	bool GetUse(void) { return m_use; }

	static CLaserParticle* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 velocity, float alpha, int life, char* filePass, CTextureManager::TEXTYPE textype);

private:
	D3DXVECTOR3 m_velocity;
	D3DXCOLOR m_color;
	int m_life;
	bool m_use;

};

#endif