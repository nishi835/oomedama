/*==============================================================================

    particle�̃w�b�_�[ [particle.h]
                                                       �쐬�� : �����@�S��
                                                       �쐬�� : 
--------------------------------------------------------------------------------
    ��Update : 
==============================================================================*/
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

/*------------------------------------------------------------------------------
  �@�w�b�_�t�@�C��
------------------------------------------------------------------------------*/
#include "emitter.h"
#include "textureManager.h"

/*------------------------------------------------------------------------------
  �@�}�N����`
------------------------------------------------------------------------------*/
#define MAX_PARTICLE (5120)
#define PARTICLE001_TEXTURENAME "data/TEXTURE/bullet.png"
#define HOMING_PARTICLE_SIZE (0.5f)

/*------------------------------------------------------------------------------
  �@�N���X
------------------------------------------------------------------------------*/
class CParticle : public CBillboard
{
public: 
	CParticle( int Priority ) : CBillboard( Priority ){};
	~CParticle();
	
	void Init(void);
	void Uninit( void );
	void Update( void );
	void Draw( void );

	// �Z�b�^�[
	void SetVelocity(D3DXVECTOR3 velocity) { m_velocity = velocity; }
	void SetColor(D3DXCOLOR color) { m_color = color; }
	void SetLife(int life) { m_life = life; }
	void SetUse(bool use) { m_use = use; }
	void SetAcceleration(float acceleration) { m_acceleration = acceleration; }
	void SetAlphaDecay(float alphaDecay) { m_alphaDecay = alphaDecay; }

	// �Q�b�^�[
	bool GetUse(void) { return m_use; }

	static CParticle* Create( D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 velocity, D3DXCOLOR color, int life, CTextureManager::TEXTYPE textype);

private:
	D3DXVECTOR3 m_velocity;
	D3DXCOLOR m_color;
	float m_speed;
	float m_acceleration;
	float m_alphaDecay;
	int m_life;
	bool m_use;
};

#endif