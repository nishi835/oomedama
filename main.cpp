
/*==============================================================================

    main�̏��� [main.cpp]
                                                       �쐬�� : �����@�S��
                                                       �쐬�� : 
--------------------------------------------------------------------------------
    ��Update : 
==============================================================================*/

/*------------------------------------------------------------------------------
  �@�w�b�_�[�t�@�C��
------------------------------------------------------------------------------*/
#include "main.h"
#include "manager.h"
#include "scene.h"    // �p���N���X�̃C���N���[�h�̑O�ɁA���N���X���C���N���[�h����
#include "scene2D.h"
#include "scene3D.h"
#include "sceneModel.h"

/*------------------------------------------------------------------------------
  �@�}�N����`
------------------------------------------------------------------------------*/
#define CLASS_NAME	"hoge"		 //�E�B���h�E�N���X��
#define WINDOW_NAME	"�^�C�g����" //�E�B���h�E�^�C�g��

#define NUM_VERTEX ( 4 )  // ���_�̐�
#define NUM_POLYGON ( 2 ) // �|���S���̖���

/*------------------------------------------------------------------------------
  �@�O���[�o���ϐ�
------------------------------------------------------------------------------*/
LPDIRECT3D9 g_pD3D = NULL; // Direct3D�C���^�[�t�F�[�X ( DX�̃o�[�W�������擾���� )�@��LP�`�̓|�C���^�^�I
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL; // Direct3D�f�o�C�X�ւ̃|�C���^ ( �O���t�B�b�N�{�[�h�ɃA�N�Z�X���邽�߂̃|�C���^ ) ���ŏd�v

HWND g_hWnd; //�E�B���h�E�n���h���i�|�C���^�j

/*------------------------------------------------------------------------------
  �@���C���֐�
------------------------------------------------------------------------------*/
int APIENTRY WinMain( HINSTANCE hInstance,
					  HINSTANCE hPrevInstance,
					  LPSTR lpCmdLine,
					  int nCmdShow )
{
	UNREFERENCED_PARAMETER( hPrevInstance );
	UNREFERENCED_PARAMETER( lpCmdLine );

	WNDCLASSEX wcex; //�E�B���h�E�N���X�\����

	wcex.cbSize			= sizeof( WNDCLASSEX ); //�\���̂̃T�C�Y
	wcex.style			= CS_CLASSDC; //�E�B���h�E�N���X�̃X�^�C����ݒ�
	wcex.lpfnWndProc	= WndProc; //�E�B���h�E�v���V�[�W���̊֐��|�C���^�i�A�h���X�j���w��
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance; //WinMain�̃p�����[�^�̃C���X�^���X�n���h�����w��
	wcex.hIcon			= NULL; //�E�B���h�E�A�C�R���̎w��
	wcex.hCursor		= LoadCursor( NULL, IDC_ARROW ); //�}�E�X�J�[�\���̎w��
	wcex.hbrBackground  = ( HBRUSH )( COLOR_WINDOW + 1 ); //�E�B���h�E�̃N���C�A���g�̈�̔w�i�F�̎w��
	wcex.lpszMenuName   = NULL; //�E�B���h�E���j���[�̎w��
	wcex.lpszClassName  = CLASS_NAME; //���̃E�B���h�E�N���X�̖��O
	wcex.hIconSm	    = NULL; //�~�j�A�C�R���̎w��

	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx( &wcex );

	MSG msg;

	//�E�B���h�E���쐬
	RECT cr = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	DWORD style = WS_OVERLAPPEDWINDOW;
	AdjustWindowRect( &cr, style, FALSE );
	int ww = cr.right - cr.left;
	int wh = cr.bottom - cr.top;
	
	// �f�X�N�g�b�v�̋�`���擾
	RECT dr;
	GetWindowRect( GetDesktopWindow(), &dr );
	int dw = dr.right - dr.left;
	int dh = dr.bottom - dr.top;

	// �E�B���h�E�̏����ʒu����ʒ����ɐݒ�
	int wx = ww > dw ? 0 : ( dw / 2 ) - ( ww / 2 );
	int wy = wh > dh ? 0 : ( dh / 2 ) - ( wh / 2 );

	g_hWnd = CreateWindowEx( 0, //�g���E�B���h�E�X�^�C��
			 		       CLASS_NAME, //�E�B���h�E�N���X�̖��O
					   	   WINDOW_NAME, //�E�B���h�E�̖��O
						   style ^ ( WS_MAXIMIZEBOX | WS_THICKFRAME ), //�E�B���h�E�̃X�^�C���i�^�C�v�j���d�v
						   wx, //�E�B���h�E�̏���X���W
						   wy, //�E�B���h�E�̏���Y���W
						   ww, //�E�B���h�E�̕��i�E�B���h�E�̃t���[�����܂ށj
						   wh, //�E�B���h�E�̍����i�E�B���h�E�̃t���[�����܂ށj
						   NULL, //�e�E�B���h�E�̃n���h��
						   NULL, //���j���[�o�[�̃n���h�����͎q�E�B���h�EID
						   hInstance, //�C���X�^���X
						   NULL ); //�E�B���h�E�쐬�f�[�^
	
	//�E�B���h�E�̕\��
	ShowWindow( g_hWnd, nCmdShow ); //�E�B���h�E�̌Ăяo��
	UpdateWindow( g_hWnd );
	
	// Manager�̏�����
	CManager::Init( hInstance, g_hWnd, TRUE );
	
	//���b�Z�[�W���[�v
	//��P�����F���b�Z�[�W���
	//��Q�����F�E�B���h�E�̃n���h��
	//�����b�Z�[�W���擾����܂œ��삪�~�܂�d�l�Ȃ̂ŁA�Q�[�����[�v�ɂ���ɂ͂��̂������������K�v������
	for( ;; )  //( GetMessage( &msg, NULL, 0, 0 ) ) //GetMessage�֐��ŁA�E�B���h�E���R���g���[������
	{
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) != 0)
		{
			// Windows�̏���
			if( msg.message == WM_QUIT )
			{
				break;
			}
			else
			{
				//���b�Z�[�W�̖|��Ƒ��o
				TranslateMessage( &msg ); 
				DispatchMessage( &msg ); //�E�B���h�E�v���V�[�W���Ƀ��b�Z�[�W�𑗏o
			}
		}
		else
		{
			//DirectX�̏���
			CManager::Update();
			CManager::Draw();
		}
	}

	// DirectX�̏I������
	CManager::Uninit();

	//�E�B���h�E�N���X�̓o�^�����i�E�B���h�E�̏I�������j���{���͎����I�ɂ���Ă����
	UnregisterClass( CLASS_NAME, wcex.hInstance );
	
	return ( int )msg.wParam;
}

/*------------------------------------------------------------------------------
�@  �E�B���h�E�v���V�[�W��
    (CALLBACK : Win32API�֐����Ăяo���Ƃ��̋K��
    g_hWnd :�E�B���h�E�̃n���h��
    uMsg :���b�Z�[�W�̎��ʎq
    wParam : ���b�Z�[�W�̍ŏ��̃p�����[�^(�⑫���) ���|�C���^�^�����A�p�r�͉��ł��悢
�@  lParam : ���b�Z�[�W�̂Q�Ԗڂ̃p�����[�^(�⑫���) ���|�C���^�^�����A�p�r�͉��ł��悢
------------------------------------------------------------------------------*/
LRESULT CALLBACK WndProc( HWND g_hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	HDC hDC; // �f�o�C�X�R���e�L�X�g�p�ϐ�
	PAINTSTRUCT ps;
	const RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	switch( uMsg )
	{
	case WM_DESTROY:
		DestroyWindow( g_hWnd );
		PostQuitMessage( 0 );
		break;

	case WM_KEYDOWN:
		switch( wParam )
		{
		// �I������
		case VK_ESCAPE:
			UINT nID = MessageBox( NULL, "�I�����܂���?",  "�I��", MB_YESNO );
			if( nID == IDYES )
			{
				DestroyWindow( g_hWnd );
			}
		}
		break;

	// �E�B���h�E�����ꂽ�Ƃ�
	case WM_CREATE:
		break;

	// �{�^���������ꂽ�Ƃ�
	case WM_COMMAND:
		break;

	// �`�惁�b�Z�[�W�̎�M
	case WM_PAINT:
		break;

	case WM_TIMER:
		//InvalidateRect( g_hWnd, NULL, TRUE );
		break;

	default:
		break;
	}

	return DefWindowProc( g_hWnd, uMsg, wParam, lParam );
}

/*------------------------------------------------------------------------------
�@�Q�b�^�[
 ------------------------------------------------------------------------------*/
HWND GethWnd(void)
{
	return g_hWnd;
}