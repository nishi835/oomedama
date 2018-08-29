/*==============================================================================

homingBullet�̏��� [homingBullet.cpp]
�쐬�� : �����@�S��
�쐬�� :
--------------------------------------------------------------------------------
��Update :
==============================================================================*/

/*------------------------------------------------------------------------------
�@�w�b�_�t�@�C��
 ------------------------------------------------------------------------------*/
#include "main.h"
#include "renderer.h"
#include "sceneModel.h"
#include "homingBullet.h"

/*------------------------------------------------------------------------------
 �@�}�N����`
------------------------------------------------------------------------------*/
#define WHITE_TEXTURE_NAME  "data/TEXTURE/white.jpg"

/*------------------------------------------------------------------------------
  �@�f�X�g���N�^
------------------------------------------------------------------------------*/
CHomingBullet::~CHomingBullet()
{
}

/*------------------------------------------------------------------------------
�@������
------------------------------------------------------------------------------*/
void CHomingBullet::Init(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// ���f���̃��[�h
	HRESULT hr;

	hr = (D3DXLoadMeshFromX(m_FilePass,		// ���f���̃t�@�C����
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

	// �I�u�W�F�N�g�^�C�v�̐ݒ�
	SetObjType(OBJTYPE_NONE);
}

/*------------------------------------------------------------------------------
�@�I������
------------------------------------------------------------------------------*/
void CHomingBullet::Uninit(void)
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

	CScene::SetDelete();
}

/*------------------------------------------------------------------------------
�@�X�V
------------------------------------------------------------------------------*/
void CHomingBullet::Update(void)
{
	if (!m_use) return;

	// �ړ�
	m_pos += m_velocity;

	// �i�s�����x�N�g���̐ݒ� /////////////////////////////////////////

	// �O�ςŁA��]�������߂�
	D3DXVECTOR3 vecOrg = m_velocity;
	D3DXVec3Normalize(&vecOrg, &vecOrg);

	D3DXVECTOR3 vecTarget = m_targetPos - m_pos;
	D3DXVec3Normalize(&vecTarget, &vecTarget);

	D3DXVECTOR3 vecAxis;
	D3DXVec3Cross(&vecAxis, &vecOrg, &vecTarget);

	// ���ς�90�x�ȏ�A������؂蕪��
	float temp = D3DXVec3Dot(&vecOrg, &vecTarget);

	float rot;
	if (temp > 0)
	{
		rot = asin(D3DXVec3Length(&vecAxis));
	}
	// 90�x�ȏ�Ȃ�A�p�x�𒲐�
	else
	{
		rot = D3DX_PI - asin(D3DXVec3Length(&vecAxis));
	}

	// �i�K�I�Ɋp�x��ς���
	rot *= (0.1f);

	// ��]���Ɗp�x����N�H�[�^�j�I�������߂�
	D3DXQUATERNION quaternion;
	D3DXQuaternionRotationAxis(&quaternion, &vecAxis, rot);

	// �N�H�[�^�j�I�������]�s������߂�
	D3DXMatrixRotationQuaternion(&m_mtxRot, &quaternion);

	// �x�N�g�����s��ŉ�]
	D3DXVec3TransformCoord(&vecOrg, &vecOrg, &m_mtxRot);

	m_velocity = vecOrg * HOMINGBULLET_SPEED;
	m_deltaRot += 0.006f;

	// ���f���̌����̉�]���A�p�x�̎Z�o /////////////////////////////////////

	// ���̎Z�o
	D3DXVECTOR3 vecTemp = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	D3DXVec3Cross(&m_axis, &vecTemp, &vecOrg);

	// �p�x�̎Z�o

	// ���ς�90�x�ȏ�A������؂蕪��
	temp = D3DXVec3Dot(&vecOrg, &vecTarget);

	if (temp > 0)
	{
		m_rocalRot = asinf(D3DXVec3Length(&m_axis));
	}
	// 90�x�ȏ�Ȃ�A�p�x�𒲐�
	else
	{
		m_rocalRot = D3DX_PI - asinf(D3DXVec3Length(&m_axis));
	}
}

/*------------------------------------------------------------------------------
�@�`�揈��
------------------------------------------------------------------------------*/
void CHomingBullet::Draw(void)
{
	if (!m_use) return;

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

	// ��]�s��쐬�֐�
	D3DXMatrixRotationAxis(&mtxRot,		   // �i�[�p
		&m_axis,
		m_rocalRot
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
CHomingBullet* CHomingBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 velocity, float rotThe, float rotFai, bool use, char* filePass)
{
	CHomingBullet* pHomingBullet = new CHomingBullet(CScene::PRIORITY_3D);

	// ������
	pHomingBullet->SetPos(pos);
	pHomingBullet->SetVelocity(velocity);
	pHomingBullet->SetDeltaRot(0.0f);
	pHomingBullet->SetRocalRot(0.0f);
	pHomingBullet->SetUse(use);

	// �e�N�X�`��ID�̐ݒ�
	pHomingBullet->SetFilePass(filePass);
	pHomingBullet->Init();

	return pHomingBullet;
}

