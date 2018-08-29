/*==============================================================================

    modeTitleの処理 [modeTitle.cpp]
                                                       作成者 : 中西　祐介
                                                       作成日 : 
--------------------------------------------------------------------------------
    ■Update : 
==============================================================================*/

/*------------------------------------------------------------------------------
  　ヘッダファイル
------------------------------------------------------------------------------*/
#include "main.h"
#include "manager.h"
#include "modeTitle.h"
#include "modeTutorial.h"
#include "textureManager.h"
#include  "filepassHeader.h"
#include "sound.h"
#include "background.h"
#include "cursorTitle.h"

/*------------------------------------------------------------------------------
　マクロ
------------------------------------------------------------------------------*/

//------------------------------------------------------------------------------
//　静的メンバ変数
//------------------------------------------------------------------------------
// オブジェクト
CCursorTitle* CModeTitle::m_cursorTitle = NULL;
// その他

/*------------------------------------------------------------------------------
  　デストラクタ
------------------------------------------------------------------------------*/
CModeTitle::~CModeTitle()
{
}

/*------------------------------------------------------------------------------
  　初期化
------------------------------------------------------------------------------*/
void CModeTitle::Init(void)
{
	// テクスチャ読み込み //////////////////////////////////////////////
	
	// インスタンス生成 /////////////////////////////////////////////////

	// オブジェクト
	CBackground::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), 1.0f, TITLE001_TEXTURENAME);
	m_cursorTitle = CCursorTitle::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.63f, SCREEN_HEIGHT * 0.6f, 0.0f), D3DXVECTOR3(35.0f, 35.0f, 0.0f), 1.0f, CURSORTITLE_TEXTURENAME, CTextureManager::TEXTYPE_NONE);

	// その他

	PlaySound(SOUND_LABEL_BGM000);
}

/*------------------------------------------------------------------------------
  　終了処理
------------------------------------------------------------------------------*/
void CModeTitle::Uninit( void )
{
	CScene::ReleaseAll();	

	StopSound(SOUND_LABEL_BGM000);
}

/*------------------------------------------------------------------------------
  　更新
------------------------------------------------------------------------------*/
void CModeTitle::Update(void)
{
	// カーソル移動
	if (CManager::GetInputKeyboard()->GetKeyTrigger(DIK_UP))
	{
		m_cursorTitle->AddPosition(-1);

		if (m_cursorTitle->GetPosition() < 0)
		{
			m_cursorTitle->SetPosition(1);
			m_cursorTitle->AddPos(D3DXVECTOR3(0.0f, 80.0f, 0.0f));
		}
		else
		{
			m_cursorTitle->AddPos(D3DXVECTOR3(0.0f, -80.0f, 0.0f));
		}
	}

	if (CManager::GetInputKeyboard()->GetKeyTrigger(DIK_DOWN))
	{
		m_cursorTitle->AddPosition(1);

		if (m_cursorTitle->GetPosition() > 1)
		{
			m_cursorTitle->SetPosition(0);
			m_cursorTitle->AddPos(D3DXVECTOR3(0.0f, -80.0f, 0.0f));
		}
		else 
		{
			m_cursorTitle->AddPos(D3DXVECTOR3(0.0f, 80.0f, 0.0f));
		}
	}
	
	// ゲームモード変更
	if (CManager::GetInputKeyboard()->GetKeyTrigger(DIK_SPACE))
	{
		if (m_cursorTitle->GetPosition() == 0)
		{
			CManager::Fade(new CModeGame);
		}
		else if (m_cursorTitle->GetPosition() == 1)
		{
			CManager::Fade(new CModeTutorial);
		}
	}
}

/*------------------------------------------------------------------------------
  　描画処理
------------------------------------------------------------------------------*/
void CModeTitle::Draw( void )
{
}
