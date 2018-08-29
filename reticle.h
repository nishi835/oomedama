/*==============================================================================

reticleのヘッダー [reticle.h]
作成者 : 中西　祐介
作成日 :
--------------------------------------------------------------------------------
■Update :
==============================================================================*/
#ifndef _RETICLE_H_
#define _RETICLE_H_

//------------------------------------------------------------------------------
//  ヘッダファイル
//------------------------------------------------------------------------------
#include "billboard.h"

//------------------------------------------------------------------------------
//  マクロ定義
//------------------------------------------------------------------------------
#define RETICLE001_TEXTURENAME "data/TEXTURE/reticle.png"
#define MAX_RETICLE (1)
#define RETICLE_SIZE_X (7.0f)
#define RETICLE_SIZE_Y (7.0f)
#define RETICLE_DISTANCE_FROM_PLAYER (150.0f)

//------------------------------------------------------------------------------
//  クラス
//------------------------------------------------------------------------------
class CReticle : public CBillboard
{
public:
	CReticle(int Priority) : CBillboard(Priority) {};
	~CReticle();

	void Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// ゲッター

	// セッター

	static CReticle* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, char* filePass);

private:
	int m_rockonID;

};

#endif
