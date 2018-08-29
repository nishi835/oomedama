/*==============================================================================

    score�̏��� [score.cpp]
                                                       �쐬�� : �����@�S��
                                                       �쐬�� : 
--------------------------------------------------------------------------------
    ��Update : 
==============================================================================*/

/*------------------------------------------------------------------------------
  �@�w�b�_�t�@�C��
------------------------------------------------------------------------------*/
#include "renderer.h"
#include "manager.h"
#include "score.h"

//=============================================================================
// �|���S���̏���������
//=============================================================================
HRESULT CScore::Init( int spritenum )
{	
	m_spriteNum = spritenum;
	m_leftup    = new D3DXVECTOR2[ m_spriteNum ];			// ����̒��_XY
	m_rightup   = new D3DXVECTOR2[ m_spriteNum ];			// �E��̒��_XY
	m_leftdown  = new D3DXVECTOR2[ m_spriteNum ];			// �����̒��_XY
	m_rightdown = new D3DXVECTOR2[ m_spriteNum ];			// �E���̒��_XY	
	m_tex	    = new D3DXVECTOR2[ m_spriteNum ];			// �|���S����UV�l
	m_texsize   = new D3DXVECTOR2[ m_spriteNum ];			// �|���S����UV�l�̑傫��
	m_color     = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// ���_�o�b�t�@�̍쐬
	if( FAILED( pDevice->CreateVertexBuffer( sizeof( VERTEX_2D ) * m_spriteNum * 4,  // �쐬���������_�o�b�t�@�̍��v�f�[�^�T�C�Y
											 D3DUSAGE_WRITEONLY,		  			 // ���_�o�b�t�@�̎g�p���@�i�������݂̂݁j
											 FVF_VERTEX_2D,						 	 // �H
											 D3DPOOL_MANAGED,						 // ���_�o�b�t�@�̒u����ƂȂ郁�������w��i�f�o�C�X�Ɉϑ��j
											 &m_pVtxBuff,							 // ���_�o�b�t�@�Ǘ��C���^�[�t�F�[�X���i�[
											 NULL ) ) )								 // �g��Ȃ�
											 {
												 return E_FAIL;
											 }

	// ���_�C���f�b�N�X�쐬
	pDevice->CreateIndexBuffer( sizeof( DWORD ) * m_spriteNum * 6,
							    0,
							    D3DFMT_INDEX32,
							    D3DPOOL_MANAGED,
							    &m_pIdxBuff,
							    NULL );

	// ���_�̃������𒼂ŃR�s�[����
	DWORD *vIndex;
	m_pIdxBuff->Lock( 0, 0, ( void** )&vIndex, 0 ); 

	for( int nCntSprite = 0; nCntSprite < m_spriteNum; nCntSprite++ )
	{
		// �����ŎO�p�`�����i�g���C�A���O�����X�g�j
		vIndex[ ( nCntSprite * 6 ) + 0 ] = ( nCntSprite * 4 ) + 0;  
		vIndex[ ( nCntSprite * 6 ) + 1 ] = ( nCntSprite * 4 ) + 1;
		vIndex[ ( nCntSprite * 6 ) + 2 ] = ( nCntSprite * 4 ) + 2;
		vIndex[ ( nCntSprite * 6 ) + 3 ] = ( nCntSprite * 4 ) + 2;
		vIndex[ ( nCntSprite * 6 ) + 4 ] = ( nCntSprite * 4 ) + 1;
		vIndex[ ( nCntSprite * 6 ) + 5 ] = ( nCntSprite * 4 ) + 3;
	}

	m_pIdxBuff->Unlock();

	// ���_�̐ݒ�
	SetVertex();

	// ������
	for (int nCntDigit = 0; nCntDigit < spritenum; nCntDigit++)
	{
		m_leftup[nCntDigit] = D3DXVECTOR2(m_pos.x + m_size.x * (-nCntDigit - 0.5f), m_pos.y - m_size.y * 0.5f);
		m_rightup[nCntDigit] = D3DXVECTOR2(m_pos.x + m_size.x * (-nCntDigit + 0.5f), m_pos.y - m_size.y * 0.5f);
		m_leftdown[nCntDigit] = D3DXVECTOR2(m_pos.x + m_size.x * (-nCntDigit - 0.5f), m_pos.y + m_size.y * 0.5f);
		m_rightdown[nCntDigit] = D3DXVECTOR2(m_pos.x + m_size.x * (-nCntDigit + 0.5f), m_pos.y + m_size.y * 0.5f);
		m_tex[nCntDigit] = D3DXVECTOR2(0.0f, 0.0f);
		m_texsize[nCntDigit] = D3DXVECTOR2(0.1f, 1.0f);
	}

	m_pos = D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z);
	m_size = D3DXVECTOR3(m_size.x, m_size.y, m_size.z);
	m_length = sqrt(m_size.x * m_size.x + m_size.y * m_size.y) / 2.0f;					// �Ίp���̒����̎Z�o
	m_angle = atan2(m_size.y, m_size.y);															// �Ίp���̊p�x�̎Z�o

	return S_OK;
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CScore::Uninit( void )
{
	// ���_�o�b�t�@�̔j��
	SAFE_RELEASE( m_pVtxBuff );
	
	// ���W�z��|�C���^�̔j��
	delete[] m_leftup;			// ����̒��_XY
	delete[] m_rightup;			// �E��̒��_XY
	delete[] m_leftdown;		// �����̒��_XY
	delete[] m_rightdown;		// �E���̒��_XY	
	delete[] m_tex;				// �|���S����UV�l
	delete[] m_texsize;			// �|���S����UV�l�̑傫��

	// �I������
	//Release();
	CScene::SetDelete();
}

//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CScore::Update( void )
{
	int nValue = m_score;			// �\������X�R�A
	int nNum = 0;					// �\�����錅�̒l

	for (int nNumDigit = 0; nNumDigit < m_spriteNum; nNumDigit++)
	{
		nNum = nValue % 10;
		nValue /= 10;
		m_tex[nNumDigit] = D3DXVECTOR2(nNum * 0.1f, 0.0f);
	}

	// ���_�̐ݒ�
	SetVertex();
}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CScore::Draw( void )
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
	pDevice->SetTexture( 0,	CTextureManager::BindTexture(m_TexID));			

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF( FVF_VERTEX_2D );

	// �v���~�e�B�u�i�|���S���j�̕`��
	pDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, // �v���~�e�B�u�̎��
								   0,				   // �`��J�n�ʒu�̃I�t�Z�b�g�i���_���j
								   0,				   // �ŏ��C���f�b�N�X�ԍ�
								   m_spriteNum * 6,	   // �ő�C���f�b�N�X�ԍ�
								   0,				   // �C���f�b�N�X�z��̓ǂݎ��ʒu
								   m_spriteNum * 2 );  // �`�悷��v���~�e�B�u�̐�
}

//=============================================================================
// ���_�̐ݒ�
//=============================================================================
void CScore::SetVertex( void )
{	
	VERTEX_2D* pVtx; // VRAM�̉��z�A�h���X���i�[

	// ���_�o�b�t�@�����b�N���āA���z�A�h���X���擾����
	m_pVtxBuff->Lock( 0,
					  0,			   // ���ׂĂ����b�N
					  ( void** )&pVtx, // ���z�A�h���X�p�|�C���^�̃A�h���X��n��
					  0 );			   // ���b�N�t���O�H
	
	// ���_���W�̐ݒ�( 2D���W�͉E���ɒ��_��p�ӂ��� )
	for( int nCntSprite = 0; nCntSprite < m_spriteNum; nCntSprite++ )
	{
		pVtx[ 0 ].pos = D3DXVECTOR3( m_leftup[ nCntSprite ].x,    m_leftup[ nCntSprite ].y,	   0.0f ); // �R���X�g���N�^�ɂ�钸�_�ݒ� ( x, y, z )
		pVtx[ 1 ].pos = D3DXVECTOR3( m_rightup[ nCntSprite ].x,   m_rightup[ nCntSprite ].y,   0.0f ); 
		pVtx[ 2 ].pos = D3DXVECTOR3( m_leftdown[ nCntSprite ].x,  m_leftdown[ nCntSprite ].y,  0.0f );
		pVtx[ 3 ].pos = D3DXVECTOR3( m_rightdown[ nCntSprite ].x, m_rightdown[ nCntSprite ].y, 0.0f ); 

		// rhw�̐ݒ�i�K��1.0f�j����O�����i�o�b�t�@�j�̏��H
		pVtx[ 0 ].rhw = 1.0f;
		pVtx[ 1 ].rhw = 1.0f;
		pVtx[ 2 ].rhw = 1.0f;
		pVtx[ 3 ].rhw = 1.0f;

		// ���_�J���[�̐ݒ�i 0 �` 255�̐����l )
		pVtx[ 0 ].color = D3DXCOLOR( m_color.r, m_color.g, m_color.b, m_color.a );
		pVtx[ 1 ].color = D3DXCOLOR( m_color.r, m_color.g, m_color.b, m_color.a ); 
		pVtx[ 2 ].color = D3DXCOLOR( m_color.r, m_color.g, m_color.b, m_color.a );
		pVtx[ 3 ].color = D3DXCOLOR( m_color.r, m_color.g, m_color.b, m_color.a );

		// ���_�f�[�^��UV�f�[�^��ǉ�
		pVtx[ 0 ].tex = D3DXVECTOR2( m_tex[ nCntSprite ].x,							    m_tex[ nCntSprite ].y );
		pVtx[ 1 ].tex = D3DXVECTOR2( m_tex[ nCntSprite ].x + m_texsize[ nCntSprite ].x, m_tex[ nCntSprite ].y );
		pVtx[ 2 ].tex = D3DXVECTOR2( m_tex[ nCntSprite ].x,								m_tex[ nCntSprite ].y + m_texsize[ nCntSprite ].y );
		pVtx[ 3 ].tex = D3DXVECTOR2( m_tex[ nCntSprite ].x + m_texsize[ nCntSprite ].x, m_tex[ nCntSprite ].y + m_texsize[ nCntSprite ].y );

		pVtx += 4;
	}

	// ���_�o�b�t�@�̃��b�N������
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �쐬
//=============================================================================
CScore* CScore::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int spriteNum, char* filePass)
{
	CScore* pScore = new CScore(CScene::PRIORITY_2D);
	pScore->SetPos(pos);
	pScore->SetSize(size);
	pScore->SetScore(0);
	pScore->SetTexID(CTextureManager::LoadTexture(filePass, CTextureManager::TEXTYPE_NONE));
	pScore->Init(spriteNum);

	return pScore;
}