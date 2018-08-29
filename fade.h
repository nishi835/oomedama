/*==============================================================================

    Fade処理のヘッダ [fade.h]
                                                       作成者 : 中西　祐介
                                                       作成日 : 
--------------------------------------------------------------------------------
    ■Update : 
==============================================================================*/
#ifndef _FADE_H_
#define _FADE_H_

/*------------------------------------------------------------------------------
  　マクロ
------------------------------------------------------------------------------*/
#define FADE_TEXTURENAME "data/TEXTURE/fade00.png"		 // テクスチャファイル名

/*------------------------------------------------------------------------------
  　ヘッダファイル
------------------------------------------------------------------------------*/
#include "scene2D.h"
#include "main.h"

/*------------------------------------------------------------------------------
  　列挙体の宣言
------------------------------------------------------------------------------*/
class CFade
{
public:
	typedef enum
	{
		FADE_NONE = 0,
		FADE_IN,
		FADE_OUT,
		FADE_OUTEND,
		FADE_END,
		FADE_MAX
	}FADE;

	CFade() {}
	~CFade() {}

	void Init(void);
	void Uninit( void );
	void Update( void );
	void Draw( void );

	// セッター
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetSize(D3DXVECTOR3 size) { m_size = size; }
	void SetFadeMode(FADE fadeMode) { m_fadeMode = fadeMode; }
	void SetTexID(int TexID) { m_TexID = TexID; }

	// ゲッター
	FADE GetFadeMode(void) { return m_fadeMode; }
	
	// その他
	static CFade* CFade::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, char* filePass);
	void SetVertex(void);

private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;
	D3DXVECTOR2  m_leftup;			// 左上の頂点XY
	D3DXVECTOR2  m_rightup;			// 右上の頂点XY
	D3DXVECTOR2  m_leftdown;		// 左下の頂点XY
	D3DXVECTOR2  m_rightdown;		// 右下の頂点XY	
	D3DXVECTOR2  m_tex;				// ポリゴンのUV値
	D3DXVECTOR2  m_texsize;			// ポリゴンのUV値の大きさ
	D3DXCOLOR    m_color;
	FADE m_fadeMode;
	int m_TexID;

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;
};

#endif