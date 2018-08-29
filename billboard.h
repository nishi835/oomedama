/*==============================================================================

    billboardのヘッダー [billboard.h]
                                                       作成者 : 中西　祐介
                                                       作成日 : 
--------------------------------------------------------------------------------
    ■Update : 
==============================================================================*/
#ifndef _BILLBORAD_H_
#define _BILLBORAD_H_

/*------------------------------------------------------------------------------
  　ヘッダファイル
------------------------------------------------------------------------------*/
#include "scene.h"

/*------------------------------------------------------------------------------
  　マクロ定義
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
  　クラス宣言
------------------------------------------------------------------------------*/
class CBillboard : public CScene
{	
public:
	CBillboard( int Priority ) : CScene( Priority ){};
	~CBillboard();

	HRESULT Init( void );
	void Uninit( void );
	void Update( void );
	void Draw( void );

	// セッター
	void SetTex(D3DXVECTOR2 tex) { m_tex = tex; }
	void SetTexSize(D3DXVECTOR2 texSize) { m_texSize = texSize; }
	void SetAlpha(int alpha) { m_alpha = alpha; }
	void SetTexID(int TexID) { m_TexID = TexID; }

	void AddAlpha(int value) { m_alpha += value; }

	// ゲッター
	int GetAlpha(void) { return m_alpha; }

	// その他のメソッド
	void Set3D( void );

protected:
	D3DXVECTOR2 m_tex;
	D3DXVECTOR2 m_texSize;
	float m_rot;
	int m_alpha;
	int m_TexID;                    // テクスチャのID
	
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; // 頂点バッファインターフェースの格納
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff; // インデックスバッファインターフェースの格納
};

#endif

