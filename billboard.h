/*==============================================================================

    billboard�̃w�b�_�[ [billboard.h]
                                                       �쐬�� : �����@�S��
                                                       �쐬�� : 
--------------------------------------------------------------------------------
    ��Update : 
==============================================================================*/
#ifndef _BILLBORAD_H_
#define _BILLBORAD_H_

/*------------------------------------------------------------------------------
  �@�w�b�_�t�@�C��
------------------------------------------------------------------------------*/
#include "scene.h"

/*------------------------------------------------------------------------------
  �@�}�N����`
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
  �@�N���X�錾
------------------------------------------------------------------------------*/
class CBillboard : public CScene
{	
public:
	CBillboard( int Priority ) : CScene( Priority ){};
	~CBillboard();

	HRESULT Init( void );
	void Uninit( void );
	void Update( void );
	void Draw( void );

	// �Z�b�^�[
	void SetTex(D3DXVECTOR2 tex) { m_tex = tex; }
	void SetTexSize(D3DXVECTOR2 texSize) { m_texSize = texSize; }
	void SetAlpha(int alpha) { m_alpha = alpha; }
	void SetTexID(int TexID) { m_TexID = TexID; }

	void AddAlpha(int value) { m_alpha += value; }

	// �Q�b�^�[
	int GetAlpha(void) { return m_alpha; }

	// ���̑��̃��\�b�h
	void Set3D( void );

protected:
	D3DXVECTOR2 m_tex;
	D3DXVECTOR2 m_texSize;
	float m_rot;
	int m_alpha;
	int m_TexID;                    // �e�N�X�`����ID
	
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; // ���_�o�b�t�@�C���^�[�t�F�[�X�̊i�[
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff; // �C���f�b�N�X�o�b�t�@�C���^�[�t�F�[�X�̊i�[
};

#endif

