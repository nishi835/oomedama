/*==============================================================================

    gameのヘッダー [modeGame.h]
                                                       作成者 : 中西　祐介
                                                       作成日 : 
--------------------------------------------------------------------------------
    ■Update : 
==============================================================================*/
#ifndef _GAME_H_
#define _GAME_H_

/*------------------------------------------------------------------------------
  　ヘッダファイル
------------------------------------------------------------------------------*/
#include <vector>
#include "meshField.h"
#include "mode.h"
#include "camera.h"
#include "light.h"
#include "score.h"
#include "emitter.h"
#include "particle.h"
#include "laserEmitter.h"
#include "laserParticle.h"
#include "player.h"
#include "bullet.h"
#include "homingBullet.h"
#include "meshDome.h"
#include "gang.h"
#include "weed.h"
#include "enemy.h"
#include "debug.h"
#include "item.h"
#include "tombstone.h"
#include "textBox.h"
#include "textBox3D.h"
#include "rockon.h"
#include "mediator.h"

/*------------------------------------------------------------------------------
  　マクロ定義
------------------------------------------------------------------------------*/
#define GAME_CLEAR_SCORE (100)
#define MAX_NIRVANA (64)
#define TIMER_LIMIT (600)
#define CLEARTEXT_TEXTURENAME "data/TEXTURE/cleartext.png"
#define STARTTEXT_TEXTURENAME "data/TEXTURE/starttext.png"
#define GAMEOVERTEXT_TEXTURENAME "data/TEXTURE/gameovertext.png"
#define NIRVANA_TEXTURENAME "data/TEXTURE/joubutsu.png"
#define HITMESSAGE_TEXTURENAME "data/TEXTURE/hitmessage.png"
#define TIME_TEXTURENAME "data/TEXTURE/jikan.png"

/*------------------------------------------------------------------------------
  　クラス
------------------------------------------------------------------------------*/
class CModeGame : public CMode
{
public:
	typedef enum
	{
		STEP_1 = 0,
		STEP_2,
		STEP_3,
		STEP_4
	}GAMESTEP;
	
	CModeGame() {};
	~CModeGame() ;
	
	void Init( void)override;
	void Uninit( void )override;
	void Update( void )override;
	void Draw( void )override;
	
	// ゲッター
	static CCamera* GetCamera(void) { if(m_Camera != NULL) return m_Camera; }
	static CMeshField* GetMeshField(void) { if(m_MeshField != NULL) return m_MeshField; }
	static CPlayer* GetPlayer(void) { if(m_Player != NULL) return m_Player; }
	static CParticle** GetParticle(void) { if(&m_Particle[0] != NULL) return &m_Particle[0]; }
	static CItem** GetItem(void) { if (&m_Item[0] != NULL) return &m_Item[0]; }
	static CLaserParticle** GetLaserParticle(void) { if (m_LaserParticle[0] != NULL) return &m_LaserParticle[0]; }
	static CEnemy** GetEnemy(void) { return &m_Enemy[0]; }
	static POINT GetCurPos(void) { return m_cursorPos; }

	// セッター
	static void SetRockon(CRockon* pRockon)
	{ 
		m_Rockon.push_back(pRockon);
	}

	static void SetMediator(CMediator* pMediator)
	{
		m_Mediator.push_back(pMediator);
	}

	// その他のメソッド
	void CameraFollowPlayer(void);
	void RotationCamera(void);
	void CollisionBulletAndEnemy(void);
	void CollisionHomingBulletAndEnemy(void);
	void CollisionLaserAndEnemy(void);
	void CollisionPlayerAndItem(void);
	void CollisionPlayerAndBullet(void);
	void DivisionEnemy(D3DXVECTOR3 pos, CEnemy::ENEMYTYPE type, CEnemy::ENEMYMOVETYPE moveType);
	void OperationPlayer(void);
	void OperationEnemy(void);
	void CheckUninit(void);  // 終了フラグのチェック
	void DoNullPointer(void); // フラグをチェックしてModeGameの持つポインターをNullにする
	void UpdateText(void);
	void UpdateTimer(void);
	void UpdateEmitter(void);
	void UpdateBullet(void);
	void Load(void);

private:
	// インフラ系
	static CLight* m_Light;
	static CCamera* m_Camera;
	static CDebug* m_Debug;

	// オブジェクト
	static CMeshField* m_MeshField;
	static CMeshDome* m_MeshDome;
	static CPlayer* m_Player;
	static CBullet* m_Bullet[MAX_BULLET];
	static CBullet* m_EnemyBullet[MAX_BULLET];
	static CHomingBullet* m_HomingBullet[MAX_HOMING_BULLET];
	static CGang* m_Gang;
	static CWeed* m_Weed[MAX_WEED];
	static CEnemy* m_Enemy[MAX_ENEMY];
	static CItem* m_Item[MAX_ITEM];
	static CTombstone* m_Tombstone[MAX_TOMBSTONE];
	static std::vector<CRockon*> m_Rockon;
	static std::vector<CMediator*> m_Mediator;

	// UI
	static CScore* m_Score;
	static CScore* m_Timer;
	static CTextBox* m_StartText; 
	static CTextBox* m_ClearText;
	static CTextBox* m_GameOverText;
	static CTextBox3D* m_Nirvana[MAX_NIRVANA];

	// その他
	static CEmitter* m_Emitter[MAX_EMITTER];
	static CParticle* m_Particle[MAX_PARTICLE];
	static CParticle* m_HitParticle[MAX_PARTICLE];
	static CLaserEmitter* m_LaserEmitter;
	static CLaserParticle* m_LaserParticle[MAX_PARTICLE];
	static POINT m_cursorPos;

	GAMESTEP m_step;
	int m_timer;
	int m_gameTimer;
};

#endif