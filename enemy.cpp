/*==============================================================================

    enemyの処理 [enemy.cpp]
                                                       作成者 : 中西　祐介
                                                       作成日 : 
--------------------------------------------------------------------------------
    ■Update : 
==============================================================================*/

/*------------------------------------------------------------------------------
  　ヘッダファイル
------------------------------------------------------------------------------*/
#include "main.h"
#include "modeGame.h"
#include "textureManager.h"
#include "renderer.h"
#include <time.h>

/*------------------------------------------------------------------------------
  　マクロ定義
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
  　デストラクタ
------------------------------------------------------------------------------*/
CEnemy::~CEnemy()
{
}

/*------------------------------------------------------------------------------
  　初期化
------------------------------------------------------------------------------*/
void CEnemy::Init()
{	
	// 初期化
	m_rockon = false;
	m_timer = 0;
	m_velocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotX = 0.0f;
	m_moveCount = 0.0f;
	m_sign = 1.0f;

	// 乱数初期化
	srand(unsigned(time(0)));

	// ビルボードの初期化
	CBillboard::Init();

	// オブジェクトタイプの設定
	SetObjType( OBJTYPE_MESHFIELD );
}

/*------------------------------------------------------------------------------
  　終了処理
------------------------------------------------------------------------------*/
void CEnemy::Uninit( void )
{
	CBillboard::Uninit();
	CScene::SetDelete();
}

/*------------------------------------------------------------------------------
  　更新
------------------------------------------------------------------------------*/
void CEnemy::Update( void )
{
	m_timer++;

	// 地面の高さ取得
	int height = CModeGame::GetMeshField()->GetHeight(m_pos);

	// 移動
	switch (m_moveType)
	{
	case ENEMYMOVETYPE_UPDOWN:
		if ((m_pos.y > 50.0f) || (m_pos.y <= height))
		{
			m_sign *= -1.0f;
		}
		m_velocity.y = ENEMY_MOVE_SPEED * m_sign;
		
		break;

	case ENEMYMOVETYPE_CIRCLE:
		m_rotX += 0.01f;
		m_velocity.x = cosf(m_rotX) * ENEMY_MOVE_SPEED;
		m_velocity.z = sinf(m_rotX) * ENEMY_MOVE_SPEED;
		break;

	case ENEMYMOVETYPE_RANDOM:
		if (m_moveCount == 0.0f)
		{
			m_velocity.x = rand() % 10 - 5;
			m_velocity.y = rand() % 10 - 5;
			m_velocity.z = rand() % 10 - 5;

			D3DXVec3Normalize(&m_velocity, &m_velocity);
		}

		m_moveCount += D3DXVec3Length(&m_velocity);

		if (m_moveCount > 50.0f)
		{
			m_moveCount = 0.0f;
		}

		break;

	case ENEMYMOVETYPE_HOMING:
		D3DXVECTOR3 vecPE = CModeGame::GetPlayer()->GetPos() - m_pos;
		D3DXVec3Normalize(&vecPE, &vecPE);

		m_velocity = vecPE * ENEMY_MOVE_SPEED * 0.5f;

		break;
	}

	// 移動
	m_pos += m_velocity;

	// 高さ調整
	if (m_pos.y < height)
	{
		m_pos.y = height;
	}
}

/*------------------------------------------------------------------------------
  　描画処理
------------------------------------------------------------------------------*/
void CEnemy::Draw( void )
{		
	CBillboard::Draw();
}

/*------------------------------------------------------------------------------
  　作成
------------------------------------------------------------------------------*/
CEnemy* CEnemy::Create( D3DXVECTOR3 pos, D3DXVECTOR3 size, ENEMYTYPE type, ENEMYMOVETYPE moveType, char* filePass)
{
	CEnemy* pEnemy = new CEnemy(CScene::PRIORITY_BILLBOARD);

	pEnemy->SetPos(pos);
	pEnemy->SetSize(size);
	pEnemy->SetType(type);
	pEnemy->SetMoveType(moveType);

	// テクスチャのロード
	pEnemy->SetTexID(CTextureManager::LoadTexture(filePass, CTextureManager::TEXTYPE_NONE));
	pEnemy->Init();

	return pEnemy;
}

