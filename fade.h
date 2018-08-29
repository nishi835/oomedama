/*==============================================================================

    Fade�����̃w�b�_ [fade.h]
                                                       �쐬�� : �����@�S��
                                                       �쐬�� : 
--------------------------------------------------------------------------------
    ��Update : 
==============================================================================*/
#ifndef _FADE_H_
#define _FADE_H_

/*------------------------------------------------------------------------------
  �@�}�N��
------------------------------------------------------------------------------*/
#define FADE_TEXTURENAME "data/TEXTURE/fade00.png"		 // �e�N�X�`���t�@�C����

/*------------------------------------------------------------------------------
  �@�w�b�_�t�@�C��
------------------------------------------------------------------------------*/
#include "scene2D.h"
#include "main.h"

/*------------------------------------------------------------------------------
  �@�񋓑̂̐錾
------------------------------------------------------------------------------*/
class CFade
{
public:
	typedef enum
	{
		FADE_NONE = 0,
		FADE_IN,
		FADE_OUT,
		FADE_OUTEND,
		FADE_END,
		FADE_MAX
	}FADE;

	CFade() {}
	~CFade() {}

	void Init(void);
	void Uninit( void );
	void Update( void );
	void Draw( void );

	// �Z�b�^�[
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetSize(D3DXVECTOR3 size) { m_size = size; }
	void SetFadeMode(FADE fadeMode) { m_fadeMode = fadeMode; }
	void SetTexID(int TexID) { m_TexID = TexID; }

	// �Q�b�^�[
	FADE GetFadeMode(void) { return m_fadeMode; }
	
	// ���̑�
	static CFade* CFade::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, char* filePass);
	void SetVertex(void);

private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;
	D3DXVECTOR2  m_leftup;			// ����̒��_XY
	D3DXVECTOR2  m_rightup;			// �E��̒��_XY
	D3DXVECTOR2  m_leftdown;		// �����̒��_XY
	D3DXVECTOR2  m_rightdown;		// �E���̒��_XY	
	D3DXVECTOR2  m_tex;				// �|���S����UV�l
	D3DXVECTOR2  m_texsize;			// �|���S����UV�l�̑傫��
	D3DXCOLOR    m_color;
	FADE m_fadeMode;
	int m_TexID;

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;
};

#endif