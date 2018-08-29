/*==============================================================================

cursorTitleのヘッダー [cursorTitle.h]
作成者 : 中西　祐介
作成日 :
--------------------------------------------------------------------------------
■Update :
==============================================================================*/
#ifndef _CURSORTITLE_H_
#define _CURSORTITLE_H_

//------------------------------------------------------------------------------
//  ヘッダファイル
//------------------------------------------------------------------------------
#include "textureManager.h"
#include "scene2D.h"

//------------------------------------------------------------------------------
// マクロ定義
//------------------------------------------------------------------------------
#define NIRVANA_TEXTURENAME "data/TEXTURE/joubutsu.png"

//------------------------------------------------------------------------------
//  クラス
//------------------------------------------------------------------------------
class CCursorTitle : public CScene2D
{
public:
	CCursorTitle(int Priority) : CScene2D(Priority) {};
	~CCursorTitle();

	void Init(void);
	void Uninit(void)override;
	void Update(void)override;
	void Draw(void)override;

	// セッター
	void SetUse(bool use) { m_use = use; }
	void SetPosition(int position) { m_position = position; }
	void AddPosition(int value) { m_position += value; }

	// ゲッター
	bool GetUse(void) { return m_use; }
	int GetPosition(void) { return m_position; }

	// その他のメソッド
	static CCursorTitle* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float alpha, char* filePass, CTextureManager::TEXTYPE textype);

private:
	int m_position;

	bool m_use;
};

#endif