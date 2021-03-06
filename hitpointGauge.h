/*==============================================================================

hitpointGaugeのヘッダー [hitpointGauge.h]
作成者 : 中西　祐介
作成日 :
--------------------------------------------------------------------------------
■Update :
==============================================================================*/
#ifndef _HITPOINT_GAUGE_H_
#define _HITPOINT_GAUGE_H_

/*------------------------------------------------------------------------------
　ヘッダファイル
 ------------------------------------------------------------------------------*/
#include "textureManager.h"
#include "scene2D.h"

 /*------------------------------------------------------------------------------
 　マクロ定義
  ------------------------------------------------------------------------------*/
#define HITPOINT_TEXTURENAME "data/TEXTURE/tairyoku.png"

  /*------------------------------------------------------------------------------
  　クラス
   ------------------------------------------------------------------------------*/
class CHitpointGauge : public CScene2D
{
public:
	CHitpointGauge(int Priority) : CScene2D(Priority) {};
	~CHitpointGauge();

	void Init(void);
	void Uninit(void)override;
	void Update(void)override;
	void Draw(void)override;

	// セッター
	void SetEndSize(D3DXVECTOR3 endSize) { m_endSize = endSize; }
	void SetDeltaSize(D3DXVECTOR3 deltaSize) { m_deltaSize = deltaSize; }
	void SetPosX(float posx) { m_pos.x = posx; }
	void SetSizeX(float sizex) { m_size.x = sizex; }

	void AddSize(D3DXVECTOR3 value) { m_size += value; }

	// ゲッター
	D3DXVECTOR3 GetEndSize(void) { return m_endSize; }
	D3DXVECTOR3 GetDeltaSize(void) { return m_deltaSize; }

	// その他のメソッド
	static CHitpointGauge* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float alpha, char* filePass, CTextureManager::TEXTYPE textype);

private:
	D3DXVECTOR3 m_endSize;
	D3DXVECTOR3 m_deltaSize;
};

#endif
