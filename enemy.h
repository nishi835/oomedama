/*==============================================================================

    enemyのヘッダー [enemy.h]
                                                       作成者 : 中西　祐介
                                                       作成日 : 
--------------------------------------------------------------------------------
    ■Update : 
==============================================================================*/
#ifndef _ENEMY_H_
#define _ENEMY_H_

/*------------------------------------------------------------------------------
  　ヘッダファイル
------------------------------------------------------------------------------*/
#include "billboard.h"

/*------------------------------------------------------------------------------
  　マクロ定義
------------------------------------------------------------------------------*/
#define ENEMY001_TEXTURENAME "data/TEXTURE/gang02.png"
#define ENEMY_EXPLOSION_TEXTURENAME "data/TEXTURE/bullet.png"
#define MAX_ENEMY (15)
#define ENEMY_SIZE_SMALL_X (7.0f)
#define ENEMY_SIZE_SMALL_Y (7.0f)
#define ENEMY_SIZE_MIDDLE_X (15.0f)
#define ENEMY_SIZE_MIDDLE_Y (15.0f)
#define ENEMY_SIZE_LARGE_X (23.0f)
#define ENEMY_SIZE_LARGE_Y (23.0f)
#define ENEMY_EXPLOSION_SIZE (2.0f)
#define ENEMY_MOVE_SPEED (0.3f)

/*------------------------------------------------------------------------------
  　クラス
------------------------------------------------------------------------------*/
class CEnemy : public CBillboard
{
public:
	typedef enum
	{
		ENEMYTYPE_SMALL = 0,
		ENEMYTYPE_MIDDLE,
		ENEMYTYPE_LARGE
	}ENEMYTYPE;

	typedef enum {
		ENEMYMOVETYPE_UPDOWN = 0,
		ENEMYMOVETYPE_CIRCLE,
		ENEMYMOVETYPE_RANDOM,
		ENEMYMOVETYPE_HOMING
	}ENEMYMOVETYPE;

	CEnemy( int Priority ) : CBillboard( Priority ){};
	~CEnemy();
	
	void Init();
	void Uninit( void );
	void Update( void );
	void Draw( void );

	// ゲッター
	ENEMYTYPE GetType(void) { return m_type; }
	ENEMYMOVETYPE GetMoveType(void) { return m_moveType; }

    bool GetRockon(void) { return m_rockon; }
	int GetRockonID(void) { return m_rockonID; }
	int GetTimer(void) { return m_timer; }

	// セッター
	void SetType(ENEMYTYPE type) { m_type = type; }
	void SetMoveType(ENEMYMOVETYPE moveType) { m_moveType = moveType; }
	void SetRockon(bool rockon) { m_rockon = rockon; }
	void SetRockonID(int rockonID) { m_rockonID = rockonID; }
	void SetTimer(int timer) { m_timer = timer; }

	static CEnemy* Create( D3DXVECTOR3 pos, D3DXVECTOR3 size, ENEMYTYPE type, ENEMYMOVETYPE moveType, char* filePass);

private:
	D3DXVECTOR3 m_velocity;
	float m_rotX;
	float m_moveCount;
	ENEMYTYPE m_type;
	ENEMYMOVETYPE m_moveType;
	bool m_rockon;
	int m_rockonID;
	int m_timer;
	int m_sign; // 符号
};

#endif