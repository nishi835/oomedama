/*==============================================================================

    managerの処理 [manager.cpp]
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
#include "renderer.h"
#include "modeTitle.h"
#include "modeGame.h"
#include "textureManager.h"
#include "input.h"
#include "sound.h"
#include "debug.h"
#include "scene.h"
#include "scene2D.h"
#include "fade.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
// モード
CMode* CManager::m_Mode = NULL;
CMode* CManager::m_modeNext = NULL;
CFade* CManager::m_Fade = NULL;
// インフラ系
CTextureManager* CManager::m_TextureManager = NULL;
CInputKeyboard* CManager::m_InputKeyboard = NULL;
CInputMouse* CManager::m_InputMouse = NULL;

//=============================================================================
// 初期化処理
//=============================================================================
void CManager::Init( HINSTANCE hInstance, HWND hWnd, BOOL bWindow )
{
	CRenderer::Init( hInstance, hWnd, TRUE );

	// インフラ系
	m_TextureManager = new CTextureManager();
	m_TextureManager->Init();
	m_InputKeyboard = new CInputKeyboard();
	m_InputKeyboard->Init( hInstance, hWnd );
	m_InputMouse = new CInputMouse();
	m_InputMouse->Init( hInstance, hWnd );
	InitSound(hWnd);

	// モード初期化
	m_Mode = new CModeTitle();
	m_Mode->Init();

#ifdef _DEBUG

	CDebug::Init();

#endif

}

//=============================================================================
// 終了処理
//=============================================================================
void CManager::Uninit( void )
{
	if( m_TextureManager != NULL )
	{
		m_TextureManager->Uninit();
		delete m_TextureManager;
		m_TextureManager = NULL;
	}

	if( m_InputKeyboard != NULL )
	{
		m_InputKeyboard->Uninit();
		delete m_InputKeyboard;
		m_InputKeyboard = NULL;
	}
	
	if( m_InputMouse != NULL )
	{
		m_InputMouse->Uninit();
		delete m_InputMouse;
		m_InputMouse = NULL;
	}

	CRenderer::Uninit();
	UninitSound();

#ifdef _DEBUG

	CDebug::Uninit();

#endif

}

//=============================================================================
// 更新処理
//=============================================================================
void CManager::Update(void)
{

#ifdef _DEBUG

	CDebug::ClearText();

#endif

	// インフラ系の更新
	if(m_InputKeyboard) m_InputKeyboard->Update();

	// シーンの更新
	CScene::UpdateAll();

	// ゲームの更新
	if(m_Mode) m_Mode->Update();

	// フェードの更新
	if (m_Fade)
	{
		m_Fade->Update();

		if (m_Fade->GetFadeMode() == CFade::FADE_OUTEND)
		{
			SetMode(m_modeNext);
			m_Fade->SetFadeMode(CFade::FADE_IN);
		}

		if (m_Fade->GetFadeMode() == CFade::FADE_END)
		{
			m_Fade->Uninit();
			delete m_Fade;
			m_Fade = NULL;
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CManager::Draw( void )
{
	// 描画開始
	CRenderer::DrawBegin();
	
	// シーンの描画	
	CScene::DrawAll();

	// フェードの描画
	if (m_Fade) m_Fade->Draw();

#ifdef _DEBUG

	CDebug::Draw();

#endif

	// 描画終了
	CRenderer::DrawEnd();

	// 削除チェック
	CScene::CheckRelease();
}

//=============================================================================
// モード設定
//=============================================================================
void CManager::SetMode(CMode* modeNext)
{
	if (m_Mode != NULL)
	{
		m_Mode->Uninit();
		delete m_Mode;
	}

	m_Mode = modeNext;

	if (m_Mode != NULL)
	{
		m_Mode->Init();
	}
}

//=============================================================================
// フェード
//=============================================================================
void CManager::Fade(CMode* modeNext)
{
	m_Fade = CFade::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), FADE_TEXTURENAME);

	m_modeNext = modeNext;
}