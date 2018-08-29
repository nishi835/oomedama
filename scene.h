/*==============================================================================

scene�̃w�b�_ [scene.h]
�쐬�� : �����@�S��
�쐬�� : 2016/5/31
--------------------------------------------------------------------------------
��Update :
==============================================================================*/
#ifndef _SCENE_H_
#define _SCENE_H_

/*------------------------------------------------------------------------------
�w�b�_�t�@�C��
------------------------------------------------------------------------------*/
#include "main.h"
#include <vector>

#define NUM_PRIORITY (PRIORITY_MAX)

/*------------------------------------------------------------------------------
�@�N���X
 ------------------------------------------------------------------------------*/
class CScene
{
public:
	typedef enum
	{
		OBJTYPE_NONE = 0,	// �^�C�v�Ȃ�
		OBJTYPE_GANG,
		OBJTYPE_PLAYER,		// �v���C���[
		OBJTYPE_MESHFIELD,
		OBJTYPE_MAX			// �^�C�v�}�b�N�X
	}OBJTYPE;

	typedef enum
	{
		PRIORITY_3D = 0,
		PRIORITY_BILLBOARD,
		PRIORITY_2D,
		PRIORITY_MAX
	}PRIORITY;

private:
	static CScene* m_Top[NUM_PRIORITY];   // ���X�g�̐擪�̃|�C���^
	CScene* m_Next;							// ���̃V�[���̃|�C���^
	bool m_Delete;							// �폜�t���O
	static int m_nNumScene;				    // �I�u�W�F�N�g�̑���
	int m_nID;							    // �I�u�W�F�N�g�ŗLID
	OBJTYPE m_objType;                      // �I�u�W�F�N�g�̃^�C�v

public:
	CScene() {};
	CScene(int Priority);
	~CScene();

	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	static void CheckRelease(void); // �폜�t���O���`�F�b�N���āAtrue�̂��̂��폜

	static void UpdateAll(void);
	static void DrawAll(void);
	static void ReleaseAll(void);

	// �Z�b�^�[
	void SetPos(const D3DXVECTOR3& pos) { m_pos = pos; }
	void SetSize(const D3DXVECTOR3& size) { m_size = size; }
	void SetObjType(const OBJTYPE& objtype) { m_objType = objtype; }			// �I�u�W�F�N�g�̃^�C�v�ݒ�
	void SetDoUninit(const bool doUninit) { m_doUninit = doUninit; }
	void SetDelete(void) { m_Delete = true; };
	void SetLenToCamLine(float lenToCamLine) { m_lenToCamLine = lenToCamLine; }

	void AddPos(const D3DXVECTOR3& pos) { m_pos += pos; }

	// �Q�b�^�[
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetSize(void) { return m_size; }
	OBJTYPE GetObjType(void) { return m_objType; }						// �I�u�W�F�N�g�̃^�C�v�擾
	static CScene* GetList(int Priority) { return m_Top[Priority]; }	// �v���C�I���e�B�ʂ̃I�u�W�F�N�g���X�g�̎擾
	bool GetDoUninit(void) { return m_doUninit; }
	float GetSetLenToCamLine(void) { return m_lenToCamLine; }

	// ���̑��̃��\�b�h
	static void CheckUninit(void);
	static void SortBillboard(void);

protected:
	D3DXVECTOR3	 m_pos;				// �|���S���̈ʒu
	D3DXVECTOR3  m_size;			// �|���S���̃T�C�Y
	bool m_doUninit;  // �폜�t���O
	static std::vector<CScene*> c_scene;
	float m_lenToCamLine; // �J��������̐^�������܂ł̋���

};

#endif