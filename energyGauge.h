/*==============================================================================

energyGauge�̃w�b�_�[ [energyGauge.h]
�쐬�� : �����@�S��
�쐬�� :
--------------------------------------------------------------------------------
��Update :
==============================================================================*/
#ifndef _ENERGY_GAUGE_H_
#define _ENERGY_GAUGE_H_

/*------------------------------------------------------------------------------
�@�w�b�_�t�@�C��
------------------------------------------------------------------------------*/
#include "textureManager.h"
#include "scene2D.h"

/*------------------------------------------------------------------------------
 �@�}�N����`
------------------------------------------------------------------------------*/
#define ENERGYGAUGE_TEXTURENAME "data/TEXTURE/joubutsu.png"

/*------------------------------------------------------------------------------
  �@�N���X
------------------------------------------------------------------------------*/
class CEnergyGauge : public CScene2D
{
public:
	CEnergyGauge(int Priority) : CScene2D(Priority) {};
	~CEnergyGauge();

	void Init(void);
	void Uninit(void)override;
	void Update(void)override;
	void Draw(void)override;

	// �Z�b�^�[
	void SetEndSize(D3DXVECTOR3 endSize) { m_endSize = endSize; }
	void SetDeltaSize(D3DXVECTOR3 deltaSize) { m_deltaSize = deltaSize; }
	void SetPosX(float posx) { m_pos.x = posx; }
	void SetSizeX(float sizex) { m_size.x = sizex; }

	void AddSize(D3DXVECTOR3 value) { m_size += value; }

	// �Q�b�^�[
	D3DXVECTOR3 GetEndSize(void) { return m_endSize; }
	D3DXVECTOR3 GetDeltaSize(void) { return m_deltaSize; }

	// ���̑��̃��\�b�h
	static CEnergyGauge* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float alpha, char* filePass, CTextureManager::TEXTYPE textype);

private:
	D3DXVECTOR3 m_endSize;
	D3DXVECTOR3 m_deltaSize;
};

#endif