/*==============================================================================

sceneのヘッダ [scene.h]
作成者 : 中西　祐介
作成日 : 2016/5/31
--------------------------------------------------------------------------------
■Update :
==============================================================================*/
#ifndef _SCENE_H_
#define _SCENE_H_

/*------------------------------------------------------------------------------
ヘッダファイル
------------------------------------------------------------------------------*/
#include "main.h"
#include <vector>

#define NUM_PRIORITY (PRIORITY_MAX)

/*------------------------------------------------------------------------------
　クラス
 ------------------------------------------------------------------------------*/
class CScene
{
public:
	typedef enum
	{
		OBJTYPE_NONE = 0,	// タイプなし
		OBJTYPE_GANG,
		OBJTYPE_PLAYER,		// プレイヤー
		OBJTYPE_MESHFIELD,
		OBJTYPE_MAX			// タイプマックス
	}OBJTYPE;

	typedef enum
	{
		PRIORITY_3D = 0,
		PRIORITY_BILLBOARD,
		PRIORITY_2D,
		PRIORITY_MAX
	}PRIORITY;

private:
	static CScene* m_Top[NUM_PRIORITY];   // リストの先頭のポインタ
	CScene* m_Next;							// 次のシーンのポインタ
	bool m_Delete;							// 削除フラグ
	static int m_nNumScene;				    // オブジェクトの総数
	int m_nID;							    // オブジェクト固有ID
	OBJTYPE m_objType;                      // オブジェクトのタイプ

public:
	CScene() {};
	CScene(int Priority);
	~CScene();

	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	static void CheckRelease(void); // 削除フラグをチェックして、trueのものを削除

	static void UpdateAll(void);
	static void DrawAll(void);
	static void ReleaseAll(void);

	// セッター
	void SetPos(const D3DXVECTOR3& pos) { m_pos = pos; }
	void SetSize(const D3DXVECTOR3& size) { m_size = size; }
	void SetObjType(const OBJTYPE& objtype) { m_objType = objtype; }			// オブジェクトのタイプ設定
	void SetDoUninit(const bool doUninit) { m_doUninit = doUninit; }
	void SetDelete(void) { m_Delete = true; };
	void SetLenToCamLine(float lenToCamLine) { m_lenToCamLine = lenToCamLine; }

	void AddPos(const D3DXVECTOR3& pos) { m_pos += pos; }

	// ゲッター
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetSize(void) { return m_size; }
	OBJTYPE GetObjType(void) { return m_objType; }						// オブジェクトのタイプ取得
	static CScene* GetList(int Priority) { return m_Top[Priority]; }	// プライオリティ別のオブジェクトリストの取得
	bool GetDoUninit(void) { return m_doUninit; }
	float GetSetLenToCamLine(void) { return m_lenToCamLine; }

	// その他のメソッド
	static void CheckUninit(void);
	static void SortBillboard(void);

protected:
	D3DXVECTOR3	 m_pos;				// ポリゴンの位置
	D3DXVECTOR3  m_size;			// ポリゴンのサイズ
	bool m_doUninit;  // 削除フラグ
	static std::vector<CScene*> c_scene;
	float m_lenToCamLine; // カメラからの真横直線までの距離

};

#endif