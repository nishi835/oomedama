/*==============================================================================

    meshDome�̃w�b�_�[ [meshDome.h]
                                                       �쐬�� : �����@�S��
                                                       �쐬�� :
--------------------------------------------------------------------------------
    ��Update : 
==============================================================================*/
#ifndef _MESHDOME_H_
#define _MESHDOME_H_

/*------------------------------------------------------------------------------
  �@�w�b�_�t�@�C��
------------------------------------------------------------------------------*/
#include "scene.h"

/*------------------------------------------------------------------------------
  �@�}�N����`
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
  �@�\���̂̐錾
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
	D3DXVECTOR3 m_posVtx;		// ���_���W
	D3DXVECTOR3 m_center;		// ���S���W
	D3DXVECTOR2 m_UV;			// UV(�n�_)
	float		m_radius;		// ���a
	int			m_numRow;		// ��������
	int			m_numColumn;		// �c������
	int			m_numVertex;
	int			m_numIndex;
	int			m_numPolygon;
	int			m_texID;

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	LPDIRECT3DINDEXBUFFER9  m_pIdxBuff;
};

#endif

