/*==============================================================================

    scene2D�̏��� [scene2D.cpp]
                                                       �쐬�� : �����@�S��
                                                       �쐬�� : 2016/4/17
--------------------------------------------------------------------------------
    ��Update : 
==============================================================================*/

/*------------------------------------------------------------------------------
  �@�w�b�_�t�@�C��
------------------------------------------------------------------------------*/
#include "manager.h"
#include "scene.h"
#include "scene2D.h"
#include "renderer.h"
#include "main.h"
#include "textureManager.h"
#include <math.h>

/*------------------------------------------------------------------------------
  �@�}�N��
------------------------------------------------------------------------------*/
#define POLYGON_WIDTH (50)
#define POLYGON_HEIGHT (50)

//=============================================================================
// �R���X�g���N�^
//=============================================================================

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene2D::~CScene2D()
{
}

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================

//=============================================================================
// ����������
//=============================================================================
void CScene2D::Init( void )
{
	m_pos			  = D3DXVECTOR3( m_pos.x, m_pos.y, m_pos.z );
	m_size			  = D3DXVECTOR3( m_size.x, m_size.y, m_size.z );
	m_leftup          = D3DXVECTOR2( m_pos.x - m_size.x * 0.5f, m_pos.y - m_size.y * 0.5f );
	m_rightup         = D3DXVECTOR2( m_pos.x + m_size.x * 0.5f, m_pos.y - m_size.y * 0.5f );
	m_leftdown        = D3DXVECTOR2( m_pos.x - m_size.x * 0.5f, m_pos.y + m_size.y * 0.5f );
	m_rightdown       = D3DXVECTOR2( m_pos.x + m_size.x * 0.5f, m_pos.y + m_size.y * 0.5f );
	m_tex             = D3DXVECTOR2( 0.0f, 0.0f );
	m_texsize         = D3DXVECTOR2( 1.0f, 1.0f );
	m_color			  = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_color.a);

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// ���_�o�b�t�@�̍쐬
	if( FAILED( pDevice->CreateVertexBuffer( sizeof( VERTEX_2D ) * 4,  // �쐬���������_�o�b�t�@�̍��v�f�[�^�T�C�Y
											 D3DUSAGE_WRITEONLY,				// ���_�o�b�t�@�̎g�p���@�i�������݂̂݁j
											 FVF_VERTEX_2D,						// �H
											 D3DPOOL_MANAGED,					// ���_�o�b�t�@�̒u����ƂȂ郁�������w��i�f�o�C�X�Ɉϑ��j
											 &m_pVtxBuff,				// ���_�o�b�t�@�Ǘ��C���^�[�t�F�[�X���i�[
											 NULL ) ) )							// �g��Ȃ�
											 {
												 return;
											 }

	//���_�C���f�b�N�X�쐬
	pDevice->CreateIndexBuffer(
							   sizeof( DWORD ) * 6,
							   0,
							   D3DFMT_INDEX32,
							   D3DPOOL_MANAGED,
							   &m_pIdxBuff,
							   NULL );

	//���_�̃������𒼂ŃR�s�[����
	DWORD *vIndex;
	m_pIdxBuff->Lock( 0, 0, ( void** )&vIndex, 0 ); 
	
	// �����ŎO�p�`�����i�g���C�A���O�����X�g�j
	vIndex[ 0 ] = 0;  
	vIndex[ 1 ] = 1;
	vIndex[ 2 ] = 2;
	vIndex[ 3 ] = 2;
	vIndex[ 4 ] = 1;
	vIndex[ 5 ] = 3;

	m_pIdxBuff->Unlock();

	// ���_�̐ݒ�
	SetVertex();
}

//=============================================================================
// �I������
//=============================================================================
void CScene2D::Uninit( void )
{
	// ���_�o�b�t�@�̔j��
	SAFE_RELEASE( m_pVtxBuff );

	// �C���f�b�N�X�o�b�t�@�̔j��
	SAFE_RELEASE( m_pIdxBuff );
}

//=============================================================================
// �X�V����
//=============================================================================
void CScene2D::Update( void )
{
	// ���_�̐ݒ�
	SetVertex();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CScene2D::Draw( void )
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
		
	// �p�C�v���C���i�X�g���[���j��ݒ�
	pDevice->SetStreamSource( 0,						// �p�C�v���C���ԍ�
							  m_pVtxBuff,				// �p�C�v���C���̌��ɂȂ�̈���w��
							  0,						// �I�t�Z�b�g�i�P�ʂ�byte�j���X�g���[���̊J�n�ʒu���w��ł���
							  sizeof( VERTEX_2D ) );	// �����f�[�^�̒P�ʃT�C�Y�i�X�g���C�h�ʁj�C���f�b�N�X�̐ݒ�
	// �C���f�b�N�X�̐ݒ�
	pDevice->SetIndices( m_pIdxBuff );

	// �e�N�X�`���̐ݒ�i�e�N�X�`���̃X�e�[�W�ւ̊����āj
	pDevice->SetTexture( 0,									 // �X�e�[�W�� 
		CTextureManager::BindTexture( m_TexID ) );			 //�e�N�X�`���C���^�[�t�F�[�X

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF( FVF_VERTEX_2D );

	// �v���~�e�B�u�i�|���S���j�̕`��
	pDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, // �v���~�e�B�u�̎��
								   0,				   // �`��J�n�ʒu�̃I�t�Z�b�g�i���_���j
								   0,				   // �ŏ��C���f�b�N�X�ԍ�
								   6,				   // �ő�C���f�b�N�X�ԍ�
								   0,				   // �C���f�b�N�X�z��̓ǂݎ��ʒu
								   2 );				   // �`�悷��v���~�e�B�u�̐�
}

//=============================================================================
// ���_�̐ݒ�
//=============================================================================
void CScene2D::SetVertex( void )
{
	// ���W�X�V
	m_leftup = D3DXVECTOR2(m_pos.x - m_size.x * 0.5f, m_pos.y - m_size.y * 0.5f);
	m_rightup = D3DXVECTOR2(m_pos.x + m_size.x * 0.5f, m_pos.y - m_size.y * 0.5f);
	m_leftdown = D3DXVECTOR2(m_pos.x - m_size.x * 0.5f, m_pos.y + m_size.y * 0.5f);
	m_rightdown = D3DXVECTOR2(m_pos.x + m_size.x * 0.5f, m_pos.y + m_size.y * 0.5f);

	VERTEX_2D* pVtx; // VRAM�̉��z�A�h���X���i�[

	// ���_�o�b�t�@�����b�N���āA���z�A�h���X���擾����
	m_pVtxBuff->Lock( 0,
					  0,			   // ���ׂĂ����b�N
					  ( void** )&pVtx, // ���z�A�h���X�p�|�C���^�̃A�h���X��n��
					  0 );			   // ���b�N�t���O�H
	
	// ���_���W�̐ݒ�( 2D���W�͉E���ɒ��_��p�ӂ��� )
	
	pVtx[ 0 ].pos = D3DXVECTOR3( m_leftup.x,    m_leftup.y,	   0.0f ); // �R���X�g���N�^�ɂ�钸�_�ݒ� ( x, y, z )
	pVtx[ 1 ].pos = D3DXVECTOR3( m_rightup.x,   m_rightup.y,   0.0f ); 
	pVtx[ 2 ].pos = D3DXVECTOR3( m_leftdown.x,  m_leftdown.y,  0.0f );
	pVtx[ 3 ].pos = D3DXVECTOR3( m_rightdown.x, m_rightdown.y, 0.0f ); 

	// rhw�̐ݒ�i�K��1.0f�j����O�����i�o�b�t�@�j�̏��H
	pVtx[ 0 ].rhw = 1.0f;
	pVtx[ 1 ].rhw = 1.0f;
	pVtx[ 2 ].rhw = 1.0f;
	pVtx[ 3 ].rhw = 1.0f;

	//// ���_�J���[�̐ݒ�
	//pVtx[ 0 ].color = D3DXCOLOR( m_color.r, m_color.g, m_color.b, m_color.a );
	//pVtx[ 1 ].color = D3DXCOLOR( m_color.r, m_color.g, m_color.b, m_color.a ); 
	//pVtx[ 2 ].color = D3DXCOLOR( m_color.r, m_color.g, m_color.b, m_color.a );
	//pVtx[ 3 ].color = D3DXCOLOR( m_color.r, m_color.g, m_color.b, m_color.a );

	pVtx[ 0 ].color = m_color;
	pVtx[ 1 ].color = m_color; 
	pVtx[ 2 ].color = m_color;
	pVtx[ 3 ].color = m_color;

	// ���_�f�[�^��UV�f�[�^��ǉ�
	pVtx[ 0 ].tex = D3DXVECTOR2( m_tex.x,			    m_tex.y );
	pVtx[ 1 ].tex = D3DXVECTOR2( m_tex.x + m_texsize.x, m_tex.y );
	pVtx[ 2 ].tex = D3DXVECTOR2( m_tex.x,				m_tex.y + m_texsize.y );
	pVtx[ 3 ].tex = D3DXVECTOR2( m_tex.x + m_texsize.x, m_tex.y + m_texsize.y );
	
	// ���_�o�b�t�@�̃��b�N������
	m_pVtxBuff->Unlock();
}
