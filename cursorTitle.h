/*==============================================================================

cursorTitle�̃w�b�_�[ [cursorTitle.h]
�쐬�� : �����@�S��
�쐬�� :
--------------------------------------------------------------------------------
��Update :
==============================================================================*/
#ifndef _CURSORTITLE_H_
#define _CURSORTITLE_H_

//------------------------------------------------------------------------------
//  �w�b�_�t�@�C��
//------------------------------------------------------------------------------
#include "textureManager.h"
#include "scene2D.h"

//------------------------------------------------------------------------------
// �}�N����`
//------------------------------------------------------------------------------
#define NIRVANA_TEXTURENAME "data/TEXTURE/joubutsu.png"

//------------------------------------------------------------------------------
//  �N���X
//------------------------------------------------------------------------------
class CCursorTitle : public CScene2D
{
public:
	CCursorTitle(int Priority) : CScene2D(Priority) {};
	~CCursorTitle();

	void Init(void);
	void Uninit(void)override;
	void Update(void)override;
	void Draw(void)override;

	// �Z�b�^�[
	void SetUse(bool use) { m_use = use; }
	void SetPosition(int position) { m_position = position; }
	void AddPosition(int value) { m_position += value; }

	// �Q�b�^�[
	bool GetUse(void) { return m_use; }
	int GetPosition(void) { return m_position; }

	// ���̑��̃��\�b�h
	static CCursorTitle* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float alpha, char* filePass, CTextureManager::TEXTYPE textype);

private:
	int m_position;

	bool m_use;
};

#endif