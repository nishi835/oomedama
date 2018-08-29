/*==============================================================================

    scoreのヘッダー [score.h]
                                                       作成者 : 中西　祐介
                                                       作成日 : 
--------------------------------------------------------------------------------
    ■Update : 
==============================================================================*/
#ifndef _SCORE_H_
#define _SCORE_H_

/*------------------------------------------------------------------------------
  　ヘッダファイル
------------------------------------------------------------------------------*/
#include "main.h"
#include "scene.h"

/*------------------------------------------------------------------------------
　マクロ
------------------------------------------------------------------------------*/
#define SCORE_DIGIT (3)
#define SCORE_TEX_NAME "data/TEXTURE/number02.png"

/*------------------------------------------------------------------------------
　クラス
------------------------------------------------------------------------------*/
class CScore : public CScene
{
public:
	CScore(int Priority) : CScene(Priority) {};
	~CScore() {};

	HRESULT Init( int spritenum );
	void Uninit( void );
	void Update( void )override;
	void Draw( void )override;
	void SetVertex( void );
	
	static CScore* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int spritenum, char* filePass);

	// セッター
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetSize(D3DXVECTOR3 size) { m_size = size; }
	void SetScore(int score) { m_score = score; }
	void SetTexID(int TexID) { m_TexID = TexID; }

	void AddScore(int value) { m_score += value; }

	// ゲッター
	D3DXVECTOR3 GetPos(void) const { return m_pos; }					
	D3DXVECTOR3 GetSize( void ) const {	return m_size; }
	int GetScore(void) { return m_score; }
	
private:
	D3DXVECTOR3	 m_pos;				// ポリゴンの位置
	D3DXVECTOR3	 m_size;			// ポリゴンのサイズ
	D3DXVECTOR2* m_leftup;			// 左上の頂点XY
	D3DXVECTOR2* m_rightup;			// 右上の頂点XY
	D3DXVECTOR2* m_leftdown;		// 左下の頂点XY
	D3DXVECTOR2* m_rightdown;		// 右下の頂点XY	
	D3DXVECTOR2* m_tex;				// ポリゴンのUV値
	D3DXVECTOR2* m_texsize;			// ポリゴンのUV値の大きさ
	D3DXCOLOR    m_color;
	float		 m_length;			// ポリゴンの対角線の長さ
	float		 m_angle;			// ポリゴンの対角線の角度
	float		 m_score;
	int			 m_spriteNum;       // ポリゴン数
	int			 m_TexID;

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;
};

#endif