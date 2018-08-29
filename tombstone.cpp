/*==============================================================================

tombstone�̏��� [tombstone.cpp]
�쐬�� : �����@�S��
�쐬�� :
--------------------------------------------------------------------------------
��Update :
==============================================================================*/

//-------------------------------------------------------------------------------
//  �w�b�_
//-------------------------------------------------------------------------------
#include "main.h"
#include "modeGame.h"
#include "textureManager.h"
#include "renderer.h"
#include "tombstone.h"
#include "camera.h"
#include "light.h"

//-------------------------------------------------------------------------------
//  �}�N��
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
//  �f�X�g���N�^
//-------------------------------------------------------------------------------
CTombstone::~CTombstone()
{
}

//-------------------------------------------------------------------------------
//  ������
//-------------------------------------------------------------------------------
void CTombstone::Init(D3DXVECTOR3 pos, char* filePass)
{
	// �p�����[�^�ݒ�
	m_pos = pos;
	strcpy_s(m_filePass, filePass);

	// ������
	CSceneModel::Init();

	// ���f���̔��a�擾 ///////////////////////////////////////////////////////////

	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	LPD3DXMESH pCloneMesh;
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;
	VERTEX_3D* pVertex;

	// ���b�V���̎擾
	m_pMeshModel->CloneMeshFVF(D3DXMESH_MANAGED, FVF_VERTEX_3D, pDevice, &pCloneMesh);

	// ���_���̃J�E���g
	int count = pCloneMesh->GetNumVertices();

	// ���_�o�b�t�@�擾
	pCloneMesh->GetVertexBuffer(&pVtxBuff);

	// ���_�o�b�t�@�����b�N
	VERTEX_3D* vertex;
	pVtxBuff->Lock(0, 0, (void**)&vertex, 0);

	// ���a�̎擾
	D3DXVECTOR3 temp;
	float len = 0;
	m_radius = 0;
	for (int i = 0; i < count; i++)
	{
		temp = vertex[i].pos;
		len = D3DXVec3Length(&temp);
		m_radius = max(len, m_radius);
	}
	
	// �����ݒ�
	m_pos.y = CModeGame::GetMeshField()->GetHeight(m_pos) - m_radius * 0.07f;

	// �I�u�W�F�N�g�^�C�v�̐ݒ�
	SetObjType(OBJTYPE_NONE);
}

//-------------------------------------------------------------------------------
//  �I������
//-------------------------------------------------------------------------------
void CTombstone::Uninit(void)
{
}

//-------------------------------------------------------------------------------
//  �`��
//-------------------------------------------------------------------------------
void CTombstone::Draw(void)
{
	CSceneModel::Draw();
}

//-------------------------------------------------------------------------------
//  �쐬
//-------------------------------------------------------------------------------
CTombstone* CTombstone::Create(D3DXVECTOR3 pos, float rotThe, float rotFai, char* filePass)
{
	CTombstone* pTombstone = new CTombstone(PRIORITY_3D);
	pTombstone->SetRotThe(rotThe);
	pTombstone->SetRotFai(rotFai);
	pTombstone->Init(pos, filePass);
	return pTombstone;
}

