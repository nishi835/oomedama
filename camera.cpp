/*==============================================================================

    camera�̏��� [camera.cpp]
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
#include "camera.h"
#include "input.h"

#define CAMERA_ROTATION_RADIUS ( 0.01f ) // �J�����̉�]���a
#define CAMERA_MOVE_COEFFICIENT (0.1f)  // �ړ��W��

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCamera::CCamera()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCamera::~CCamera()
{
}

//=============================================================================
// �|���S���̏���������
//=============================================================================
void CCamera::Init( void )
{
	// �f�o�C�X�̃|�C���^�擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// �J�����̏�����
	m_posEye = D3DXVECTOR3( 0.0f, 10.0f, -30.0f );
	m_posAt  = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	m_posEyeTarget = D3DXVECTOR3(0.0f, 10.0f, -30.0f);
	m_posAtTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotXZ  = 0.0f;
	m_rotXY = 0.0f;
	m_vecUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_distance = 10.0f;

	// �^���x�N�g���̏�����
	D3DXVECTOR3 temp = m_posAt - m_posEye;
	D3DXVec3Cross(&m_flatLine, &temp, &m_vecUp);
	D3DXVec3Normalize(&m_flatLine, &m_flatLine);

	// --- �r���[�ϊ��s��̍쐬 ---
	D3DXMATRIX  mtxView;									  // �r���[���W�ϊ��s��
	D3DXVECTOR3 posEye( m_posEye.x, m_posEye.y, m_posEye.z ); // �J�����̍��W
	D3DXVECTOR3 posAt( 0.0f, 0.0f, 0.0f );					  // �J�����̒����_
	D3DXVECTOR3 vecUp( 0.0f, 1.0f, 0.0f );					  // �J�����̏���
	
	// �r���[�s��̍쐬
	D3DXMatrixLookAtLH( &mtxView,					 // �s��̊i�[
						&posEye, &posAt, &vecUp
						);	 // �K�v�ȏ��

	// �f�o�C�X�ɐݒ�
	pDevice->SetTransform( D3DTS_VIEW,
						   &mtxView
						  );

	// --- �v���W�F�N�V�����ϊ��s��̍쐬 ---
	D3DXMATRIX mtxProj; // �v���W�F�N�V�����ϊ��s����i�[
	
	//
	D3DXMatrixPerspectiveFovLH( &mtxProj,								// �s��̊i�[
								D3DX_PI / 3.0f,							// ��p�i����p�j
								( float )SCREEN_WIDTH / SCREEN_HEIGHT,  // �A�X�y�N�g��
								1.0f,									// near�i0.0f < near ��0.0f�̓_���j
								10000.0f									// far
							    );
	
	// �f�o�C�X�ɐݒ�
	pDevice->SetTransform( D3DTS_PROJECTION,
						   &mtxProj
						  );
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CCamera::Uninit( void )
{
}

//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CCamera::Update(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
	CInputKeyboard* pInputKeyboard = CManager::GetInputKeyboard();

	// �p�����[�^�X�V
	
	// --- �J�����̉�] ---

	if (pInputKeyboard->GetKeyPress(DIK_1))
	{
		m_rotXY += CAMERA_ROTATION_RADIUS;
	}

	if (pInputKeyboard->GetKeyPress(DIK_2))
	{
		m_rotXY -= CAMERA_ROTATION_RADIUS;
	}

	if (pInputKeyboard->GetKeyPress(DIK_3))
	{
		m_rotXZ += CAMERA_ROTATION_RADIUS;
	}

	if (pInputKeyboard->GetKeyPress(DIK_4))
	{
		m_rotXZ -= CAMERA_ROTATION_RADIUS;
	}

	if (pInputKeyboard->GetKeyPress(DIK_Z))
	{
	}

	if (pInputKeyboard->GetKeyPress(DIK_O))
	{
	}

	// �J�����̈ړ�
	
	D3DXMATRIX	mtxRot;  // ��]�s��i�[

	// --- �J�����̉�] ---

	// ��]�s��쐬�֐�
	//D3DXMatrixRotationAxis(&mtxRot,		   // �i�[�p

	//	m_rotXY     // Y��
	//);

//	D3DXVec3TransformCoord(&m_posEye, &m_posEye, &mtxRot); // ��]�s�񂩂���W���擾

	// --- �����_�̉�] ---

	// --- �J�����̕��s�ړ� ---

	// --- �r���[�ϊ��s��̍쐬 ---

	D3DXMATRIX mtxView;						 // �r���[���W�ϊ��s��

	// �r���[�s��̍쐬
	D3DXMatrixLookAtLH( &mtxView,					 // �s��̊i�[
						&m_posEye,			 // �J�����̍��W
						&m_posAt,				 // �J�����̒����_
						&m_vecUp						 // �J�����̏���
						);	 

	// �f�o�C�X�ɐݒ�
	pDevice->SetTransform( D3DTS_VIEW,
								&mtxView
							  );

	// --- �v���W�F�N�V�����ϊ��s��̍쐬 ---
	D3DXMATRIX mtxProj; // �v���W�F�N�V�����ϊ��s����i�[
	
	//
	D3DXMatrixPerspectiveFovLH( &mtxProj,								// �s��̊i�[
								D3DX_PI / 3.0f,							// ��p�i����p�j
								( float )SCREEN_WIDTH / SCREEN_HEIGHT,  // �A�X�y�N�g��
								1.0f,									// near�i0.0f < near ��0.0f�̓_���j
								10000.0f									// far
							  );
	
	// �f�o�C�X�ɐݒ�
	pDevice->SetTransform( D3DTS_PROJECTION,
								&mtxProj
							  );	

}

//=============================================================================
// �쐬
//=============================================================================
CCamera* CCamera::Create(void)
{
	CCamera* pCamera = new CCamera();
	pCamera->Init();

	return pCamera;
}