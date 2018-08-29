/*==============================================================================

    billboard�̏��� [billboard.cpp]
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
#include "textureManager.h"
#include "input.h"
#include "camera.h"
#include "light.h"
#include "billboard.h"
#include "manager.h"

/*------------------------------------------------------------------------------
  �@�}�N����`
------------------------------------------------------------------------------*/
// �Z�[�t�����[�X�}�N��
#define SAFE_RELEASE( x ) { if( x ) { ( x )->Release(); ( x ) = NULL; } }

#define BILLBOARD_TEXTURENAME "data/TEXTURE/weed001.png"
#define NUM_BILLBOARD (1)	// ��

/*------------------------------------------------------------------------------
  �@�ÓI�����o�ϐ�
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
  �@�R���X�g���N�^
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
  �@�f�X�g���N�^
------------------------------------------------------------------------------*/
CBillboard::~CBillboard()
{
}

/*------------------------------------------------------------------------------
  �@������
------------------------------------------------------------------------------*/
HRESULT CBillboard::Init( void )
{
	// ������
	m_tex = D3DXVECTOR2(0.0f, 0.0f);
	m_texSize = D3DXVECTOR2(1.0f, 1.0f);

	// �f�o�C�X�̃|�C���^�擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// *** ���_�o�b�t�@�̍쐬 ***
	if( FAILED( pDevice->CreateVertexBuffer( sizeof( VERTEX_3D ) * NUM_BILLBOARD * 4,			  // �쐬���������_�o�b�t�@�̍��v�f�[�^�T�C�Y
											 D3DUSAGE_WRITEONLY,						 	  // ���_�o�b�t�@�̎g�p���@�i�������݂̂݁j
											 FVF_VERTEX_3D,								      // �H
											 D3DPOOL_MANAGED,								  // ���_�o�b�t�@�̒u����ƂȂ郁�������w��i�f�o�C�X�Ɉϑ��j
											 &m_pVtxBuff,									  // ���_�o�b�t�@�Ǘ��C���^�[�t�F�[�X�̃|�C���^�i�C���^�[�t�F�[�X�̊i�[�j
											 NULL ) ) )										  // �g��Ȃ�
											 {
												 return E_FAIL;
											 }	

	// *** ���_�o�b�t�@�̏����� ***										

	VERTEX_3D* pVtx; // VRAM�̉��z���_�A�h���X���i�[

	// ���_�o�b�t�@�����b�N���āA���z���_�A�h���X���擾����
	if( FAILED ( ( m_pVtxBuff )->Lock( 0,
										     0,				// ���ׂĂ����b�N
										     ( void** )&pVtx,  // ���z���_�A�h���X�p�|�C���^�̃A�h���X��n��
										     0 ) ) )			// ���b�N�t���O�H
										     {	
										   	  return E_FAIL;
										     }		
	// ���_�f�[�^�̐ݒ�
	
	// ���_�J���[�̐ݒ�i 0 �` 255�̐����l )
	pVtx[ 0 ].color = D3DCOLOR_RGBA( 255, 255, 255, m_alpha );
	pVtx[ 1 ].color = D3DCOLOR_RGBA( 255, 255, 255, m_alpha );
	pVtx[ 2 ].color = D3DCOLOR_RGBA( 255, 255, 255, m_alpha );
	pVtx[ 3 ].color = D3DCOLOR_RGBA( 255, 255, 255, m_alpha );
	
	// ���_�f�[�^��UV�f�[�^��ǉ�
	pVtx[0].tex = D3DXVECTOR2(m_tex.x, m_tex.y);
	pVtx[1].tex = D3DXVECTOR2(m_tex.x + m_texSize.x, m_tex.y);
	pVtx[2].tex = D3DXVECTOR2(m_tex.x, m_tex.y + m_texSize.y);
	pVtx[3].tex = D3DXVECTOR2(m_tex.x + m_texSize.x, m_tex.y + m_texSize.y);
	
	// ���_���W
	pVtx[ 0 ].pos  = D3DXVECTOR3( 0.0f - m_size.x * 0.5f, 0.0f + m_size.y, 0.0f );
	pVtx[ 1 ].pos  = D3DXVECTOR3( 0.0f + m_size.x * 0.5f, 0.0f + m_size.y, 0.0f );
	pVtx[ 2 ].pos  = D3DXVECTOR3( 0.0f - m_size.x * 0.5f, 0.0f,			   0.0f );
	pVtx[ 3 ].pos  = D3DXVECTOR3( 0.0f + m_size.x * 0.5f, 0.0f,			   0.0f );

	// ���_�@���̐ݒ�
	pVtx[ 0 ].normal  = D3DXVECTOR3( 0.0f, 1.0f, 0.0f ); // �R���X�g���N�^�ɂ�钸�_�ݒ� ( x, y, z )
	pVtx[ 1 ].normal  = D3DXVECTOR3( 0.0f, 1.0f, 0.0f ); // �R���X�g���N�^�ɂ�钸�_�ݒ� ( x, y, z )
	pVtx[ 2 ].normal  = D3DXVECTOR3( 0.0f, 1.0f, 0.0f ); // �R���X�g���N�^�ɂ�钸�_�ݒ� ( x, y, z )
	pVtx[ 3 ].normal  = D3DXVECTOR3( 0.0f, 1.0f, 0.0f ); // �R���X�g���N�^�ɂ�钸�_�ݒ� ( x, y, z )
	
	// ���_�o�b�t�@�̃��b�N������
	( m_pVtxBuff )->Unlock();
			
	// 3D�`��̏���
	Set3D();
	
	return S_OK;
}

/*------------------------------------------------------------------------------
  �@�I������
------------------------------------------------------------------------------*/
void CBillboard::Uninit( void )
{
	// ���_�o�b�t�@�̔j��
	SAFE_RELEASE( m_pVtxBuff );
}

/*------------------------------------------------------------------------------
  �@�X�V
------------------------------------------------------------------------------*/
void CBillboard::Update( void )
{
	VERTEX_3D* pVtx; // VRAM�̉��z���_�A�h���X���i�[

					 // ���_�o�b�t�@�����b�N���āA���z���_�A�h���X���擾����
	if (FAILED((m_pVtxBuff)->Lock(0,
		0,				// ���ׂĂ����b�N
		(void**)&pVtx,  // ���z���_�A�h���X�p�|�C���^�̃A�h���X��n��
		0)))			// ���b�N�t���O�H
	{
		return;
	}

	// ���_�f�[�^�̐ݒ�

	// ���_���W
	pVtx[0].pos = D3DXVECTOR3(0.0f - m_size.x * 0.5f, 0.0f + m_size.y * 0.5f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f + m_size.x * 0.5f, 0.0f + m_size.y * 0.5f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f - m_size.x * 0.5f, 0.0f - m_size.y * 0.5f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f + m_size.x * 0.5f, 0.0f - m_size.y * 0.5f, 0.0f);

	// ���_�f�[�^��UV�f�[�^��ǉ�
	pVtx[0].tex = D3DXVECTOR2(m_tex.x, m_tex.y);
	pVtx[1].tex = D3DXVECTOR2(m_tex.x + m_texSize.x, m_tex.y);
	pVtx[2].tex = D3DXVECTOR2(m_tex.x, m_tex.y + m_texSize.y);
	pVtx[3].tex = D3DXVECTOR2(m_tex.x + m_texSize.x, m_tex.y + m_texSize.y);

	// ���_�J���[�̐ݒ�i 0 �` 255�̐����l )
	pVtx[0].color = D3DCOLOR_RGBA(255, 255, 255, m_alpha);
	pVtx[1].color = D3DCOLOR_RGBA(255, 255, 255, m_alpha);
	pVtx[2].color = D3DCOLOR_RGBA(255, 255, 255, m_alpha);
	pVtx[3].color = D3DCOLOR_RGBA(255, 255, 255, m_alpha);

	// ���_�o�b�t�@�̃��b�N������
	(m_pVtxBuff)->Unlock();

	// 3D�`��̏���
	Set3D();
}

/*------------------------------------------------------------------------------
  �@�`��
------------------------------------------------------------------------------*/
void CBillboard::Draw( void )
{	
	// �f�o�C�X�̃|�C���^�擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// �R�c����
	Set3D();

	// �p�C�v���C���i�X�g���[���j��ݒ�
	pDevice->SetStreamSource( 0,						// �p�C�v���C���ԍ�
							  m_pVtxBuff,				// �p�C�v���C���̌��ɂȂ�̈���w��
							  0,						// �I�t�Z�b�g�i�P�ʂ�byte�j���X�g���[���̊J�n�ʒu���w��ł���
							  sizeof( VERTEX_3D ) );	// �����f�[�^�̒P�ʃT�C�Y�i�X�g���C�h�ʁj

	// �e�N�X�`���̐ݒ�
	LPDIRECT3DTEXTURE9 temp = CTextureManager::BindTexture(m_TexID);
	pDevice->SetTexture( 0, temp );

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF( FVF_VERTEX_3D );

	for( int nCnt = 0; nCnt < NUM_BILLBOARD; nCnt++ )
	{
		// �v���~�e�B�u�i�|���S���j�̕`��
		pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
								nCnt * 4,				// �I�t�Z�b�g
								NUM_BILLBOARD * 2		// �v���~�e�B�u�̐�
								);
	}
}

/*------------------------------------------------------------------------------
  �@�R�c�`�揀��
------------------------------------------------------------------------------*/
void CBillboard::Set3D( void )
{
	// �f�o�C�X�̃|�C���^�擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
	
	// --- ���[���h���W�ϊ��s��̍쐬 ---
	D3DXMATRIX mtxWorld,	   // ���[���h���W�ϊ��s��
			   mtxRotY,		   // ��]�s��
			   mtxPos,		   // ���s�ړ��s��
			   mtxView,        // �r���[�s��
			   mtxViewInverse; // �r���[�̋t�s��
	
	// �P�ʍs��ŏ���������
	D3DXMatrixIdentity( &mtxWorld );	
	
	// --- �g��s��̔��f ---

	// --- ��]�s��̔��f ---
	
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

	// --- �r���{�[�h�p���[���h�s��̍쐬 ---

	// �r���[�s��̎擾
	pDevice->GetTransform( D3DTS_VIEW,  // �s��̎��
						   &mtxView		// �o��
						   );

	// �t�s��쐬
	D3DXMatrixInverse( &mtxViewInverse, // �o��
					   NULL,
					   &mtxView         // ����
					   );

	// �t�s�񂩂畽�s�ړ��������J�b�g
	mtxViewInverse._41 = 0.0f;
	mtxViewInverse._42 = 0.0f;	
	mtxViewInverse._43 = 0.0f;

	// �s��̐ώZ
	D3DXMatrixMultiply( &mtxWorld,		 // �o��
						&mtxViewInverse, // ����
						&mtxWorld        // �E��
						);

	// �f�o�C�X�ɐݒ�
	pDevice->SetTransform( D3DTS_WORLD,		 // ���[���h���W
						   &mtxWorld	 // 
						   );				 
}