/*==============================================================================

    renderer�̏��� [renderer.cpp]
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

LPDIRECT3D9 CRenderer::m_D3D = NULL;
LPDIRECT3DDEVICE9 CRenderer::m_D3DDevice = NULL;
LPD3DXFONT CRenderer::m_pFont = NULL;

//=============================================================================
// �����_���[�̏���������
//=============================================================================
HRESULT CRenderer::Init( HINSTANCE hInstance, HWND hWnd, BOOL bWindow )
{
	D3DPRESENT_PARAMETERS d3dpp; // �f�o�C�X����邽�߂̐ݒ�̊i�[
	D3DDISPLAYMODE d3ddm; // �f�B�X�v���C���[�h�̊i�[

	// Direct3D�C���^�[�t�F�C�X�̎擾
	m_D3D = Direct3DCreate9( D3D_SDK_VERSION );
	if( m_D3D == NULL )
	{
		return E_FAIL; // HRESULT�^�̖߂�l�̓G���[�̓��e������
	}

	// �f�B�X�v���C���[�h�̎擾
	if( FAILED( m_D3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm ) ) ) // FAILED�}�N���ł�����ƁABOOL�^�ɃL���X�g�����
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���g�p�����[�^�[�̐ݒ�i �f�o�C�X����邽�߂̐ݒ�̐ݒ� )
	ZeroMemory( &d3dpp, sizeof( d3dpp ) ); // ��������Ԃ�0�Ŗ��߂� 

	// �o�b�N�o�b�t�@�̐ݒ�
	d3dpp.BackBufferWidth = SCREEN_WIDTH; // �o�b�N�o�b�t�@�̕�
	d3dpp.BackBufferHeight = SCREEN_HEIGHT; // �o�b�N�o�b�t�@�̍���
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1; // �o�b�N�o�b�t�@�̐�

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD; // �X���b�v�G�t�F�N�g�̐ݒ�
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16; // �X�e���V���o�b�t�@���g���Ƃ��ɕύX
	d3dpp.Windowed = bWindow; // �t���X�N���[���ɂ���Ƃ���TRUE�ɂ���
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; // �t���X�N���[���ɂ���Ƃ��ɓK�X���l������
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT; // 

	// Direct3D�f�o�C�X�̍쐬
	if( FAILED( m_D3D->CreateDevice( D3DADAPTER_DEFAULT, // �O���t�B�b�N�{�[�h�̑I��
									  D3DDEVTYPE_HAL, // �n�[�h�E�F�A���`��
									  hWnd, // �E�B���h�E�w��
									  D3DCREATE_HARDWARE_VERTEXPROCESSING, // �`��A���_�����̓n�[�h�E�F�A�ɔC����
									  &d3dpp,
									  &m_D3DDevice ) ) ) // �f�o�C�X���i�[
	{
		if( FAILED( m_D3D->CreateDevice( D3DADAPTER_DEFAULT, // �O���t�B�b�N�{�[�h�̑I��
										  D3DDEVTYPE_HAL, // �n�[�h�E�F�A���`��
										  hWnd, // �E�B���h�E�w��
										  D3DCREATE_SOFTWARE_VERTEXPROCESSING, // �`��̓n�[�h�E�F�A�A���_������CPU���s��
										  &d3dpp,
										  &m_D3DDevice ) ) ) // �f�o�C�X���i�[
		{
			if( FAILED( m_D3D->CreateDevice( D3DADAPTER_DEFAULT, // �O���t�B�b�N�{�[�h�̑I��
											  D3DDEVTYPE_REF, // �\�t�g�E�F�A( CPU )���`��
											  hWnd, // �E�B���h�E�w��
											  D3DCREATE_SOFTWARE_VERTEXPROCESSING, // �`��̓n�[�h�E�F�A�A���_������CPU���s��
											  &d3dpp,
											  &m_D3DDevice ) ) ) // �f�o�C�X���i�[
			{
				return E_FAIL; // �f�o�C�X�擾�s��
			}
		}
	}

	// *** �����_�[�X�e�[�g�i�f�o�C�X�ݒ�j�̐ݒ� ***

	// �J�����O�i�Жʕ`��j�̐ݒ� 
	m_D3DDevice->SetRenderState( D3DRS_CULLMODE,						  // �J�����O�ݒ�
								  D3DCULL_CCW );						  // �����ŃJ�����O

	// �|���S���̓h��Ԃ��ݒ�
	m_D3DDevice->SetRenderState( D3DRS_FILLMODE,						  // �h��Ԃ��ݒ�
								  D3DFILL_SOLID );						  // �ʂ�h��Ԃ�

	// �A���t�@�u�����h�i�������j�̐ݒ�
	m_D3DDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );		  // �A���t�@�u�����h���L�����ǂ���
	m_D3DDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );	  // �`�挳�i�X�v���C�g�j�̃A���t�@�u�����h�ݒ�
	m_D3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA); // �`���i�w�i�j�̃A���t�@�u�����h�ݒ�

	// *** �T���v���[�X�e�[�g�̐ݒ� ***

	m_D3DDevice->SetSamplerState( 0,
								   D3DSAMP_MINFILTER,    // �k����
								   D3DTEXF_LINEAR );     // ���j�A�t�B���^�[���w��
	
	m_D3DDevice->SetSamplerState( 0,
								   D3DSAMP_MAGFILTER,	 // �g�厞
								   D3DTEXF_LINEAR );	 // ���j�A�t�B���^�[���w��
	
	m_D3DDevice->SetSamplerState( 0,
								   D3DSAMP_ADDRESSU,	 // u���ix���j���A�h���b�V���O���[�h�ɐݒ�
								   D3DTADDRESS_WRAP );   // ���b�v���[�h

														 // *** �T���v���[�X�e�[�g�̐ݒ� ***

	 // �e�N�X�`���u�����f�B���O�̐ݒ�
	m_D3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);   // �����P,�e�N�X�`���̃A���t�@�l
	m_D3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);   // ���Z�q,��Z
	m_D3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);   // �����Q,�f�B�t���[�Y�i�|���S���j�̃A���t�@�l	

	// ���C�g�̏����� ////////////////////////////////////////////	

	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();	

	D3DLIGHT9 light;									  // ���C�g�̍\����
	ZeroMemory( &light, sizeof( D3DLIGHT9 ) );			  // �\���̂̏�����

	light.Type		   = D3DLIGHT_DIRECTIONAL;					// ���C�g�̃^�C�v 
	light.Diffuse	   = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );   // ���C�g(���s�����j�̃J���[(1.0f��100%�j
	light.Ambient	   = D3DXCOLOR( 0.8f, 0.8f, 0.8f, 1.0f );   // ����
	D3DXVECTOR3 vecDir = D3DXVECTOR3( 1.0f, -1.0f, 1.0f );		// ���C�g(���s�����j�̌���

	// ���C�g�x�N�g����P�ʃx�N�g����
	D3DXVec3Normalize( ( D3DXVECTOR3* )&light.Direction,   
					   &vecDir
					   );

	// �f�o�C�X�Ƀ��C�g��ݒ�
	pDevice->SetLight( 0, 
					   &light
					   );

	// ���C�g�̃X�C�b�`
	pDevice->LightEnable( 0,
						  TRUE
						  );

	// �A���r�G���g���C�g�̐ݒ�
	pDevice->SetRenderState( D3DRS_AMBIENT, 0x00202020 );


	return S_OK;

}

//=============================================================================
// �����_���[�̏I������
//=============================================================================
void CRenderer::Uninit( void )
{
	// �f�o�C�X�̔j��
	if( m_D3DDevice != NULL ) // �f�o�C�X���g�p�����ǂ������`�F�b�N
	{
		m_D3DDevice->Release(); // Direct3D�f�o�C�X�̉���@
		m_D3DDevice = NULL; // �f�o�C�X���i�[����Ă����A�h���X������
	}

	// �C���^�[�t�F�[�X�̔j��
	if( m_D3D != NULL ) // �C���^�[�t�F�[�X���g�p�����`�F�b�N
	{
		m_D3D->Release(); // Direct3D�C���^�[�t�F�[�X�̉��
		m_D3D = NULL; // �C���^�[�t�F�[�X���i�[����Ă����A�h���X������
	}
}

//=============================================================================
// �����_���[�̍X�V����
//=============================================================================
void CRenderer::Update( void )
{
}

//=============================================================================
// �����_���[�̕`��J�n
//=============================================================================
void CRenderer::DrawBegin( void )
{
	// ��ʁi�o�b�N�o�b�t�@�j�̃N���A�@
	m_D3DDevice->Clear( 0, 
					     NULL,
						 D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, // 
					     D3DCOLOR_RGBA( 0, 255, 255, 255 ),
						 1.0f,
						 0 );

	// �`��̊J�n
	m_D3DDevice->BeginScene(); // �����ŕ`��̃^�X�N��ςݏグ��	
}

//=============================================================================
// �����_���[�̕`��I��
//=============================================================================
void CRenderer::DrawEnd( void )
{
	// �`��̏I��
	m_D3DDevice->EndScene();	

	m_D3DDevice->Present( NULL, NULL, NULL, NULL ); // �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ��@
	// �����ߍ��񂾃^�X�N�������ł܂Ƃ߂ď�������
}