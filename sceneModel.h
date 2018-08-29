/*==============================================================================

    sceneModel�̃w�b�_ [sceneModel.h]

                                                       �쐬�� : �����@�S��
==============================================================================*/
#ifndef _SCENEMODEL_H_
#define _SCENEMODEL_H_

/*------------------------------------------------------------------------------
    �w�b�_�t�@�C��
------------------------------------------------------------------------------*/
#include "main.h"
#include "scene.h"
#include <string.h>

/*------------------------------------------------------------------------------
  �@�N���X
------------------------------------------------------------------------------*/
class CSceneModel : public CScene
{
public:
	CSceneModel( int Priority ) : CScene( Priority ){};
	~CSceneModel(){};

	void Init( void );
	void Uninit( void );
	void Update( void );
	void Draw( void );

	// �Q�b�^�[
	float GetRotThe(void) { return m_rotThe; }
	float GetRotFai(void) { return m_rotFai; }
	float GetRadius(void) { return m_radius; }
	D3DXVECTOR3 GetVelocity(void) { return m_velocity; }

	// �Z�b�^�[
	void SetVelocity(const D3DXVECTOR3& velocity) { m_velocity = velocity; }
	void SetRotThe(const float& rotThe) { m_rotThe = rotThe; }
	void SetRotFai(const float& rotFai) { m_rotFai = rotFai; }
	void SetRadius(const float& radius) { m_radius = radius; }
	void AddRotThe(const float& rotThe) { m_rotThe += rotThe; }
	void AddRotFai(const float& rotFai) { m_rotFai += rotFai; }

	// ���̑��̃��\�b�h
	static void SetFilePass(const char* filePass) { strcpy(m_filePass, filePass); }
	static CSceneModel* Create(D3DXVECTOR3 pos, float rotThe, float rotFai, char* filePass);

protected:
	float m_rotThe;
	float m_rotFai;
	float m_radius;
	D3DXVECTOR3 m_velocity;
	static char m_filePass[256];

	LPD3DXMESH			m_pMeshModel;		// ���b�V�����C���^�[�t�F�[�X�̊i�[

private:
	LPD3DXBUFFER		m_pBuffMatModel;    // �}�e���A�����������C���^�[�t�F�[�X�ւ̃|�C���^�̊i�[
	LPDIRECT3DTEXTURE9  m_pTextureModel;    // �e�N�X�`���C���^�[�t�F�[�X�̊i�[�p
	DWORD				m_nNumMatModel;		// �}�e���A���̐�
};

#endif