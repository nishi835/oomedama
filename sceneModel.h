/*==============================================================================

    sceneModelのヘッダ [sceneModel.h]

                                                       作成者 : 中西　祐介
==============================================================================*/
#ifndef _SCENEMODEL_H_
#define _SCENEMODEL_H_

/*------------------------------------------------------------------------------
    ヘッダファイル
------------------------------------------------------------------------------*/
#include "main.h"
#include "scene.h"
#include <string.h>

/*------------------------------------------------------------------------------
  　クラス
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

	// ゲッター
	float GetRotThe(void) { return m_rotThe; }
	float GetRotFai(void) { return m_rotFai; }
	float GetRadius(void) { return m_radius; }
	D3DXVECTOR3 GetVelocity(void) { return m_velocity; }

	// セッター
	void SetVelocity(const D3DXVECTOR3& velocity) { m_velocity = velocity; }
	void SetRotThe(const float& rotThe) { m_rotThe = rotThe; }
	void SetRotFai(const float& rotFai) { m_rotFai = rotFai; }
	void SetRadius(const float& radius) { m_radius = radius; }
	void AddRotThe(const float& rotThe) { m_rotThe += rotThe; }
	void AddRotFai(const float& rotFai) { m_rotFai += rotFai; }

	// その他のメソッド
	static void SetFilePass(const char* filePass) { strcpy(m_filePass, filePass); }
	static CSceneModel* Create(D3DXVECTOR3 pos, float rotThe, float rotFai, char* filePass);

protected:
	float m_rotThe;
	float m_rotFai;
	float m_radius;
	D3DXVECTOR3 m_velocity;
	static char m_filePass[256];

	LPD3DXMESH			m_pMeshModel;		// メッシュ情報インターフェースの格納

private:
	LPD3DXBUFFER		m_pBuffMatModel;    // マテリアル情報を扱うインターフェースへのポインタの格納
	LPDIRECT3DTEXTURE9  m_pTextureModel;    // テクスチャインターフェースの格納用
	DWORD				m_nNumMatModel;		// マテリアルの数
};

#endif