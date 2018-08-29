/*==============================================================================

rockonのヘッダー [rockon.h]
作成者 : 中西　祐介
作成日 :
--------------------------------------------------------------------------------
■Update :
==============================================================================*/
#ifndef _ROCKON_H_
#define _ROCKON_H_

//------------------------------------------------------------------------------
//  ヘッダファイル
//------------------------------------------------------------------------------
#include "billboard.h"

//------------------------------------------------------------------------------
//  マクロ定義
//------------------------------------------------------------------------------
#define ROCKON001_TEXTURENAME "data/TEXTURE/rockon.png"
#define MAX_ROCKON (15)
#define ROCKON_SIZE_X (7.0f)
#define ROCKON_SIZE_Y (7.0f)

//------------------------------------------------------------------------------
//  クラス
//------------------------------------------------------------------------------
class CRockon : public CBillboard
{
public:
	CRockon(int Priority) : CBillboard(Priority) {};
	~CRockon();

	void Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// ゲッター
	bool GetUse(void) { return m_use; }
	int GetTimer(void) { return m_timer; }
	int GetRockonID(void) { return m_rockonID; }

	// セッター
	void SetUse(bool use) { m_use = use; }
	void SetRockonID(int rockonID) { m_rockonID = rockonID; }

	static CRockon* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int rockonID, char* filePass);

private:
	int m_timer;
	int m_rockonID;
	bool m_use;

};

#endif