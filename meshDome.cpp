/*==============================================================================

    ���b�V���X�t�B�A�̏��� [meshDome.cpp]
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
#include "meshDome.h"
#include "textureManager.h"
#include "input.h"
#include "camera.h"
#include "light.h"

/*------------------------------------------------------------------------------
  �@�}�N����`
------------------------------------------------------------------------------*/
// �Z�[�t�����[�X�}�N��
#define SAFE_RELEASE( x ) { if( x ) { ( x )->Release(); ( x ) = NULL; } }

#define SPHERE_TEXTURENAME "data/TEXTURE/skydome002.jpg"
#define NUM_VERTEX_WALL (28)	// ���_��
#define NUM_INDEX_WALL (36)	// ���_�C���f�b�N�X��

#define DELTA_U (0.001f) // UV��U�̕ω���

/*-----------------------------------------------------------t-------------------
  �@�O���[�o���ϐ�
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
  �@������
------------------------------------------------------------------------------*/
HRESULT CMeshDome::Init(void)
{
	// �e�N�X�`���̓ǂݍ���
	m_texID = CTextureManager::LoadTexture(SPHERE_TEXTURENAME, CTextureManager::TEXTYPE_NONE);

	// �p�����[�^�ݒ�
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_UV = D3DXVECTOR2(0.0f, 0.0f);
	m_numColumn    = 8;
	m_numRow	   = 8;
	m_radius	   = 200.0f;
	m_center       = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	m_numVertex    = ( m_numRow + 1 ) * ( m_numColumn + 1 );
	m_numIndex	   = ( 2 + m_numRow * 2 ) * m_numColumn + ( m_numColumn - 1 ) * 2;
	m_numPolygon   =  m_numIndex - 2;

	// �f�o�C�X�̃|�C���^�擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// *** ���_�o�b�t�@�̍쐬 ***
	if( FAILED( pDevice->CreateVertexBuffer( sizeof( VERTEX_3D ) * m_numVertex * 1,	  // �쐬���������_�o�b�t�@�̍��v�f�[�^�T�C�Y
											 D3DUSAGE_WRITEONLY,						 	  // ���_�o�b�t�@�̎g�p���@�i�������݂̂݁j
											 FVF_VERTEX_2D,								      // �H
											 D3DPOOL_MANAGED,								  // ���_�o�b�t�@�̒u����ƂȂ郁�������w��i�f�o�C�X�Ɉϑ��j
											 &m_pVtxBuff,									  // ���_�o�b�t�@�Ǘ��C���^�[�t�F�[�X�̃|�C���^�i�C���^�[�t�F�[�X�̊i�[�j
											 NULL ) ) )										  // �g��Ȃ�
											 {
												 return E_FAIL;
											 }	

	// *** �C���f�b�N�X�o�b�t�@�̍쐬 *** 
	if( FAILED( pDevice->CreateIndexBuffer( sizeof( WORD ) * m_numIndex,	// �f�[�^�T�C�Y
											D3DUSAGE_WRITEONLY,					// �g�p�p�r�t���O
											D3DFMT_INDEX16,						// �C���f�b�N�X�f�[�^�̃t�H�[�}�b�g �����_���W2byte�ȉ��̏ꍇ16�A�ȏ�̏ꍇ32
											D3DPOOL_MANAGED,					// �������Ǘ��̕��@
											&m_pIdxBuff,					// �C���f�b�N�X�o�b�t�@�C���^�[�t�F�[�X�̃|�C���^
											NULL ) ) )							// �g��Ȃ�
											{
												return E_FAIL;
											}			
		
	// --- ���_�o�b�t�@�̏����� --- //////////////////////////////////////////////										

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
	float fRotV    = 0.0f;							 // ���S�ɑ΂��鐂�����ʏ�̊p�x
	float fRotDifV = D3DX_PI * 0.6f	/ m_numColumn;   // �������ʏ�̊p�x�̕ω���
	float fRotDifH = D3DX_PI * 2.0f / m_numRow;      // �������ʏ�̊p�x�̕ω���

	for( int nCntY = 0; nCntY < m_numColumn + 1; nCntY++ )
	{
		// �������ʏ�̊p�x�̍X�V
		fRotV = fRotDifV * nCntY;

		float fRotH = D3DX_PI * 0.5f; // ���S�ɑ΂��鐅�����ʏ�̊p�x
		
		for( int nCntX = 0; nCntX < m_numRow + 1; nCntX++ )
		{
			// �������ʏ�̊p�x�̍X�V
			fRotH = fRotDifH * nCntX;

			// ���_�J���[�̐ݒ�i 0 �` 255�̐����l )
			pVtx[ 0 ].color = D3DCOLOR_RGBA( 255, 255, 255, 255 );
		
			// ���_�f�[�^��UV�f�[�^��ǉ�
			pVtx[ 0 ].tex = D3DXVECTOR2((float)nCntX, (float)nCntY);
		
			// ���_���W
			pVtx[ 0 ].pos = D3DXVECTOR3(m_center.x - sinf( fRotV ) * cosf( fRotH ) * m_radius,
										m_center.y + cosf( fRotV )				   * m_radius, 
										m_center.z + sinf( fRotV ) * sinf( fRotH ) * m_radius ); 

			// ���_�@���̐ݒ�
			pVtx[ 0 ].normal  = D3DXVECTOR3( 0.0f, 0.0f, -1.0f ); // �R���X�g���N�^�ɂ�钸�_�ݒ� ( x, y, z )
			
			pVtx += 1;	
		}
	}
	
	// ���_�o�b�t�@�̃��b�N������
	( m_pVtxBuff )->Unlock();

	// �C���f�b�N�X�o�b�t�@�̍쐬
	WORD* pIdx;
	
	// �C���f�b�N�X�o�b�t�@�����b�N���āA���z���_�A�h���X���擾����
	if( FAILED ( ( m_pIdxBuff )->Lock( 0,
									         0,				   // ���ׂĂ����b�N
									         ( void** )&pIdx,  // ���z���_�A�h���X�p�|�C���^�̃A�h���X��n��
									         0 ) ) )		   // ���b�N�t���O�H
									         {	
									           return E_FAIL;
									         }		

	// ���_�C���f�b�N�X�̐ݒ�
	for( int nCntY = 0; nCntY < m_numColumn; nCntY++ )
	{
		for( int nCntX = 0; nCntX < m_numRow + 1; nCntX++ )
		{
			// �k�ރ|���S���p���_�ݒ�(1)
			if( nCntY != 0 && nCntX == 0 )
			{
				pIdx[ 0 ] = ( m_numRow + 1 ) * ( nCntY + 1 ); 	
					
				pIdx++;
			}

			// ���_�ݒ�
			pIdx[ 0 ] = ( m_numRow + 1 ) * ( nCntY + 1 ) + nCntX; 
			pIdx[ 1 ] = ( m_numRow + 1 ) * nCntY + nCntX;	

			pIdx += 2;
		}

		// �k�ރ|���S���p���_�ݒ�(2)
		if( nCntY != m_numColumn - 1 )
		{
			// ���_���W
			pIdx[ 0 ] = ( pIdx - 2 )[ 1 ];
			pIdx++;
		}
	}
	
	// �C���f�b�N�X�o�b�t�@�̃��b�N������
	( m_pIdxBuff )->Unlock();

	// 3D�`��̏���
	Set3D();
	
	return S_OK;
}

/*------------------------------------------------------------------------------
  �@�I������
------------------------------------------------------------------------------*/
void CMeshDome::Uninit( void )
{
	// �I������
	if( m_pIdxBuff != NULL )
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

/*------------------------------------------------------------------------------
  �@�X�V
------------------------------------------------------------------------------*/
void CMeshDome::Update(void)
{
	// UV�̍X�V
	m_UV.x += DELTA_U;

	VERTEX_3D* pVtx; // VRAM�̉��z���_�A�h���X���i�[

	// ���_�o�b�t�@�����b�N���āA���z���_�A�h���X���擾����
	if (FAILED((m_pVtxBuff)->Lock(0,
		0,				// ���ׂĂ����b�N
		(void**)&pVtx,  // ���z���_�A�h���X�p�|�C���^�̃A�h���X��n��
		0)))			// ���b�N�t���O�H
	{
		return;
	}

	for (int nCntY = 0; nCntY < m_numColumn; nCntY++)
	{
		for (int nCntX = 0; nCntX < m_numRow + 1; nCntX++)
		{
			// ���_�f�[�^��UV�f�[�^��ǉ�
			pVtx[0].tex = D3DXVECTOR2(m_UV.x + (float)nCntX / (float) m_numRow, (float)nCntY / (float)m_numColumn);

			pVtx += 1;
		}
	}

	// ���_�o�b�t�@�̃��b�N������
	(m_pVtxBuff)->Unlock();
}

/*------------------------------------------------------------------------------
  �@�`�揈��
------------------------------------------------------------------------------*/
void CMeshDome::Draw( void )
{
	// 3D�`��ݒ�
	Set3D();

	// �f�o�C�X�̃|�C���^�擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// ���C�g�̃X�C�b�`
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �p�C�v���C���i�X�g���[���j��ݒ�
	pDevice->SetStreamSource( 0,						// �p�C�v���C���ԍ�
							  m_pVtxBuff,				// �p�C�v���C���̌��ɂȂ�̈���w��
							  0,						// �I�t�Z�b�g�i�P�ʂ�byte�j���X�g���[���̊J�n�ʒu���w��ł���
							  sizeof( VERTEX_3D ) );	// �����f�[�^�̒P�ʃT�C�Y�i�X�g���C�h�ʁj

	// �C���f�b�N�X�o�b�t�@�̐ݒ�
	pDevice->SetIndices( m_pIdxBuff );
	
	// �e�N�X�`���̐ݒ�
	HRESULT hr = pDevice->SetTexture( 0, CTextureManager::BindTexture(m_texID));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF( FVF_VERTEX_3D );

	// �v���~�e�B�u�i�|���S���j�̕`��
	pDevice->DrawIndexedPrimitive( D3DPT_TRIANGLESTRIP,		// �v���~�e�B�u�̎��
								   0,								// �ŏ��̃C���f�b�N�X�܂ł̃I�t�Z�b�g
								   0,								// �ŏ��̒��_�C���f�b�N�X
								   m_numVertex,				// ���_��
								   0,								// �X�^�[�g�C���f�b�N�X�i�ǂݎn�߂̏ꏊ�H)
								   m_numPolygon				// �v���~�e�B�u�̐�
								   );

	// ���C�g�̃X�C�b�`
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

/*------------------------------------------------------------------------------
�@�쐬
 ------------------------------------------------------------------------------*/
CMeshDome* CMeshDome::Create(void)
{
	CMeshDome* pDome = new CMeshDome(CScene::PRIORITY_3D);
	pDome->Init();
	return pDome;
}

/*------------------------------------------------------------------------------
  �@�R�c�`�揀��
------------------------------------------------------------------------------*/
void CMeshDome::Set3D( void )
{
	// �f�o�C�X�̃|�C���^�擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// --- ���[���h���W�ϊ��s��̍쐬 ---
	D3DXMATRIX mtxWorld,
			   mtxRotY,
			   mtxPos;	// ���[���h���W�ϊ��s��

	// �P�ʍs��ŏ���������
	D3DXMatrixIdentity( &mtxWorld );

	// --- ��]�s�� ---

	// ��]�s��̍쐬
	 float fRadian = 0.0f;

	D3DXMatrixRotationYawPitchRoll( &mtxRotY,				  		   // �i�[�p
									fRadian, /*D3DXToRadian( 45 ),*/ // Y��
									0.0f,						   	   // X��
									0.0f							   // Y��
									);

	// �s��̐ώZ
	D3DXMatrixMultiply( &mtxWorld, // �o��
						&mtxWorld, // ����
						&mtxRotY   // �E��
						);

	// --- ���s�ړ��s�� ---

	// ���s�ړ��s��쐬�֐�
	D3DXMatrixTranslation(&mtxPos,	// �i�[�p
		0.0f,	// X�ړ���
		0.0f,	// Y�ړ���
		0.0f	// Z�ړ���
	);

	// �s��̐ώZ
	D3DXMatrixMultiply(&mtxWorld, // �o��
		&mtxWorld, // ����
		&mtxPos    // �E��
	);

	// �f�o�C�X�ɐݒ�
	pDevice->SetTransform( D3DTS_WORLD, // ���[���h���W
								&mtxWorld	 // 
							    );				 
}

































