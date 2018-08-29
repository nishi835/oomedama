/*==============================================================================

reticle�̏��� [reticle.cpp]
�쐬�� : �����@�S��
�쐬�� :
--------------------------------------------------------------------------------
��Update :
==============================================================================*/

//------------------------------------------------------------------------------
//�@�w�b�_�t�@�C��
//------------------------------------------------------------------------------
#include "main.h"
#include "modeGame.h"
#include "player.h"
#include "reticle.h"
#include "mediator.h"

//------------------------------------------------------------------------------
// �}�N����`
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// �f�X�g���N�^
//------------------------------------------------------------------------------
CReticle::~CReticle()
{
}

//------------------------------------------------------------------------------
//�@������
//------------------------------------------------------------------------------
void CReticle::Init()
{
	// ������
	m_rockonID = 0;

	// �r���{�[�h�̏�����
	CBillboard::Init();

	// �I�u�W�F�N�g�^�C�v�̐ݒ�
	SetObjType(OBJTYPE_MESHFIELD);
}

//------------------------------------------------------------------------------
//�@�I������
//------------------------------------------------------------------------------*/
void CReticle::Uninit(void)
{
	CBillboard::Uninit();
	CScene::SetDelete();
}

//------------------------------------------------------------------------------
//�@�X�V
//------------------------------------------------------------------------------
void CReticle::Update(void)
{
	CPlayer* pPlayer = CModeGame::GetPlayer();
	D3DXVECTOR3 vec = pPlayer->GetVelocity();
	D3DXVec3Normalize(&vec, &vec);
	m_pos = pPlayer->GetPos() +  vec * RETICLE_DISTANCE_FROM_PLAYER;

	D3DXVECTOR3 vecPR = m_pos - pPlayer->GetPos();
	float lenPR = D3DXVec3Length(&vecPR);

	CEnemy** pEnemy = CModeGame::GetEnemy();
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		if (pEnemy[i] == NULL) continue;

		D3DXVECTOR3 vecPE = pEnemy[i]->GetPos() - pPlayer->GetPos();
		D3DXVECTOR3 vecBuf;
		D3DXVec3Cross(&vecBuf, &vecPE, &vecPR);
		float Dist = D3DXVec3Length(&vecBuf) / lenPR;
		if (Dist < pEnemy[i]->GetSize().x * 0.5f && pEnemy[i]->GetRockon() == false)
		{
			D3DXVec3Normalize(&vecBuf, &vecPR);
			float Len = D3DXVec3Dot(&vecPE, &vecBuf);
			if (Len < lenPR && Len >= 0)
			{
				CRockon* pRockon = CRockon::Create(pEnemy[i]->GetPos(), D3DXVECTOR3(ROCKON_SIZE_X, ROCKON_SIZE_Y, 0.0f), m_rockonID, ROCKON001_TEXTURENAME);
				CModeGame::SetRockon(pRockon);
				CMediator* pMediator = CMediator::Create(pEnemy[i], pRockon);
				CModeGame::SetMediator(pMediator);
				pEnemy[i]->SetRockonID(m_rockonID);
				pEnemy[i]->SetRockon(true);
				m_rockonID++;
			}
		}
	}
}

//------------------------------------------------------------------------------
//�@�`�揈��
//------------------------------------------------------------------------------
void CReticle::Draw(void)
{
	CBillboard::Draw();
}

//------------------------------------------------------------------------------
//�@�쐬
//------------------------------------------------------------------------------
CReticle* CReticle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, char* filePass)
{
	CReticle* pEnemy = new CReticle(CScene::PRIORITY_BILLBOARD);

	pEnemy->SetPos(pos);
	pEnemy->SetSize(size);

	// �e�N�X�`���̃��[�h
	pEnemy->SetTexID(CTextureManager::LoadTexture(filePass, CTextureManager::TEXTYPE_NONE));
	pEnemy->Init();

	return pEnemy;
}

