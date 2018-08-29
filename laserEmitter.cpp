/*==============================================================================

laserEmitterの処理 [laserEmitter.cpp]
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
#include "laserEmitter.h"
#include "particle.h"
#include <stdio.h>

/*------------------------------------------------------------------------------
 　マクロ定義
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
  　初期化
------------------------------------------------------------------------------*/
void CLaserEmitter::Init(void)
{
}

/*------------------------------------------------------------------------------
　終了処理
------------------------------------------------------------------------------*/
void CLaserEmitter::Uninit(void)
{
	CScene::SetDelete();
}

/*------------------------------------------------------------------------------
　更新
------------------------------------------------------------------------------*/
void CLaserEmitter::Update(void)
{
	// 移動
	m_pos += m_velocity;

	// パーティクルの作成
	CLaserParticle** pLaserParticle = CModeGame::GetLaserParticle();

	for (int j = 0; j < MAX_PARTICLE; j++)
	{
		if (pLaserParticle == NULL) break;

		if (pLaserParticle[j]->GetUse() == false)
		{
			pLaserParticle[j]->SetPos(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z));
			pLaserParticle[j]->SetSize(m_sizeParticle);
			pLaserParticle[j]->SetVelocity(D3DXVECTOR3(0.0f, 0.0f, 0.0f)/*m_velocityParticle*/);
			pLaserParticle[j]->SetColor(m_colorParticle);
			pLaserParticle[j]->SetLife(m_lifeParticle);
			pLaserParticle[j]->SetUse(true);

			break;
		}
	}

	m_life--;

	if (m_life <= 0)
	{
		SetDoUninit(true);
	}

	char str[128];
	sprintf(str, "LaserEmitter pos.x = %.5f\n", m_pos.x);
	CDebug::AddText(str);
}

/*------------------------------------------------------------------------------
　描画処理
 ------------------------------------------------------------------------------*/
void CLaserEmitter::Draw(void)
{
}

/*------------------------------------------------------------------------------
　作成
 ------------------------------------------------------------------------------*/
CLaserEmitter* CLaserEmitter::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& velocity, const D3DXVECTOR3& velocityParticle, const D3DXVECTOR3& sizeParticle, const D3DXCOLOR& colorParticle, const int& lifeParticle, const int& life, const char* filePass)
{
	CLaserEmitter* pLaserEmitter = new CLaserEmitter(CScene::PRIORITY_BILLBOARD);

	pLaserEmitter->SetPos(pos);
	pLaserEmitter->SetVelocity(velocity);
	pLaserEmitter->SetSizeParticle(sizeParticle);
	pLaserEmitter->SetColorParticle(colorParticle);
	pLaserEmitter->SetLifeParticle(lifeParticle);
	pLaserEmitter->SetLife(life);
	pLaserEmitter->SetDoUninit(false);

	pLaserEmitter->Init();

	return pLaserEmitter;
}
