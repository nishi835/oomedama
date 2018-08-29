/*==============================================================================

    ポリゴン処理のヘッダ [polygon.h]
                                                       作成者 : 中西　祐介
                                                       作成日 : 2016/5/31
--------------------------------------------------------------------------------
    ■Update : 
==============================================================================*/
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

/*------------------------------------------------------------------------------
    ヘッダファイル
------------------------------------------------------------------------------*/
#include "main.h"
#include "scene.h"

/*------------------------------------------------------------------------------
  　クラス
------------------------------------------------------------------------------*/
class CScene2D : public CScene
{
public:
	CScene2D( int Priority ) : CScene( Priority )
	{	
		m_pVtxBuff = NULL;
	};

	~CScene2D();

	void Init(void);
	virtual void Uninit( void )override;
	virtual void Update( void )override;
	virtual void Draw( void )override;

	// セッター
	void SetTexID(int TexID) { m_TexID = TexID; }
	void SetAlpha(const float& alpha) { m_color.a = alpha; }

	void AddAlpha(const float& value) { m_color.a += value; }

	// ゲッター
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	float GetAlpha(void) { return m_color.a; }

	// その他
	void SetVertex( void );
	
protected:
	D3DXVECTOR2  m_leftup;			// 左上の頂点XY
	D3DXVECTOR2  m_rightup;			// 右上の頂点XY
	D3DXVECTOR2  m_leftdown;		// 左下の頂点XY
	D3DXVECTOR2  m_rightdown;		// 右下の頂点XY	
	D3DXVECTOR2  m_tex;				// ポリゴンのUV値
	D3DXVECTOR2  m_texsize;			// ポリゴンのUV値の大きさ
	D3DXCOLOR    m_color;

	float		 m_length;			// ポリゴンの対角線の長さ
	float		 m_angle;			// ポリゴンの対角線の角度
	float		 m_rot;

	bool         m_use;				// 使用フラグ
	int			 m_TexID;           // テクスチャのID

private:	
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;
};

#endif