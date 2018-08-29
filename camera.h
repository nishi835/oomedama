/*==============================================================================

    camera�̃w�b�_ [camera.h]
                                                       �쐬�� : �����@�S��
                                                       �쐬�� : 2016/5/31
--------------------------------------------------------------------------------
    ��Update : 
==============================================================================*/
#ifndef _CAMERA_H_
#define _CAMERA_H_

/*------------------------------------------------------------------------------
    �w�b�_�t�@�C��
------------------------------------------------------------------------------*/
#include "main.h"

/*------------------------------------------------------------------------------
  �@�N���X
------------------------------------------------------------------------------*/
class CCamera
{
public:
	CCamera();
	~CCamera();

	void Init(void);
	void Uninit(void);
	void Update(void);

	// �Q�b�^�[
	D3DXVECTOR3 GetPosAt(void) { return m_posAt; }
	D3DXVECTOR3 GetPosEye(void) { return m_posEye;	}
	D3DXVECTOR3 GetPosAtTarget(void) { return m_posAtTarget; }
	D3DXVECTOR3 GetPosEyeTarget(void) { return m_posEyeTarget; }
	D3DXVECTOR3 GetFlatLine(void) { return m_flatLine; }
	float GetRotXY(void) { return m_rotXY; }
	float GetRotXZ(void) { return m_rotXZ; }

	// �Z�b�^�[
	void SetPosAt(D3DXVECTOR3 posAt) { m_posAt = posAt; }
	void SetPosEye(D3DXVECTOR3 posEye) { m_posEye = posEye; }
	void SetPosAtTarget(D3DXVECTOR3 posEyeTarget) { m_posAt = posEyeTarget; }
	void SetPosEyeTarget(D3DXVECTOR3 posAtTarget) { m_posEye = posAtTarget; }

	void AddPosEye(D3DXVECTOR3 posEye) { m_posEye += posEye; }
	void AddPosAt(D3DXVECTOR3 posAt) { m_posAt += posAt; }
	void AddPosEyeTarget(D3DXVECTOR3 posEyeTarget) { m_posEyeTarget += posEyeTarget; }
	void AddPosAtTarget(D3DXVECTOR3 posAtTarget) { m_posAtTarget += posAtTarget; }
	void AddRotXY(float rotXY) { m_rotXY += rotXY; }
	void AddRotXZ(float rotXZ) { m_rotXZ += rotXZ; }

	// ���̑�
	static CCamera* Create(void);
	
private:
	D3DXVECTOR3 m_posEye;		 // �J�����̍��W
	D3DXVECTOR3 m_posEyeTarget;	 // �J�������W�̖ڕW�_
	D3DXVECTOR3 m_posAt;		 // �J�����̒����_
	D3DXVECTOR3 m_posAtTarget;   // �J���������_�̖ڕW�_
	D3DXVECTOR3 m_vecUp;		 // �J�����̏����
	D3DXVECTOR3 m_flatLine;      // �J�������W��ʂ�^�������̃x�N�g��
	float m_rotXY;				 // �J�����̊p�x�iXY���ʏ�j
	float m_rotXZ;				 // �J�����̊p�x�iXZ���ʏ�j
	float m_distance;		     // �J�����̒����_�܂ł̋���
};

#endif