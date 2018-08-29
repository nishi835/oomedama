/*==============================================================================

    renderer�̃w�b�_ [camera.h]
                                                       �쐬�� : �����@�S��
                                                       �쐬�� : 2016/5/31
--------------------------------------------------------------------------------
    ��Update : 
==============================================================================*/
#ifndef _RENDERER_H_
#define _RENDERER_H_

/*------------------------------------------------------------------------------
    �w�b�_�t�@�C��
------------------------------------------------------------------------------*/
#include "main.h"

/*------------------------------------------------------------------------------
  �@�N���X
------------------------------------------------------------------------------*/
class CRenderer
{
public:
	static HRESULT Init( HINSTANCE hInstance, HWND hWnd, BOOL bWindow );
	static void Uninit( void );
	static void Update( void );
	static void DrawBegin( void );
	static void DrawEnd( void );
	static LPDIRECT3DDEVICE9 GetDevice( void )
	{
		return m_D3DDevice;
	}

private:
	static LPDIRECT3D9 m_D3D;
	static LPDIRECT3DDEVICE9 m_D3DDevice;
	static LPD3DXFONT m_pFont;
};

#endif