/*==============================================================================

    cameraのヘッダ [camera.h]
                                                       作成者 : 中西　祐介
                                                       作成日 : 2016/5/31
--------------------------------------------------------------------------------
    ■Update : 
==============================================================================*/
#ifndef _CAMERA_H_
#define _CAMERA_H_

/*------------------------------------------------------------------------------
    ヘッダファイル
------------------------------------------------------------------------------*/
#include "main.h"

/*------------------------------------------------------------------------------
  　クラス
------------------------------------------------------------------------------*/
class CCamera
{
public:
	CCamera();
	~CCamera();

	void Init(void);
	void Uninit(void);
	void Update(void);

	// ゲッター
	D3DXVECTOR3 GetPosAt(void) { return m_posAt; }
	D3DXVECTOR3 GetPosEye(void) { return m_posEye;	}
	D3DXVECTOR3 GetPosAtTarget(void) { return m_posAtTarget; }
	D3DXVECTOR3 GetPosEyeTarget(void) { return m_posEyeTarget; }
	D3DXVECTOR3 GetFlatLine(void) { return m_flatLine; }
	float GetRotXY(void) { return m_rotXY; }
	float GetRotXZ(void) { return m_rotXZ; }

	// セッター
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

	// その他
	static CCamera* Create(void);
	
private:
	D3DXVECTOR3 m_posEye;		 // カメラの座標
	D3DXVECTOR3 m_posEyeTarget;	 // カメラ座標の目標点
	D3DXVECTOR3 m_posAt;		 // カメラの注視点
	D3DXVECTOR3 m_posAtTarget;   // カメラ注視点の目標点
	D3DXVECTOR3 m_vecUp;		 // カメラの上方向
	D3DXVECTOR3 m_flatLine;      // カメラ座標を通る真横方向のベクトル
	float m_rotXY;				 // カメラの角度（XY平面上）
	float m_rotXZ;				 // カメラの角度（XZ平面上）
	float m_distance;		     // カメラの注視点までの距離
};

#endif