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
#include "particle.h"
#include "camera.h"
#include "light.h"

/*------------------------------------------------------------------------------
 　マクロ定義
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
  　デストラクタ
------------------------------------------------------------------------------*/
CParticle::~CParticle()
{
}

/*------------------------------------------------------------------------------
　初期化
------------------------------------------------------------------------------*/
void CParticle::Init(void)
{
	// パラメータ初期化
	m_acceleration = 1.0f;
	m_alphaDecay = 1.0f;

	// ビルボードの初期化
	CBillboard::Init();

	// オブジェクトタイプの設定
	SetObjType(OBJTYPE_NONE);
}

/*------------------------------------------------------------------------------
　終了処理
------------------------------------------------------------------------------*/
void CParticle::Uninit(void)
{
	CBillboard::Uninit();
	//CScene::Release();
	CScene::SetDelete();
}

/*------------------------------------------------------------------------------
　更新
------------------------------------------------------------------------------*/
void CParticle::Update(void)
{
	if (m_use)
	{
		m_velocity *= m_acceleration;
		m_color.a *= m_alphaDecay;
		m_alpha = m_color.a;
		m_pos += m_velocity;
	}

	m_life--;
	if (m_life <= 0)
	{
		SetUse(false);
	}

	CBillboard::Update();
}

/*------------------------------------------------------------------------------
　ポリゴン描画処理
------------------------------------------------------------------------------*/
void CParticle::Draw(void)
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
CParticle* CParticle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 velocity, D3DXCOLOR color, int life, CTextureManager::TEXTYPE textype)
{
	CParticle* pParticle = new CParticle(CScene::PRIORITY_BILLBOARD);

	// 初期化
	pParticle->SetPos(pos);
	pParticle->SetSize(size);
	pParticle->SetVelocity(velocity);
	pParticle->SetColor(D3DXCOLOR(255, 255, 255, 128));
	pParticle->SetLife(life);
	pParticle->SetUse(false);

	// テクスチャIDの取得
	pParticle->m_TexID = CTextureManager::GetTexID(textype);

	pParticle->Init();

	return pParticle;
}

