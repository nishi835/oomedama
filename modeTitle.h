/*==============================================================================

    modeTitleのヘッダー [modeTitle.h]
                                                       作成者 : 中西　祐介
                                                       作成日 : 
--------------------------------------------------------------------------------
    ■Update : 
==============================================================================*/
#ifndef _MODE_TITLE_H_
#define _MODE_TITLE_H_

/*------------------------------------------------------------------------------
  　ヘッダファイル
------------------------------------------------------------------------------*/
#include "mode.h"
#include "cursorTitle.h"

/*------------------------------------------------------------------------------
  　マクロ定義
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
  　クラス
------------------------------------------------------------------------------*/
class CModeTitle: public CMode
{
public:
	CModeTitle() {};
	~CModeTitle() ;
	
	void Init( void)override;
	void Uninit( void )override;
	void Update( void )override;
	void Draw( void )override;
	
	// ゲッター

	// その他のメソッド
	
private:
	// オブジェクト
	static CCursorTitle* m_cursorTitle;

	// その他
};

#endif