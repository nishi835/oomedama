/*==============================================================================

    field�̃w�b�_�[ [main.h]
                                                       �쐬�� : �����@�S��
                                                       �쐬�� : 
--------------------------------------------------------------------------------
    ��Update : 
==============================================================================*/
#ifndef _FIELD_H_
#define _FIELD_H_

/*------------------------------------------------------------------------------
  �@�w�b�_�t�@�C��
------------------------------------------------------------------------------*/
#include "scene.h"

/*------------------------------------------------------------------------------
  �@�}�N����`
------------------------------------------------------------------------------*/
#define FIELD_NUM_COLUMN (30)
#define FIELD_NUM_ROW (30)
#define FIELD_SELL_WIDTH (10)
#define FIELD_SELL_HEIGHT (10)

/*------------------------------------------------------------------------------
  �@�N���X
------------------------------------------------------------------------------*/
class CMeshField : public CScene
{
public:
	CMeshField( int Priority ) : CScene( Priority ){};
	~CMeshField();
	
	void Init( void );
	void Uninit( void );
	void Update( void );
	void Draw( void );

	void Set3D( void );
	void Load(void);

	float GetHeight( D3DXVECTOR3 Position );

	static CMeshField* Create( void );

private:
	D3DXVECTOR3 m_PosVtx;
	D3DXVECTOR3 m_Center;
	int m_NumColumn;
	int m_NumRow;
	float m_SellWidth;
	float m_SellHeight;
	int m_NumVertex;
	int m_NumPolygon;
	int m_NumIndex;
	
	LPDIRECT3DTEXTURE9 m_pTexture; // �e�N�X�`���C���^�[�t�F�[�X
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffer; 
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuffer;
	float m_FieldHeight[FIELD_NUM_ROW + 1][FIELD_NUM_COLUMN + 1];									
};

#endif