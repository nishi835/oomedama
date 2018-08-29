/*==============================================================================

textBox3Dのヘッダー [textBox3D.h]
作成者 : 中西　祐介
作成日 :
--------------------------------------------------------------------------------
■Update :
==============================================================================*/
#ifndef _TEXT_BOX3D_H_
#define _TEXT_BOX3D_H_

/*------------------------------------------------------------------------------
　ヘッダファイル
 ------------------------------------------------------------------------------*/
#include "textureManager.h"
#include "billboard.h"

 /*------------------------------------------------------------------------------
 　マクロ定義
  ------------------------------------------------------------------------------*/
#define TEXTBOX001_TEXTURENAME "data/TEXTURE/joubutsu.png"

  /*------------------------------------------------------------------------------
  　クラス
   ------------------------------------------------------------------------------*/
class CTextBox3D : public CBillboard
{
public:
	CTextBox3D(int Priority) : CBillboard(Priority) {};
	~CTextBox3D();

	void Init(void);
	void Uninit(void)override;
	void Update(void)override;
	void Draw(void)override;

	// セッター
	void SetEndPos(D3DXVECTOR3 endPos) { m_endPos = endPos; }
	void SetEndSize(D3DXVECTOR3 endSize) { m_endSize = endSize; }
	void SetVelocity(D3DXVECTOR3 velocity) { m_velocity = velocity; }
	void SetDeltaSize(D3DXVECTOR3 deltaSize) { m_deltaSize = deltaSize; }
	void SetTex(D3DXVECTOR2 tex) { m_tex = tex; }
	void SetTexSize(D3DXVECTOR2 texSize) { m_texSize = texSize; }
	void SetLife(int life) { m_life = life; }
	void SetDefaultLife(int defaultLife) { m_defaultLife = defaultLife; }
	void SetUse(bool use) { m_use = use; }

	void AddSize(D3DXVECTOR3 value) { m_size += value; }
	void AddLife(int value) { m_life += value; }

	// ゲッター
	D3DXVECTOR3 GetEndPos(void) { return m_endPos; }
	D3DXVECTOR3 GetEndSize(void) { return m_endSize; }
	D3DXVECTOR3 GetDeltaSize(void) { return m_deltaSize; }
	int GetLife(void) { return m_life; }
	bool GetUse(void) { return m_use; }

	// その他のメソッド
	static CTextBox3D* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 endPos, D3DXVECTOR3 endSize, int life, float alpha, char* filePass, CTextureManager::TEXTYPE textype);
	void Reset(void);

private:
	D3DXVECTOR3 m_velocity;
	D3DXVECTOR3 m_endPos;
	D3DXVECTOR3 m_endSize;
	D3DXVECTOR3 m_deltaSize;
	int m_life;
	int m_defaultLife;

	bool m_use;
};

#endif