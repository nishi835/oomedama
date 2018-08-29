/*==============================================================================

backgroundのヘッダー [background.h]
作成者 : 中西　祐介
作成日 :
--------------------------------------------------------------------------------
■Update :
==============================================================================*/
#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

/*------------------------------------------------------------------------------
　ヘッダファイル
------------------------------------------------------------------------------*/
#include "scene2D.h"
#include "textureManager.h"

/*------------------------------------------------------------------------------
  マクロ定義
------------------------------------------------------------------------------*/
#define TITLE001_TEXTURENAME "data/TEXTURE/title.png"
#define RESULT_TEXTURENAME "data/TEXTURE/result.png"

/*------------------------------------------------------------------------------
　クラス
------------------------------------------------------------------------------*/
class CBackground : public CScene2D
{
public:
	CBackground(int Priority) : CScene2D(Priority) {};
	~CBackground() {};

	void Init(void);
	void Uninit(void)override;
	void Update(void)override;
	void Draw(void)override;

	// セッター

	// ゲッター

	// その他のメソッド
	static CBackground* CBackground::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float alpha, char* filePass);

private:
};

#endif