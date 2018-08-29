/*==============================================================================

    ポリゴン処理のヘッダ [polygon.h]
                                                       作成者 : 中西　祐介
                                                       作成日 : 2016/5/31
--------------------------------------------------------------------------------
    ■Update : 
==============================================================================*/
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

/*------------------------------------------------------------------------------
    ヘッダファイル
------------------------------------------------------------------------------*/
#include "main.h"
#include "scene.h"

/*------------------------------------------------------------------------------
  　クラス
------------------------------------------------------------------------------*/
class CScene3D : public CScene
{
public:
	CScene3D();
	~CScene3D();

	void Init( void );
	void Uninit( void );
	void Update( void );
	void Draw( void );

	void Set3D( void );
	static CScene3D* Create( void );

private:	
	LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;
};

#endif