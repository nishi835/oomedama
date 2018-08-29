/*==============================================================================

    meshField�̏��� [meshField.cpp]
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
#include "meshField.h"
#include "camera.h"
#include "light.h"

/*------------------------------------------------------------------------------
  �@�}�N����`
------------------------------------------------------------------------------*/
// �Z�[�t�����[�X�}�N��
#define SAFE_RELEASE( x ) { if( x ) { ( x )->Release(); ( x ) = NULL; } }

#define POLYGON_TEXTURENAME "data/TEXTURE/desert.jpg"
#define NUM_VERTEX_FIELD (36)

float g_FieldHeight[ 31 ][ 31 ] =
{
	{ 5.0f, 3.0f, 5.0f, 3.0f, 3.0f, 5.0f, 3.0f, 5.0f, 3.0f, 3.0f, 3.0f, 5.0f, 3.0f, 5.0f, 3.0f, 3.0f, 5.0f, 3.0f, 5.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 5.0f, 3.0f, 5.0f, 3.0f, 3.0f, 3.0f, 5.0f },
	{ 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 5.0f, 4.0f, 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 4.0f },
	{ 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 4.0f, 3.0f, 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 3.0f },
	{ 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 3.0f, 2.0f, 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 2.0f },
	{ 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 3.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 3.0f, 2.0f, 3.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 3.0f, 2.0f },
	{ 5.0f, 3.0f, 5.0f, 3.0f, 3.0f, 5.0f, 3.0f, 5.0f, 3.0f, 3.0f, 3.0f, 5.0f, 3.0f, 5.0f, 3.0f, 3.0f, 5.0f, 3.0f, 5.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 5.0f, 3.0f, 5.0f, 3.0f, 3.0f, 3.0f, 5.0f },
	{ 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 5.0f, 4.0f, 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 4.0f },
	{ 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 4.0f, 3.0f, 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 3.0f },
	{ 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 3.0f, 2.0f, 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 2.0f },
	{ 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 3.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 3.0f, 2.0f, 3.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 3.0f, 2.0f },
	{ 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 5.0f, 4.0f, 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 4.0f },
	{ 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 4.0f, 3.0f, 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 3.0f },
	{ 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 3.0f, 2.0f, 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 2.0f },
	{ 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 3.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 3.0f, 2.0f, 3.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 3.0f, 2.0f },
	{ 5.0f, 3.0f, 5.0f, 3.0f, 3.0f, 5.0f, 3.0f, 5.0f, 3.0f, 3.0f, 3.0f, 5.0f, 3.0f, 5.0f, 3.0f, 3.0f, 5.0f, 3.0f, 5.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 5.0f, 3.0f, 5.0f, 3.0f, 3.0f, 3.0f, 5.0f },
	{ 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 5.0f, 4.0f, 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 4.0f },
	{ 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 4.0f, 3.0f, 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 3.0f },
	{ 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 3.0f, 2.0f, 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 2.0f },
	{ 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 3.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 3.0f, 2.0f, 3.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 3.0f, 2.0f },
	{ 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 5.0f, 4.0f, 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 4.0f },
	{ 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 4.0f, 3.0f, 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 3.0f },
	{ 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 3.0f, 2.0f, 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 2.0f },
	{ 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 3.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 3.0f, 2.0f, 3.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 3.0f, 2.0f },
	{ 5.0f, 3.0f, 5.0f, 3.0f, 3.0f, 5.0f, 3.0f, 5.0f, 3.0f, 3.0f, 3.0f, 5.0f, 3.0f, 5.0f, 3.0f, 3.0f, 5.0f, 3.0f, 5.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 5.0f, 3.0f, 5.0f, 3.0f, 3.0f, 3.0f, 5.0f },
	{ 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 5.0f, 4.0f, 4.0f, 3.0f, 4.0f, 5.0f, 4.0f, 4.0f, 4.0f },
	{ 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 4.0f, 3.0f, 3.0f, 4.0f, 6.0f, 4.0f, 3.0f, 3.0f, 3.0f },
	{ 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 3.0f, 2.0f, 2.0f, 3.0f, 5.0f, 3.0f, 2.0f, 2.0f, 2.0f },
	{ 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 3.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 3.0f, 2.0f, 3.0f, 2.0f, 3.0f, 5.0f, 2.0f, 3.0f, 3.0f, 2.0f }
};

/*------------------------------------------------------------------------------
  �@�f�X�g���N�^
------------------------------------------------------------------------------*/
CMeshField::~CMeshField()
{
}

/*------------------------------------------------------------------------------
  �@������
------------------------------------------------------------------------------*/
void CMeshField::Init( void )
{
	// �t�B�[���h�̃p�����[�^�ݒ�
	m_NumRow = FIELD_NUM_ROW;
	m_NumColumn = FIELD_NUM_COLUMN;
	m_SellHeight = FIELD_SELL_WIDTH;
	m_SellWidth = FIELD_SELL_HEIGHT;
	m_Center.x = 0.0f;
	m_Center.z = 0.0f;
	m_NumVertex = ( m_NumColumn + 1 ) * ( m_NumRow + 1 );
	m_NumIndex = ( m_NumColumn + 1 ) * ( m_NumRow + 1 ) + ( m_NumRow - 1 ) * ( m_NumColumn + 1 ) + ( m_NumRow - 1 ) * 2;
	m_NumPolygon =  m_NumIndex - 2;

	// �t�B�[���h�̍����ǂݍ���
	Load();

	// �f�o�C�X�̃|�C���^�擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// *** ���_�o�b�t�@�̍쐬 ***
	if( FAILED( pDevice->CreateVertexBuffer( sizeof( VERTEX_3D ) * m_NumVertex * 1,	  // �쐬���������_�o�b�t�@�̍��v�f�[�^�T�C�Y
											 D3DUSAGE_WRITEONLY,						 	  // ���_�o�b�t�@�̎g�p���@�i�������݂̂݁j
											 FVF_VERTEX_2D,								      // �H
											 D3DPOOL_MANAGED,								  // ���_�o�b�t�@�̒u����ƂȂ郁�������w��i�f�o�C�X�Ɉϑ��j
											 &m_pVtxBuffer,									  // ���_�o�b�t�@�Ǘ��C���^�[�t�F�[�X�̃|�C���^�i�C���^�[�t�F�[�X�̊i�[�j
											 NULL ) ) )										  // �g��Ȃ�
											 {
												 return;
											 }	

	// *** �C���f�b�N�X�o�b�t�@�̍쐬 *** 
	if( FAILED( pDevice->CreateIndexBuffer( sizeof( WORD ) * m_NumIndex,	// �f�[�^�T�C�Y
											D3DUSAGE_WRITEONLY,					// �g�p�p�r�t���O
											D3DFMT_INDEX16,						// �C���f�b�N�X�f�[�^�̃t�H�[�}�b�g �����_���W2byte�ȉ��̏ꍇ16�A�ȏ�̏ꍇ32
											D3DPOOL_MANAGED,					// �������Ǘ��̕��@
											&m_pIdxBuffer,					// �C���f�b�N�X�o�b�t�@�C���^�[�t�F�[�X�̃|�C���^
											NULL ) ) )							// �g��Ȃ�
											{
												return;
											}			
		
	// *** ���_�o�b�t�@�̏����� ***										

	VERTEX_3D* pVtx;  // VRAM�̉��z���_�A�h���X���i�[

	// ���_�o�b�t�@�����b�N���āA���z���_�A�h���X���擾����
	if( FAILED ( ( m_pVtxBuffer )->Lock( 0,
									   0,				// ���ׂĂ����b�N
								       ( void** )&pVtx,  // ���z���_�A�h���X�p�|�C���^�̃A�h���X��n��
									   0 ) ) )			// ���b�N�t���O�H
								       {	
									 	  return;
									   }		

	// ���_�f�[�^�̐ݒ�
	for( int nCntZ = 0; nCntZ < m_NumRow + 1; nCntZ++ )
	{
		for( int nCntX = 0; nCntX < m_NumColumn + 1; nCntX++ )
		{
			// ���_�J���[�̐ݒ�i 0 �` 255�̐����l )
			pVtx[ 0 ].color = D3DCOLOR_RGBA( 255, 255, 0, 255 );
		
			// ���_�f�[�^��UV�f�[�^��ǉ�
			pVtx[ 0 ].tex = D3DXVECTOR2( ( float )nCntX, ( float )nCntZ );
		
			// ���_���W
			pVtx[ 0 ].pos  = D3DXVECTOR3( m_Center.x - m_SellWidth  * m_NumColumn * 0.5f + m_SellWidth  * nCntX,
										  m_FieldHeight[ nCntZ ][ nCntX ],
										  m_Center.z + m_SellHeight * m_NumRow * 0.5f - m_SellHeight * nCntZ ); 


			pVtx[ 0 ].normal  = D3DXVECTOR3( 0.0f, 1.0f, 0.0f ); // �R���X�g���N�^�ɂ�钸�_�ݒ� ( x, y, z )
			
			pVtx += 1;	
		}
	}

	// ���_�o�b�t�@�̃��b�N������
	( m_pVtxBuffer )->Unlock();	

	// ���_�o�b�t�@�����b�N���āA���z���_�A�h���X���擾����
	if( FAILED ( ( m_pVtxBuffer )->Lock( 0,
									   0,				// ���ׂĂ����b�N
								       ( void** )&pVtx,  // ���z���_�A�h���X�p�|�C���^�̃A�h���X��n��
									   0 ) ) )			// ���b�N�t���O�H
								       {	
									 	  return;
									   }	
		
	// ���_�@���̐ݒ�
	D3DXVECTOR3 d1;
	D3DXVECTOR3 d2;
	int nCnt = 0;
	for( int nCntZ = 0; nCntZ < m_NumRow + 1; nCntZ++ )
	{
		for( int nCntX = 0; nCntX < m_NumColumn + 1; nCntX++ )
		{
			if( nCntX == m_NumColumn && nCntZ == m_NumRow )
			{
				// �p�^�[���ق�
				d2 = pVtx[ nCnt - m_NumColumn - 1 ].pos - pVtx[ nCnt ].pos;
				d1 = pVtx[ nCnt - 1 ].pos - pVtx[ nCnt ].pos;
			}
			else if( nCntX == m_NumColumn )
			{			
				// �p�^�[�����񂩂�
				d1 = pVtx[ nCnt + m_NumColumn + 1 ].pos - pVtx[ nCnt ].pos;
				d2 = pVtx[ nCnt - 1 ].pos - pVtx[ nCnt ].pos;
			}
			else if( nCntZ == m_NumRow )
			{			
				// �p�^�[��������
				d1 = pVtx[ nCnt - m_NumColumn - 1 ].pos - pVtx[ nCnt ].pos;
				d2 = pVtx[ nCnt + 1 ].pos - pVtx[ nCnt ].pos;
			}
			else
			{
				// �p�^�[���܂�
				d1 = pVtx[ nCnt + 1 ].pos - pVtx[ nCnt ].pos;
				d2 = pVtx[ nCnt + m_NumColumn + 1 ].pos - pVtx[ nCnt ].pos;
			}
			
			D3DXVec3Cross( &pVtx[ nCnt ].normal, &d1, &d2 );
			D3DXVec3Normalize( &pVtx[ nCnt ].normal, &pVtx[ nCnt ].normal );

			nCnt++;
		}
	}
	
	// ���_�o�b�t�@�̃��b�N������
	( m_pVtxBuffer )->Unlock();

	// �C���f�b�N�X�o�b�t�@�̍쐬
	WORD* pIdx;
	
	// �C���f�b�N�X�o�b�t�@�����b�N���āA���z���_�A�h���X���擾����
	if( FAILED ( ( m_pIdxBuffer )->Lock( 0,
									        0,				// ���ׂĂ����b�N
									        ( void** )&pIdx,  // ���z���_�A�h���X�p�|�C���^�̃A�h���X��n��
									        0 ) ) )			// ���b�N�t���O�H
									        {	
									       	  return;
									        }		

	// ���_�C���f�b�N�X�̐ݒ�
	for( int nCntZ = 0; nCntZ < m_NumRow; nCntZ++ )
	{
		for( int nCntX = 0; nCntX < m_NumColumn + 1; nCntX++ )
		{
			// �k�ރ|���S���p���_�ݒ�(1)
			if( nCntZ != 0 && nCntX == 0 )
			{
				pIdx[ 0 ] = ( m_NumColumn + 1 ) * ( nCntZ + 1 ); 	
					
				pIdx++;
			}

			// ���_�ݒ�
			pIdx[ 0 ] = ( m_NumColumn + 1 ) * ( nCntZ + 1 ) + nCntX; 
			pIdx[ 1 ] = ( m_NumColumn + 1 ) * nCntZ + nCntX;	

			pIdx += 2;
		}

		// �k�ރ|���S���p���_�ݒ�(2)
		if( nCntZ != m_NumRow - 1 )
		{
			// ���_���W
			pIdx[ 0 ] = ( pIdx - 2 )[ 1 ];
			pIdx++;
		}
	}
	
	// �C���f�b�N�X�o�b�t�@�̃��b�N������
	( m_pIdxBuffer )->Unlock();

	// �e�N�X�`���̓ǂݍ���
	if( FAILED ( D3DXCreateTextureFromFile( pDevice, POLYGON_TEXTURENAME, &m_pTexture ) ) )
	{
		MessageBox( NULL, "�ǂݍ��ݎ��s", "�G���[", MB_OK ); 
	}
	
	// �I�u�W�F�N�g�^�C�v�̐ݒ�
	SetObjType( OBJTYPE_MESHFIELD );
}

/*------------------------------------------------------------------------------
  �@�I������
------------------------------------------------------------------------------*/
void CMeshField::Uninit( void )
{
	// ���_�o�b�t�@�̔j��
	SAFE_RELEASE( m_pVtxBuffer );
	
	// �e�N�X�`���̔j��
	if( m_pTexture != NULL )
	{
		SAFE_RELEASE( m_pTexture );
	}
}

/*------------------------------------------------------------------------------
  �@�X�V
------------------------------------------------------------------------------*/
void CMeshField::Update( void )
{
}

/*------------------------------------------------------------------------------
  �@�|���S���`�揈��
------------------------------------------------------------------------------*/
void CMeshField::Draw( void )
{
	Set3D();

	// �f�o�C�X�̃|�C���^�擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// �p�C�v���C���i�X�g���[���j��ݒ�
	pDevice->SetStreamSource( 0,						// �p�C�v���C���ԍ�
							  m_pVtxBuffer,				// �p�C�v���C���̌��ɂȂ�̈���w��
							  0,						// �I�t�Z�b�g�i�P�ʂ�byte�j���X�g���[���̊J�n�ʒu���w��ł���
							  sizeof( VERTEX_3D ) );	// �����f�[�^�̒P�ʃT�C�Y�i�X�g���C�h�ʁj

	// �C���f�b�N�X�o�b�t�@�̐ݒ�
	pDevice->SetIndices( m_pIdxBuffer );
	
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture( 0, m_pTexture );

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF( FVF_VERTEX_3D );

	// �v���~�e�B�u�i�|���S���j�̕`��
	pDevice->DrawIndexedPrimitive( D3DPT_TRIANGLESTRIP,		// �v���~�e�B�u�̎��
								   0,								// �ŏ��̃C���f�b�N�X�܂ł̃I�t�Z�b�g
								   0,								// �ŏ��̒��_�C���f�b�N�X
								   m_NumVertex,				// ���_��
								   0,								// �X�^�[�g�C���f�b�N�X�i�ǂݎn�߂̏ꏊ�H)
								   m_NumPolygon				// �v���~�e�B�u�̐�
								   );		
}

/*------------------------------------------------------------------------------
  �@�쐬
------------------------------------------------------------------------------*/
CMeshField* CMeshField::Create( void )
{
	CMeshField* field = new CMeshField( 1 );
	field->Init();
	return field;
}

/*------------------------------------------------------------------------------
  �@�R�c�`�揀��
------------------------------------------------------------------------------*/
void CMeshField::Set3D( void )
{
	// �f�o�C�X�̃|�C���^�擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// --- ���[���h���W�ϊ��s��̍쐬 ---
	D3DXMATRIX mtxWorld,
			   mtxRotY,
			   mtxPos;	// ���[���h���W�ϊ��s��
	
	// �P�ʍs��ŏ���������
	D3DXMatrixIdentity( &mtxWorld );

	// ��]�s��̍쐬
	static float fRadian = 0.0f;
	//fRadian += 0.02f;

	D3DXMatrixRotationYawPitchRoll( &mtxRotY,				  		   // �i�[�p
									fRadian, /*D3DXToRadian( 45 ),*/ // Y��
									0.0f,						   	   // X��
									0.0f							   // Z��
									);
	
	// �s��̐ώZ
	D3DXMatrixMultiply( &mtxWorld, // �o��
						&mtxWorld, // ����
						&mtxRotY   // �E��
						);

	// --- ���s�ړ��s��̔��f ---

	// ���s�ړ��s��쐬�֐�
	D3DXMatrixTranslation( &mtxPos,			// �i�[�p
						   0.0f,	// X�ړ���
						   0.0f,	// Y�ړ���
						   0.0f		// Z�ړ���
						   );	

	// �s��̐ώZ
	D3DXMatrixMultiply( &mtxWorld, // �o��
						&mtxWorld, // ����
						&mtxPos   // �E��
						);

	// �f�o�C�X�ɐݒ�
	pDevice->SetTransform( D3DTS_WORLD, // ���[���h���W
								&mtxWorld	 // 
							    );				 
}

/*------------------------------------------------------------------------------
  �@�����擾
------------------------------------------------------------------------------*/
float CMeshField::GetHeight( D3DXVECTOR3 Position )
{
	VERTEX_3D* pVtx;  // VRAM�̉��z���_�A�h���X���i�[

	// ���_�o�b�t�@�����b�N���āA���z���_�A�h���X���擾����
	if( FAILED ( ( m_pVtxBuffer )->Lock( 0,
									     0,				// ���ׂĂ����b�N
								         ( void** )&pVtx,  // ���z���_�A�h���X�p�|�C���^�̃A�h���X��n��
									     0 ) ) )			// ���b�N�t���O�H
								         {	
									 	    return E_FAIL;
									     }

	// �����|���S��
	for( int nCntZ = 0; nCntZ < m_NumRow; nCntZ++ )
	{
		for( int nCntX = 0; nCntX < m_NumColumn; nCntX++ )
		{
			D3DXVECTOR3 p0 = pVtx[ ( nCntZ + 1 ) * ( m_NumColumn + 1 ) + nCntX ].pos;
			D3DXVECTOR3 p1 = pVtx[ ( nCntZ )	 * ( m_NumColumn + 1 ) + nCntX ].pos;
			D3DXVECTOR3 p2 = pVtx[ ( nCntZ + 1 ) * ( m_NumColumn + 1 ) + nCntX + 1 ].pos;

			D3DXVECTOR3 v01 = p1 - p0;
			D3DXVECTOR3 v0p = Position - p0;
			D3DXVECTOR3 vc0; // ����p�x�N�g��
			D3DXVec3Cross( &vc0, &v01, &v0p );

			if( vc0.y >= 0.0f )
			{
				D3DXVECTOR3 v12 = p2 - p1;
				D3DXVECTOR3 v1p = Position - p1;
				D3DXVECTOR3 vc1; // ����p�x�N�g��
				D3DXVec3Cross( &vc1, &v12, &v1p );

				if( vc1.y >= 0.0f )
				{
					D3DXVECTOR3 v20 = p0 - p2;
					D3DXVECTOR3 v3p = Position - p2;
					D3DXVECTOR3 vc2; // ����p�x�N�g��
					D3DXVec3Cross( &vc2, &v20, &v3p );

					if( vc2.y >= 0.0f )
					{
						D3DXVECTOR3 v02 = p2 - p0;
						D3DXVECTOR3 vn; // �ʖ@��
						D3DXVec3Cross( &vn, &v01, &v02 );
						D3DXVec3Normalize( &vn, &vn );

						// �����v�Z
						Position.y = p0.y - ( ( Position.x - p0.x ) * vn.x + ( Position.z - p0.z ) * vn.z ) / vn.y;
					}
				}
			}
		}
	}
	
	// �E��|���S��
	for( int nCntZ = 0; nCntZ < m_NumRow; nCntZ++ )
	{
		for( int nCntX = 0; nCntX < m_NumColumn; nCntX++ )
		{
			D3DXVECTOR3 p0 = pVtx[ ( nCntZ )     * ( m_NumColumn + 1 ) + nCntX + 1 ].pos;
			D3DXVECTOR3 p2 = pVtx[ ( nCntZ )	 * ( m_NumColumn + 1 ) + nCntX ].pos;
			D3DXVECTOR3 p1 = pVtx[ ( nCntZ + 1 ) * ( m_NumColumn + 1 ) + nCntX + 1 ].pos;

			D3DXVECTOR3 v01 = p1 - p0;
			D3DXVECTOR3 v0p = Position - p0;
			D3DXVECTOR3 vc0; // ����p�x�N�g��
			D3DXVec3Cross( &vc0, &v01, &v0p );

			if( vc0.y >= 0.0f )
			{
				D3DXVECTOR3 v12 = p2 - p1;
				D3DXVECTOR3 v1p = Position - p1;
				D3DXVECTOR3 vc1; // ����p�x�N�g��
				D3DXVec3Cross( &vc1, &v12, &v1p );

				if( vc1.y >= 0.0f )
				{
					D3DXVECTOR3 v20 = p0 - p2;
					D3DXVECTOR3 v3p = Position - p2;
					D3DXVECTOR3 vc2; // ����p�x�N�g��
					D3DXVec3Cross( &vc2, &v20, &v3p );

					if( vc2.y >= 0.0f )
					{
						D3DXVECTOR3 v02 = p2 - p0;
						D3DXVECTOR3 vn; // �ʖ@��
						D3DXVec3Cross( &vn, &v01, &v02 );
						D3DXVec3Normalize( &vn, &vn );

						// �����v�Z
						Position.y = p0.y - ( ( Position.x - p0.x ) * vn.x + ( Position.z - p0.z ) * vn.z ) / vn.y;
					}
				}
			}
		}
	}
	
	// ���b�N����
	m_pVtxBuffer->Unlock();

	return Position.y;
}

//------------------------------------------------------------------------------
//�@���[�h
//------------------------------------------------------------------------------
void CMeshField::Load(void)
{
	char temp[256] = {};
	sprintf(temp, "data\\stage.bin");
	FILE* fp;
	fp = fopen(temp, "rb");
	if (fp == NULL)
	{
		MessageBox(NULL, "�o�C�i���t�@�C���I�[�v�����s", "�G���[", MB_OK);
		return;
	}

	fread(&m_FieldHeight[0], sizeof(float), (FIELD_NUM_COLUMN + 1) * (FIELD_NUM_ROW + 1), fp);

	fclose(fp);
}