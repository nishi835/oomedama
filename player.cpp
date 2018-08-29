/*==============================================================================

    playerの処理 [player.cpp]
                                                       作成者 : 中西　祐介
                                                       作成日 : 
--------------------------------------------------------------------------------
    ■Update : 
==============================================================================*/

/*------------------------------------------------------------------------------
  　ヘッダファイル
------------------------------------------------------------------------------*/
#include "main.h"
#include "manager.h"
#include "modeGame.h"
#include "renderer.h"
#include "camera.h"
#include "light.h"
#include "player.h"
#include "bullet.h"
#include "sceneModel.h"
#include "collision.h"

/*------------------------------------------------------------------------------
  　マクロ定義
------------------------------------------------------------------------------*/
#define PLAYER_ACCELERATION (0.15f)  // 移動の加速度
#define PLAYER_NUM_TEX (2)

/*------------------------------------------------------------------------------
  　デストラクタ
------------------------------------------------------------------------------*/
CPlayer::~CPlayer()
{
}

/*------------------------------------------------------------------------------
  　初期化
------------------------------------------------------------------------------*/
void CPlayer::Init(void)
{
	// パラメータ初期化
	m_timer = 0; 
	m_parallelVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_speed = PLAYER_SPEED;
	m_hit = false;
	m_doDraw = true;

	// シーンモデルの初期化
	CSceneModel::Init();

	// 移動ベクトルの設定
	m_velocity.x = cosf(m_rotFai) * PLAYER_ACCELERATION * sinf(m_rotThe);
	m_velocity.y = sinf(m_rotFai) * PLAYER_ACCELERATION;
	m_velocity.z = cosf(m_rotFai) * PLAYER_ACCELERATION * cosf(m_rotThe);

	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	LPD3DXMESH pCloneMesh;
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;
	VERTEX_3D* pVertex;

	// メッシュの取得
	m_pMeshModel->CloneMeshFVF(D3DXMESH_MANAGED, FVF_VERTEX_3D, pDevice, &pCloneMesh);

	// 頂点数のカウント
	int count = pCloneMesh->GetNumVertices();

	// 頂点バッファ取得
	pCloneMesh->GetVertexBuffer(&pVtxBuff);
	
	// 頂点バッファをロック
	VERTEX_3D* vertex;
	pVtxBuff->Lock(0, 0, (void**)&vertex, 0);

	// 半径の取得
	D3DXVECTOR3 temp;
	float len = 0;
	m_radius = 0;
	for (int i = 0; i < count; i++)
	{
		temp = vertex[i].pos;
		len = D3DXVec3Length(&temp);
		m_radius = max(len, m_radius);
	}

	// オブジェクトタイプの設定
	SetObjType( OBJTYPE_PLAYER );
}

/*------------------------------------------------------------------------------
  　終了処理
------------------------------------------------------------------------------*/
void CPlayer::Uninit( void )
{
	CScene::Uninit();
}

/*------------------------------------------------------------------------------
  　更新
------------------------------------------------------------------------------*/
void CPlayer::Update(void)
{
	// 移動スピード調整
	if (m_speed > 1.5f)
	{
		m_speed = 1.5f;
	}

	if (m_speed < 0.0001f)
	{
		m_speed = 0.0001f;
		m_move = false;
	}

	// 移動ベクトルの設定
	m_velocity.x = cosf(m_rotFai) * m_speed * sinf(m_rotThe);
	m_velocity.y = sinf(m_rotFai) * m_speed;
	m_velocity.z = cosf(m_rotFai) * m_speed * cosf(m_rotThe);
	
	// 移動
	if (m_move) 
	{
		m_pos += m_velocity; 
		m_pos += m_parallelVec;
	}

	m_parallelVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = true;

	// 高さ設定	
	float tempH = CModeGame::GetMeshField()->GetHeight(m_pos);
	if (m_pos.y < tempH) { m_pos.y = tempH; }

	if (m_timer > 60)
	{
		m_hit = false;
	}

	// タイマー更新
	m_timer++;

	// デバッグ表示
	char str[128];
	sprintf(str, "Player pos.x = %.5f\n", m_pos.x);
	CDebug::AddText(str);
}

/*------------------------------------------------------------------------------
  　ポリゴン描画処理
------------------------------------------------------------------------------*/
void CPlayer::Draw( void )
{	
	if (m_doDraw == false) return;

	CSceneModel::Draw();
}

/*------------------------------------------------------------------------------
  　作成
------------------------------------------------------------------------------*/
CPlayer* CPlayer::Create( D3DXVECTOR3 pos,  D3DXVECTOR3 velocity, float rotThe, float rotFai, int energy, int hitpoint, char* filePass)
{
	CPlayer* pPlayer = new CPlayer(CScene::PRIORITY_3D);

	pPlayer->SetPos(pos);
	pPlayer->SetVelocity(velocity);
	pPlayer->SetRotThe(rotThe);
	pPlayer->SetRotFai(rotFai);	
	pPlayer->SetEnergy(energy);
	pPlayer->SetHitpoint(hitpoint);
	pPlayer->SetFilePass(filePass);

	pPlayer->Init();
	return pPlayer;
}

