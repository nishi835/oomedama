/*==============================================================================

textBox�̃w�b�_�[ [textBox.h]
�쐬�� : �����@�S��
�쐬�� :
--------------------------------------------------------------------------------
��Update :
==============================================================================*/
#ifndef _TEXT_BOX_H_
#define _TEXT_BOX_H_

/*------------------------------------------------------------------------------
�@�w�b�_�t�@�C��
 ------------------------------------------------------------------------------*/
#include "textureManager.h"
#include "scene2D.h"

 /*------------------------------------------------------------------------------
 �@�}�N����`
  ------------------------------------------------------------------------------*/
#define NIRVANA_TEXTURENAME "data/TEXTURE/joubutsu.png"

  /*------------------------------------------------------------------------------
  �@�N���X
   ------------------------------------------------------------------------------*/
class CTextBox : public CScene2D
{
public:
	CTextBox(int Priority) : CScene2D(Priority) {};
	~CTextBox();

	void Init(void);
	void Uninit(void)override;
	void Update(void)override;
	void Draw(void)override;

	// �Z�b�^�[
	void SetEndPos(D3DXVECTOR3 endPos) { m_endPos = endPos; }
	void SetEndSize(D3DXVECTOR3 endSize) { m_endSize = endSize; }
	void SetVelocity(D3DXVECTOR3 velocity) { m_velocity = velocity; }
	void SetUse(bool use) { m_use = use; }
	void SetDeltaSize(D3DXVECTOR3 deltaSize) { m_deltaSize = deltaSize; }

	void AddSize(D3DXVECTOR3 value) { m_size += value; }

	// �Q�b�^�[
	D3DXVECTOR3 GetEndPos(void) { return m_endPos; }
	D3DXVECTOR3 GetEndSize(void) { return m_endSize; }
	D3DXVECTOR3 GetDeltaSize(void) { return m_deltaSize; }
	bool GetUse(void) { return m_use; }

	// ���̑��̃��\�b�h
	static CTextBox* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 endPos, D3DXVECTOR3 endSize, float alpha, char* filePass, CTextureManager::TEXTYPE textype);

private:
	D3DXVECTOR3 m_velocity;
	D3DXVECTOR3 m_endPos;
	D3DXVECTOR3 m_endSize;
	D3DXVECTOR3 m_deltaSize;
	int m_life;

	bool m_use;
};

#endif