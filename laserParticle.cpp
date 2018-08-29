/*==============================================================================

particleの処理 [particle.cpp]
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
#include "laserParticle.h"
#include "camera.h"
#include "light.h"

/*------------------------------------------------------------------------------
 　マクロ定義
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
  デストラクタ
------------------------------------------------------------------------------*/
CLaserParticle::~CLaserParticle()
{
}

/*------------------------------------------------------------------------------
　初期化
------------------------------------------------------------------------------*/
void CLaserParticle::Init(void)
{
	// ビルボードの初期化
	CBillboard::Init();

	// オブジェクトタイプの設定
	SetObjType(OBJTYPE_NONE);
}

/*------------------------------------------------------------------------------
　終了処理
------------------------------------------------------------------------------*/
void CLaserParticle::Uninit(void)
{
	CBillboard::Uninit();
	CScene::SetDelete();
}

/*------------------------------------------------------------------------------
　更新
------------------------------------------------------------------------------*/
void CLaserParticle::Update(void)
{
	if (m_use)
	{
		m_pos += m_velocity;
		CBillboard::Update();
	}

	m_life--;
	if (m_life <= 0)
	{
		SetUse(false);
	}
	
	char str[128];
	//sprintf(str, "LaserParticle size.x = %.5f\n", m_size.x);
	//CDebug::AddText(str);
}

/*------------------------------------------------------------------------------
　ポリゴン描画処理
------------------------------------------------------------------------------*/
void CLaserParticle::Draw(void)
{
	if (m_use)
	{
		// デバイスのポインタ取得
		LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

		// 加算合成に切り替え
		pDevice->SetRenderState(D3DRS_DESTBLEND,	// 設定名(インデックス)	D3DRS_DESTBLEND：背景のアルファ設定
			D3DBLEND_ONE);		// 設定値

		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);	// Ｚバッファをオフ

		CBillboard::Draw();

		// 乗算合成に切り替え
		pDevice->SetRenderState(D3DRS_DESTBLEND,		// 設定名(インデックス)	D3DRS_DESTBLEND：背景のアルファ設定
			D3DBLEND_INVSRCALPHA);	// 設定値	D3DBLEND_INVSRCALPHA：１－α

		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);	// Ｚバッファを元に戻す
	}
}

/*------------------------------------------------------------------------------
　作成
------------------------------------------------------------------------------*/
CLaserParticle* CLaserParticle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 velocity, float alpha, int life, char* filePass, CTextureManager::TEXTYPE textype)
{
	CLaserParticle* pParticle = new CLaserParticle(CScene::PRIORITY_BILLBOARD);

	// 初期化
	pParticle->SetPos(pos);
	pParticle->SetSize(size);
	pParticle->SetAlpha(alpha);
	pParticle->SetLife(life);
	pParticle->SetUse(false);

	// テクスチャIDの取得
	pParticle->m_TexID = CTextureManager::GetTexID(textype);

	pParticle->Init();

	return pParticle;
}

