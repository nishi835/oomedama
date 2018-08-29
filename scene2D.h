/*==============================================================================

    �|���S�������̃w�b�_ [polygon.h]
                                                       �쐬�� : �����@�S��
                                                       �쐬�� : 2016/5/31
--------------------------------------------------------------------------------
    ��Update : 
==============================================================================*/
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

/*------------------------------------------------------------------------------
    �w�b�_�t�@�C��
------------------------------------------------------------------------------*/
#include "main.h"
#include "scene.h"

/*------------------------------------------------------------------------------
  �@�N���X
------------------------------------------------------------------------------*/
class CScene2D : public CScene
{
public:
	CScene2D( int Priority ) : CScene( Priority )
	{	
		m_pVtxBuff = NULL;
	};

	~CScene2D();

	void Init(void);
	virtual void Uninit( void )override;
	virtual void Update( void )override;
	virtual void Draw( void )override;

	// �Z�b�^�[
	void SetTexID(int TexID) { m_TexID = TexID; }
	void SetAlpha(const float& alpha) { m_color.a = alpha; }

	void AddAlpha(const float& value) { m_color.a += value; }

	// �Q�b�^�[
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	float GetAlpha(void) { return m_color.a; }

	// ���̑�
	void SetVertex( void );
	
protected:
	D3DXVECTOR2  m_leftup;			// ����̒��_XY
	D3DXVECTOR2  m_rightup;			// �E��̒��_XY
	D3DXVECTOR2  m_leftdown;		// �����̒��_XY
	D3DXVECTOR2  m_rightdown;		// �E���̒��_XY	
	D3DXVECTOR2  m_tex;				// �|���S����UV�l
	D3DXVECTOR2  m_texsize;			// �|���S����UV�l�̑傫��
	D3DXCOLOR    m_color;

	float		 m_length;			// �|���S���̑Ίp���̒���
	float		 m_angle;			// �|���S���̑Ίp���̊p�x
	float		 m_rot;

	bool         m_use;				// �g�p�t���O
	int			 m_TexID;           // �e�N�X�`����ID

private:	
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;
};

#endif