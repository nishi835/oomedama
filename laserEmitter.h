/*==============================================================================

laserEmitterのヘッダー [laserEmitter.h]
作成者 : 中西　祐介
作成日 :
--------------------------------------------------------------------------------
■Update :
==============================================================================*/
#ifndef _LASER_EMITTER_H_
#define _LASER_EMITTER_H_

/*------------------------------------------------------------------------------
　ヘッダファイル
------------------------------------------------------------------------------*/
#include "billboard.h"
#include <string.h>

/*------------------------------------------------------------------------------
 　マクロ定義
------------------------------------------------------------------------------*/
#define MAX_EMITTER (128)
#define LASEREMITTER_SPEED (15.0f)

/*------------------------------------------------------------------------------
  　クラス
------------------------------------------------------------------------------*/
class CLaserEmitter: public CScene
{
public:
	CLaserEmitter(int Priority) : CScene(Priority) {};
	~CLaserEmitter() {};

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// セッター
	void SetVelocity(const D3DXVECTOR3& velocity) { m_velocity = velocity; }
	void SetVelocityParticle(const D3DXVECTOR3& velocityParticle) { m_velocityParticle = velocityParticle; }
	void SetSizeParticle(const D3DXVECTOR3& sizeParticle) { m_sizeParticle = sizeParticle; }
	void SetColorParticle(const D3DXCOLOR& colorParticle) { m_colorParticle = colorParticle; }
	void SetLifeParticle(const int& lifeParticle) { m_lifeParticle = lifeParticle; }
	void SetLife(const int& life) { m_life = life; }
	void SetFilePass(const char* filePass) { strcpy(m_filePass, filePass); }

	// ゲッター
	bool GetDoUninit(void) { return m_doUninit; }

	static CLaserEmitter* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& velocity, const D3DXVECTOR3& m_velocityParticle, const D3DXVECTOR3& sizeParticle, const D3DXCOLOR& colorParticle, const int& lifeParticle, const int& life, const char* filePass);

private:
	D3DXVECTOR3 m_velocity;
	D3DXVECTOR3 m_velocityParticle;
	D3DXVECTOR3 m_sizeParticle;
	D3DXCOLOR m_colorParticle;
	int m_life;
	int m_lifeParticle;
	bool m_doUninit;
	char m_filePass[256];
};

#endif
