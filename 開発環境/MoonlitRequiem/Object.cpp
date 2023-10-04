//=========================================================================================================
//
//�|���S���̋��L����
//Author:�x�씋��
//
//=========================================================================================================
#include "Object.h"
#include "Renderer.h"
//#include "Camera.h"
#include "Manager.h"

CObject  *CObject:: m_apObject[NUM_PRIORITY][NUM_POLYGON] = {};
int CObject :: m_nNumAll = 0;

//====================================================
//�R���X�g���N�^
//====================================================
CObject::CObject(int nPriority)
{
	m_nPriority = nPriority;
	for (int nCntObject = 0; nCntObject < NUM_POLYGON; nCntObject++)
	{
		if (m_apObject[m_nPriority][nCntObject] == NULL)
		{
			m_apObject[m_nPriority][nCntObject] = this;
			m_nID = nCntObject;
			m_nNumAll++;
			break;
		}
	}
}

//====================================================
//�f�X�g���N�^
//====================================================
CObject::~CObject()
{

}

//====================================================
//���ׂẴI�u�W�F�N�g�̔j��
//====================================================
void CObject::ReleaseAll(void)
{
	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < NUM_POLYGON; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != NULL)
			{
				m_apObject[nCntPriority][nCntObject]->Release();
			}
		}
	}
}

//====================================================
//���ׂẴI�u�W�F�N�g�̍X�V����
//====================================================
void CObject::UpdateAll(void)
{

	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < NUM_POLYGON; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != NULL)
			{
				m_apObject[nCntPriority][nCntObject]->Update();
			}
		}
	}
}

//====================================================
//���ׂẴI�u�W�F�N�g�̕`�揈��
//====================================================
void CObject::DrawAll(void)
{
	//CCamera *pCamera = CManager::GetCamera();
	//pCamera->SetCamera();
	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < NUM_POLYGON; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != NULL)
			{
				m_apObject[nCntPriority][nCntObject]->Draw();
			}
		}
	}
}

//====================================================
//�I�u�W�F�N�g(�������g)�̔j��
//====================================================
void CObject::Release(void)
{
	int nVtx = m_apObject[m_nPriority][m_nID]->m_nID;
	int nPriority = m_apObject[m_nPriority][m_nID]->m_nPriority;
		if (m_apObject[nVtx] != NULL)
		{
			m_apObject[nPriority][nVtx]->Uninit();

			delete m_apObject[nPriority][nVtx];
			m_apObject[nPriority][nVtx] = NULL;
			m_nNumAll--;
		}
}

void CObject::Reset(void)
{
	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < NUM_POLYGON; nCntObject++)
		{
			
			if (m_apObject[nCntPriority][nCntObject] != NULL)
			{
				if (m_apObject[nCntPriority][nCntObject]->m_type != TYPE_PLAYER && m_apObject[nCntPriority][nCntObject]->m_type != TYPE_NUMBER && m_apObject[nCntPriority][nCntObject]->m_type != TYPE_BGS && m_apObject[nCntPriority][nCntObject]->m_type != TYPE_BG)
				{
					m_apObject[nCntPriority][nCntObject]->Release();

				}
			}
		}
	}
}