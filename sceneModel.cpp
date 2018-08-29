/*==============================================================================

���f���̏��� [model.cpp]
�쐬�� : �����@�S��
�쐬�� : 2016/4/17
--------------------------------------------------------------------------------
��Update :
==============================================================================*/

/*------------------------------------------------------------------------------
�@�w�b�_�t�@�C��
 ------------------------------------------------------------------------------*/
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "sceneModel.h"
#include "player.h"

/*------------------------------------------------------------------------------
 �@�}�N����`
------------------------------------------------------------------------------*/
#define WHITE_TEXTURE_NAME  "data/TEXTURE/white.jpg"

/*------------------------------------------------------------------------------
  �@�O���[�o���ϐ�
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
�@�ÓI�����o�ϐ�
------------------------------------------------------------------------------*/
char CSceneModel::m_filePass[256] = {};

/*------------------------------------------------------------------------------
�@���f���̏�����
------------------------------------------------------------------------------*/
void CSceneModel::Init(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// ���f���̃��[�h
	HRESULT hr;
	
	hr = (D3DXLoadMeshFromX(m_filePass,		// ���f���̃t�@�C����
		D3DXMESH_MANAGED,		// CreateVertexBuffer���g���錾
		pDevice,				// �f�o�C�X
		NULL,					// �אڏ��
		&m_pBuffMatModel,		// ���f���̃}�e���A�����̃|�C���^���i�[
		NULL,
		&m_nNumMatModel,        // �}�e���A���̐�
		&m_pMeshModel			// ���b�V�����C���^�[�t�F�[�X�̃|�C���^���i�[
	));

	// �G���[�`�F�b�N
	if (FAILED(hr))
	{
		MessageBox(NULL, "���f���ǂݍ��ݎ��s", "�G���[", MB_OK); // �G���[�`�F�b�N
	}

	// �}�e���A���̎擾
	D3DXMATERIAL* pMat; // �}�e���A�����̃A�h���X�i�[�p
	pMat = (D3DXMATERIAL*)m_pBuffMatModel->GetBufferPointer();

	// �e�N�X�`�����C���^�[�t�F�[�X�Ɋi�[
	for (int nCnt = 0; nCnt < (int)m_nNumMatModel; nCnt++)
	{
		// �e�N�X�`�����Ȃ���΁A�����e�N�X�`����\��
		if (pMat[nCnt].pTextureFilename == NULL)
		{
			if (FAILED(D3DXCreateTextureFromFile(pDevice,				     // �f�o�C�X�̃|�C���^��n��
				WHITE_TEXTURE_NAME,		     // �e�N�X�`���̃t�@�C����
				&m_pTextureModel)))	     // �e�N�X�`���C���^�[�t�F�[�X�̊i�[
			{
				MessageBox(NULL, "���e�N�X�`���ǂݍ��ݎ��s", "�G���[", MB_OK); // �G���[�`�F�b�N
			}
		}
		else
		{
			// �e�N�X�`���t�@�C���̃p�X���C��
			char* aStr = "data\\TEXTURE";
			char* aTemp = strstr(pMat[nCnt].pTextureFilename, aStr);

			// �e�N�X�`���̓ǂݍ���
			if (FAILED(D3DXCreateTextureFromFile(pDevice,				    // �f�o�C�X�̃|�C���^��n��
				aTemp,					    // �e�N�X�`���̃t�@�C����
				&m_pTextureModel)))	    // �e�N�X�`���C���^�[�t�F�[�X�̊i�[
			{
				MessageBox(NULL, "�e�N�X�`���ǂݍ��ݎ��s", "�G���[", MB_OK);  // �G���[�`�F�b�N
			}
		}
	}
}

/*------------------------------------------------------------------------------
�@���f���̏I������
------------------------------------------------------------------------------*/
void CSceneModel::Uninit(void)
{
	// �e�N�X�`���C���^�[�t�F�[�X�̊J��	
	if (m_pTextureModel != NULL)
	{
		m_pTextureModel->Release();
		m_pTextureModel = NULL;
	}

	// �}�e���A�����C���^�[�t�F�[�X�̊J��
	if (m_pBuffMatModel != NULL)
	{
		m_pBuffMatModel->Release();
		m_pBuffMatModel = NULL;
	}

	// ���b�V�����C���^�[�t�F�[�X�̊J��
	if (m_pMeshModel != NULL)
	{
		m_pMeshModel->Release();
		m_pMeshModel = NULL;
	}
}

/*------------------------------------------------------------------------------
�@���f���̍X�V
------------------------------------------------------------------------------*/
void CSceneModel::Update(void)
{
}

/*----------------------------------------------------------------------------
�@���f���̕`��
------------------------------------------------------------------------------*/
void CSceneModel::Draw(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// ���[���h���W�ϊ��s��̍쐬 //////////////////////////////////////////////
	D3DXMATRIX mtxWorld,  // ���[���h���W�ϊ��s��i�[
		mtxRot,	  // ��]�s��i�[
		mtxPos;	  // ���s�ړ��s��i�[

	// �P�ʍs��ŏ���������
	D3DXMatrixIdentity(&mtxWorld);

	// --- �g��s��̔��f ---

	// --- ��]�s��̔��f ---

	// ��]�s��쐬�֐��i Y, X, Z�̏��ŉ�]���� )
	D3DXMatrixRotationYawPitchRoll(&mtxRot,		   // �i�[�p
		m_rotThe,      // Y��
		-m_rotFai,	   // X��
		0.0f		   // Z��
	);

	// �s��̐ώZ
	D3DXMatrixMultiply(&mtxWorld, // �o��
		&mtxWorld, // ����
		&mtxRot   // �E��
	);

	// --- ���s�ړ��s��̔��f ---

	// ���s�ړ��s��쐬�֐�
	D3DXMatrixTranslation(&mtxPos,			// �i�[�p
		m_pos.x,	// X�ړ���
		m_pos.y,	// Y�ړ���
		m_pos.z		// Z�ړ���
	);

	// �s��̐ώZ
	D3DXMatrixMultiply(&mtxWorld, // �o��
		&mtxWorld, // ����
		&mtxPos    // �E��
	);

	// �f�o�C�X�ɐݒ�
	pDevice->SetTransform(D3DTS_WORLD, // ���[���h���W
		&mtxWorld	// 
	);

	// ���݂̃}�e���A�����̊i�[
	D3DMATERIAL9 matDef;
	pDevice->GetMaterial(&matDef);

	// �}�e���A���̎擾
	D3DXMATERIAL* pMat; // �}�e���A�����̃A�h���X�i�[�p
	pMat = (D3DXMATERIAL*)m_pBuffMatModel->GetBufferPointer();

	// �}�e���A���̐ݒ�/�e�N�X�`���̐ݒ�/���b�V���̕`��
	for (int nCnt = 0; nCnt < (int)m_nNumMatModel; nCnt++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCnt].MatD3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_pTextureModel);

		// ���b�V���̕`��
		m_pMeshModel->DrawSubset(nCnt);
	}

	// �}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

/*------------------------------------------------------------------------------
�@�쐬
 ------------------------------------------------------------------------------*/
CSceneModel* CSceneModel::Create(D3DXVECTOR3 pos, float rotThe, float rotFai, char* filePass)
{
	CSceneModel* pSceneModel = new CSceneModel(2);

	pos.y = CModeGame::GetMeshField()->GetHeight(pos);
	pSceneModel->SetPos(D3DXVECTOR3(pos.x, pos.y, pos.z));
	pSceneModel->SetFilePass(filePass);
	pSceneModel->SetRotThe(rotThe);
	pSceneModel->SetRotFai(rotFai);
	pSceneModel->Init();
	return pSceneModel;
}
