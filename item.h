/*==============================================================================

itemのヘッダー [item.h]
作成者 : 中西　祐介
作成日 :
--------------------------------------------------------------------------------
■Update :
==============================================================================*/
#ifndef _ITEM_H_
#define _ITEM_H_

/*------------------------------------------------------------------------------
　ヘッダファイル
------------------------------------------------------------------------------*/
#include "billboard.h"

/*------------------------------------------------------------------------------
 　マクロ定義
------------------------------------------------------------------------------*/
#define MAX_ITEM (50)
#define ITEM_SIZE_X (7.0f)
#define ITEM_SIZE_Y (7.0f)
#define ITEM_VALUE_ENERGY (10)

/*------------------------------------------------------------------------------
  　クラス
------------------------------------------------------------------------------*/
class CItem : public CBillboard
{
public:
	CItem(int Priority) : CBillboard(Priority) {};
	~CItem();

	void Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, float velY);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CItem* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float velY, float alpha, char* filePass, CTextureManager::TEXTYPE textype);
	
private:
	float m_velocityY;

};

#endif