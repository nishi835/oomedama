/*==============================================================================

    scene3D�̏��� [scene2D.cpp]
                                                       �쐬�� : �����@�S��
                                                       �쐬�� : 2016/4/17
--------------------------------------------------------------------------------
    ��Update : 
==============================================================================*/

/*------------------------------------------------------------------------------
  �@�w�b�_�t�@�C��
------------------------------------------------------------------------------*/
#include "main.h"
#include "renderer.h"
#include "scene3D.h"

#define SHADOW_TEXTURENAME "data/TEXTURE/gang02.png"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene3D::CScene3D()
{
	m_pVtxBuff = NULL;
	m_pTexture = NULL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene3D::~CScene3D()
{
}

//=============================================================================
// �|���S���̏���������
//=============================================================================
void CScene3D::Init( void )
{		
	// �f�o�C�X�̃|�C���^�擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// *** ���_�o�b�t�@�̍쐬 ***
	if( FAILED( pDevice->CreateVertexBuffer( sizeof( VERTEX_3D ) * 4,			  // �쐬���������_�o�b�t�@�̍��v�f�[�^�T�C�Y
											 D3DUSAGE_WRITEONLY,						 	  // ���_�o�b�t�@�̎g�p���@�i�������݂̂݁j
											 FVF_VERTEX_3D,								      // �H
											 D3DPOOL_MANAGED,								  // ���_�o�b�t�@�̒u����ƂȂ郁�������w��i�f�o�C�X�Ɉϑ��j
											 &m_pVtxBuff,									  // ���_�o�b�t�@�Ǘ��C���^�[�t�F�[�X�̃|�C���^�i�C���^�[�t�F�[�X�̊i�[�j
											 NULL ) ) )										  // �g��Ȃ�
											 {
												 return;
											 }	

	// *** ���_�o�b�t�@�̏����� ***										

	VERTEX_3D* pVtx; // VRAM�̉��z���_�A�h���X���i�[

	// ���_�o�b�t�@�����b�N���āA���z���_�A�h���X���擾����
	if( FAILED ( (m_pVtxBuff)->Lock( 0,
									0,				// ���ׂĂ����b�N
									( void** )&pVtx,  // ���z���_�A�h���X�p�|�C���^�̃A�h���X��n��
									0 ) ) )			// ���b�N�t���O�H
									{	
									 return;
									}		
	// ���_�f�[�^�̐ݒ�

	// ���_�J���[�̐ݒ�i 0 �` 255�̐����l )
	pVtx[ 0 ].color = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	pVtx[ 1 ].color = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	pVtx[ 2 ].color = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	pVtx[ 3 ].color = D3DCOLOR_RGBA( 255, 255, 255, 255 );
		
	// ���_�f�[�^��UV�f�[�^��ǉ�
	pVtx[ 0 ].tex = D3DXVECTOR2( 0.0f, 0.0f );
	pVtx[ 1 ].tex = D3DXVECTOR2( 1.0f, 0.0f );
	pVtx[ 2 ].tex = D3DXVECTOR2( 0.0f, 1.0f );
	pVtx[ 3 ].tex = D3DXVECTOR2( 1.0f, 1.0f );
		
	// ���_���W
	pVtx[ 0 ].pos = D3DXVECTOR3( 0.0f - m_size.x * 0.5f, 0.0f,  m_size.y * 0.5f );
	pVtx[ 1 ].pos = D3DXVECTOR3( 0.0f + m_size.x * 0.5f, 0.0f,  m_size.y * 0.5f );
	pVtx[ 2 ].pos = D3DXVECTOR3( 0.0f - m_size.x * 0.5f, 0.0f, -m_size.y * 0.5f );
	pVtx[ 3 ].pos = D3DXVECTOR3( 0.0f + m_size.x * 0.5f, 0.0f, -m_size.y * 0.5f );

	// ���_�@���̐ݒ�
	pVtx[ 0 ].normal = D3DXVECTOR3( 0.0f, 0.0f, -1.0f ); // �R���X�g���N�^�ɂ�钸�_�ݒ� ( x, y, z )
	pVtx[ 1 ].normal = D3DXVECTOR3( 0.0f, 0.0f, -1.0f ); // �R���X�g���N�^�ɂ�钸�_�ݒ� ( x, y, z )
	pVtx[ 2 ].normal = D3DXVECTOR3( 0.0f, 0.0f, -1.0f ); // �R���X�g���N�^�ɂ�钸�_�ݒ� ( x, y, z )
	pVtx[ 3 ].normal = D3DXVECTOR3( 0.0f, 0.0f, -1.0f ); // �R���X�g���N�^�ɂ�钸�_�ݒ� ( x, y, z )
		
	// ���_�o�b�t�@�̃��b�N������
	( m_pVtxBuff )->Unlock();
		
	// �e�N�X�`���̓ǂݍ���
	if( FAILED ( D3DXCreateTextureFromFile( pDevice, SHADOW_TEXTURENAME, &m_pTexture ) ) )
	{
		MessageBox( NULL, "�ǂݍ��ݎ��s", "�G���[", MB_OK ); 
	}
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CScene3D::Uninit( void )
{
	// ���_�o�b�t�@�̔j��
	SAFE_RELEASE( m_pVtxBuff );
	
	// �C���f�b�N�X�o�b�t�@�̔j��
	SAFE_RELEASE( m_pIdxBuff );
	
	// �e�N�X�`���̔j��
	if( m_pTexture != NULL )
	{
		SAFE_RELEASE( m_pTexture );
	}
}

//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CScene3D::Update( void )
{
}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CScene3D::Draw( void )
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// �p�C�v���C���i�X�g���[���j��ݒ�
	pDevice->SetStreamSource( 0,						// �p�C�v���C���ԍ�
							  m_pVtxBuff,				// �p�C�v���C���̌��ɂȂ�̈���w��
							  0,						// �I�t�Z�b�g�i�P�ʂ�byte�j���X�g���[���̊J�n�ʒu���w��ł���
							  sizeof( VERTEX_3D ) );	// �����f�[�^�̒P�ʃT�C�Y�i�X�g���C�h�ʁj

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture( 0, m_pTexture );

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF( FVF_VERTEX_3D );

	// 3D����
	Set3D();

	// �v���~�e�B�u�i�|���S���j�̕`��
	pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
							0,						// �I�t�Z�b�g
							2						// �v���~�e�B�u�̐�
							);
	
}

/*------------------------------------------------------------------------------
  �@�R�c�`�揀��
------------------------------------------------------------------------------*/
void CScene3D::Set3D( void )
{
	// �f�o�C�X�̃|�C���^�擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// --- ���[���h���W�ϊ��s��̍쐬 ---
	D3DXMATRIX mtxWorld,
			   mtxPos,
			   mtxRotY;	 // ���[���h���W�ϊ��s��

	// �P�ʍs��ŏ���������
	D3DXMatrixIdentity( &mtxWorld );

	// --- ���s�ړ��s��̔��f ---

	// ���s�ړ��s��쐬�֐�
	D3DXMatrixTranslation( &mtxPos,	// �i�[�p
						   m_pos.x,	// X�ړ���
						   m_pos.y,	// Y�ړ���
						   m_pos.z	// Z�ړ���
  						   );		
	
	// �s��̐ώZ
	D3DXMatrixMultiply( &mtxWorld, // �o��
						&mtxWorld, // ����
						&mtxPos    // �E��
						);

	// �f�o�C�X�ɐݒ�
	pDevice->SetTransform( D3DTS_WORLD, // ���[���h���W
						   &mtxWorld	// 
						   );
}

//=============================================================================
// �I�u�W�F�N�g�̍쐬
//=============================================================================
CScene3D* CScene3D::Create( void )
{
	CScene3D* scene3D;
	scene3D = new CScene3D();
	scene3D->Init();

	return scene3D;
}