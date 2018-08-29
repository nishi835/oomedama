/*==============================================================================

emitterの処理 [emitter.cpp]
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
#include "particle.h"
#include <time.h>

/*------------------------------------------------------------------------------
 　マクロ定義
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
　初期化
------------------------------------------------------------------------------*/
void CEmitter::Init(void)
{
	srand((unsigned)time(0));	// 乱数設定
}

/*------------------------------------------------------------------------------
　終了処理
------------------------------------------------------------------------------*/
void CEmitter::Uninit(void)
{
}

/*------------------------------------------------------------------------------
　更新
------------------------------------------------------------------------------*/
void CEmitter::Update(void)
{
	m_life--;

	if (m_life <= 0)
	{
		SetDoUninit(true);
	}
}

/*------------------------------------------------------------------------------
　ポリゴン描画処理
------------------------------------------------------------------------------*/
void CEmitter::Draw(void)
{
}

/*------------------------------------------------------------------------------
　作成
------------------------------------------------------------------------------*/
CEmitter* CEmitter::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& sizeParticle, const float& speedParticle, const D3DXCOLOR& colorParticle, const int& emitPerFrame, const int& lifeParticle, const int& life, const EMITTERTYPE& type)
{
	CEmitter* pEmitter = new CEmitter();

	pEmitter->SetPos(pos);
	pEmitter->SetSizeParticle(sizeParticle);
	pEmitter->SetSpeedParticle(speedParticle);
	pEmitter->SetColorParticle(colorParticle);
	pEmitter->SetEmitPerFrame(emitPerFrame);
	pEmitter->SetLifeParticle(lifeParticle);
	pEmitter->SetLife(life);
	pEmitter->SetType(type);
	pEmitter->SetDoUninit(false);

	pEmitter->Init();

	return pEmitter;
}
