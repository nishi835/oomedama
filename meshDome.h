/*==============================================================================

    meshDomeのヘッダー [meshDome.h]
                                                       作成者 : 中西　祐介
                                                       作成日 :
--------------------------------------------------------------------------------
    ■Update : 
==============================================================================*/
#ifndef _MESHDOME_H_
#define _MESHDOME_H_

/*------------------------------------------------------------------------------
  　ヘッダファイル
------------------------------------------------------------------------------*/
#include "scene.h"

/*------------------------------------------------------------------------------
  　マクロ定義
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
  　構造体の宣言
------------------------------------------------------------------------------*/
class CMeshDome : public CScene
{
public:
	CMeshDome(int Priority) : CScene(Priority) {}
	~CMeshDome() {}

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CMeshDome* Create(void);
	void Set3D(void);

private:
	D3DXVECTOR3 m_posVtx;		// 頂点座標
	D3DXVECTOR3 m_center;		// 中心座標
	D3DXVECTOR2 m_UV;			// UV(始点)
	float		m_radius;		// 半径
	int			m_numRow;		// 横分割数
	int			m_numColumn;		// 縦分割数
	int			m_numVertex;
	int			m_numIndex;
	int			m_numPolygon;
	int			m_texID;

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	LPDIRECT3DINDEXBUFFER9  m_pIdxBuff;
};

#endif

