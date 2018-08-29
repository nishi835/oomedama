/*==============================================================================

bulletのヘッダー [bullet.h]
作成者 : 中西　祐介
作成日 :
--------------------------------------------------------------------------------
■Update :
==============================================================================*/
#ifndef _BULLET_H_
#define _BULLET_H_

//------------------------------------------------------------------------------
//　ヘッダファイル
//------------------------------------------------------------------------------
#include "billboard.h"
#include "textureManager.h"

//------------------------------------------------------------------------------
//　マクロ定義
//------------------------------------------------------------------------------
#define BULLET001_TEXTURENAME "data/TEXTURE/bullet.png"
#define MAX_BULLET (256)

//------------------------------------------------------------------------------
//  クラス
//------------------------------------------------------------------------------
class CBullet : public CBillboard
{
public:
	typedef enum
	{
		BULLETTYPE_NORMAL = 0,
		BULLETTYPE_HOMING,
		BULLETTYPE_MAX
	}BULLETTYPE;

	CBullet(int Priority) : CBillboard(Priority) {};
	~CBullet();

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// セッター
	void SetVelocity(D3DXVECTOR3 velocity) { m_velocity = velocity; }
	void SetTargetPos(D3DXVECTOR3 targetPos) { m_targetPos = targetPos; }
	void SetType(BULLETTYPE type) { m_type = type; }
	void SetUse(bool use) { m_use = use; }
	void SetDeltaRot(float deltaRot) { m_deltaRot = deltaRot; }
	void SetLife(float life) { m_life = life; }

	void AddDeltaRot(float value) { m_deltaRot += value; }
	void AddLife(float value) { m_life += value; }

	// ゲッター
	D3DXVECTOR3 GetVelocity(void) { return m_velocity; }
	D3DXVECTOR3 GetTargetPos(void) { return m_targetPos; }
	BULLETTYPE GetType(void) { return m_type; }
	bool GetUse(void) { return m_use; }
	float GetDeltaRot(void) { return m_deltaRot; }
	int GetLife(void) { return m_life; }

	// その他のメソッド
	static CBullet* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 velocity, bool use, char* filePass, CTextureManager::TEXTYPE textype);

private:
	D3DXVECTOR3 m_velocity;
	D3DXVECTOR3 m_targetPos;
	BULLETTYPE m_type;
	float m_deltaRot;
	int m_life;
	bool m_use;
};

#endif