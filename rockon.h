/*==============================================================================

rockon�̃w�b�_�[ [rockon.h]
�쐬�� : �����@�S��
�쐬�� :
--------------------------------------------------------------------------------
��Update :
==============================================================================*/
#ifndef _ROCKON_H_
#define _ROCKON_H_

//------------------------------------------------------------------------------
//  �w�b�_�t�@�C��
//------------------------------------------------------------------------------
#include "billboard.h"

//------------------------------------------------------------------------------
//  �}�N����`
//------------------------------------------------------------------------------
#define ROCKON001_TEXTURENAME "data/TEXTURE/rockon.png"
#define MAX_ROCKON (15)
#define ROCKON_SIZE_X (7.0f)
#define ROCKON_SIZE_Y (7.0f)

//------------------------------------------------------------------------------
//  �N���X
//------------------------------------------------------------------------------
class CRockon : public CBillboard
{
public:
	CRockon(int Priority) : CBillboard(Priority) {};
	~CRockon();

	void Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �Q�b�^�[
	bool GetUse(void) { return m_use; }
	int GetTimer(void) { return m_timer; }
	int GetRockonID(void) { return m_rockonID; }

	// �Z�b�^�[
	void SetUse(bool use) { m_use = use; }
	void SetRockonID(int rockonID) { m_rockonID = rockonID; }

	static CRockon* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int rockonID, char* filePass);

private:
	int m_timer;
	int m_rockonID;
	bool m_use;

};

#endif