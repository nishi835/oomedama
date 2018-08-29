/*==============================================================================

    score�̃w�b�_�[ [score.h]
                                                       �쐬�� : �����@�S��
                                                       �쐬�� : 
--------------------------------------------------------------------------------
    ��Update : 
==============================================================================*/
#ifndef _SCORE_H_
#define _SCORE_H_

/*------------------------------------------------------------------------------
  �@�w�b�_�t�@�C��
------------------------------------------------------------------------------*/
#include "main.h"
#include "scene.h"

/*------------------------------------------------------------------------------
�@�}�N��
------------------------------------------------------------------------------*/
#define SCORE_DIGIT (3)
#define SCORE_TEX_NAME "data/TEXTURE/number02.png"

/*------------------------------------------------------------------------------
�@�N���X
------------------------------------------------------------------------------*/
class CScore : public CScene
{
public:
	CScore(int Priority) : CScene(Priority) {};
	~CScore() {};

	HRESULT Init( int spritenum );
	void Uninit( void );
	void Update( void )override;
	void Draw( void )override;
	void SetVertex( void );
	
	static CScore* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int spritenum, char* filePass);

	// �Z�b�^�[
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetSize(D3DXVECTOR3 size) { m_size = size; }
	void SetScore(int score) { m_score = score; }
	void SetTexID(int TexID) { m_TexID = TexID; }

	void AddScore(int value) { m_score += value; }

	// �Q�b�^�[
	D3DXVECTOR3 GetPos(void) const { return m_pos; }					
	D3DXVECTOR3 GetSize( void ) const {	return m_size; }
	int GetScore(void) { return m_score; }
	
private:
	D3DXVECTOR3	 m_pos;				// �|���S���̈ʒu
	D3DXVECTOR3	 m_size;			// �|���S���̃T�C�Y
	D3DXVECTOR2* m_leftup;			// ����̒��_XY
	D3DXVECTOR2* m_rightup;			// �E��̒��_XY
	D3DXVECTOR2* m_leftdown;		// �����̒��_XY
	D3DXVECTOR2* m_rightdown;		// �E���̒��_XY	
	D3DXVECTOR2* m_tex;				// �|���S����UV�l
	D3DXVECTOR2* m_texsize;			// �|���S����UV�l�̑傫��
	D3DXCOLOR    m_color;
	float		 m_length;			// �|���S���̑Ίp���̒���
	float		 m_angle;			// �|���S���̑Ίp���̊p�x
	float		 m_score;
	int			 m_spriteNum;       // �|���S����
	int			 m_TexID;

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;
};

#endif