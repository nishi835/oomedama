/*==============================================================================

    main�̃w�b�_�[ [main.h]
                                                       �쐬�� : �����@�S��
                                                       �쐬�� : 2016/4/17
--------------------------------------------------------------------------------
    ��Update : 
==============================================================================*/
#ifndef _MAIN_H_
#define _MAIN_H_

/*------------------------------------------------------------------------------
  �@�w�b�_�t�@�C��
------------------------------------------------------------------------------*/
#include <Windows.h>
#include <d3dx9.h>
#define DIRECTINPUT_VERSION ( 0x0800 )
#include <dinput.h>						// �����Ԃ�K�����
#include <stdio.h>

// ���C�u�����̃����N
#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )
#pragma comment( lib, "dxguid.lib" )
#pragma comment( lib, "dinput8.lib" )   // DirectInput8�̃����N

/*------------------------------------------------------------------------------
  �@�}�N����`
------------------------------------------------------------------------------*/
#define SCREEN_WIDTH ( 800 ) //�E�B���h�E�̕�
#define SCREEN_HEIGHT ( 600 ) //�E�B���h�E�̍���
#define TEXTURENAME "data/TEXTURE/gang02.png"

// ���_�t�H�[�}�b�g
#define FVF_VERTEX_2D ( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 )  // ( ���W�ϊ��ςݒ��_���W | ���_�J���[ | �e�N�X�`�����W )
#define FVF_VERTEX_3D ( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 )  // ( ���W�ϊ��ςݒ��_���W | �@�� | ���_�J���[ | �e�N�X�`�� )

// �Z�[�t�����[�X�}�N��
#define SAFE_RELEASE( x ) { if( x ) { ( x )->Release(); ( x ) = NULL; } }

/*------------------------------------------------------------------------------
  �@�\���̂̐錾
------------------------------------------------------------------------------*/
// ���_���\����( ��̒��_�t�H�[�}�b�g�ƍ\�������킹�邱�� )
typedef struct 
{
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR color;
	D3DXVECTOR2 tex;	// �t�u���W�̍\���́@���K���\���̂̍Ō�ɐ錾����
}VERTEX_2D;

// ���_���W�\����( ��̒��_�t�H�[�}�b�g�ƍ\�������킹�邱�� )
typedef struct 
{
	D3DXVECTOR3 pos; // ���_���W�̍\����
	D3DXVECTOR3 normal;
	D3DCOLOR	color; // ���_�J���[�̍\����
	D3DXVECTOR2 tex; // �t�u���W�̍\���́@���K���\���̂̍Ō�ɐ錾����
}VERTEX_3D;

/*------------------------------------------------------------------------------
  �@�v���g�^�C�v�錾
------------------------------------------------------------------------------*/
LRESULT CALLBACK WndProc( HWND hWnd, //�E�B���h�E�̔ԍ�
						UINT uMsg,	 //�E�B���h�E���b�Z�[�W
						WPARAM wParam,
						LPARAM lParam );

HWND GethWnd(void);

#endif