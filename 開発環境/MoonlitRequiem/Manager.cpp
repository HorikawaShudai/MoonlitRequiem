//=========================================================================================================
//
//�}�l�[�W���̏���
//Author:�x�씋��
//
//=========================================================================================================
#include "Manager.h"
#include "Renderer.h"
#include "Input.h"
#include "Object.h"
#include "Sound.h"
#include "Title.h"
#include "Game.h"
#include "Result.h"
#include "fade.h"
#include "Tutorial.h"

//====================================================
//�ÓI�����o�ϐ��̏�����
//====================================================
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CTexture *CManager::m_pTexture = NULL;
CScene *CManager::m_pScene = NULL;
CFade *CManager::m_pFade = NULL;
LPDIRECT3DTEXTURE9 CManager::m_aTextureBg = NULL;
//====================================================
//�R���X�g���N�^
//====================================================
CManager::CManager()
{

}

//====================================================
//�f�X�g���N�^
//====================================================
CManager::~CManager()
{

}

//====================================================
//����������
//====================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	m_pRenderer = new CRenderer;
	m_pRenderer->Init(hWnd, TRUE);
	CSound::Init(hWnd);

	m_pInputKeyboard = new CInputKeyboard;
	m_pInputKeyboard->Init(hInstance, hWnd);

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = m_pRenderer->GetDevice();

	m_pTexture = new CTexture;
	m_pTexture->Load();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\BG000.jpg",
		&m_aTextureBg);

	m_pScene = CScene::Create(CScene::MODE_TITLE);
	m_pFade = CFade::Create();
	m_pFade->SetFade(CScene::MODE_TITLE, 0.01f);
	//SetMode(m_pScene->m_mode);
	//CObject3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f),CObject::TYPE_FIELD);
	//CEnemyCreate();
	/*CScore::Create();
	CScore::SetScore(0);*/
	//CSound::Play(CSound::SOUND_LABEL_BGM001);
	return S_OK;
}

//====================================================
//�I������
//====================================================
void CManager::Uninit(void)
{
	//���ׂẴI�u�W�F�N�g��j��
	CObject::ReleaseAll();
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		//delete m_pRenderer;
		m_pRenderer = NULL;
	}

	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();
		//delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	if (m_aTextureBg != NULL)
	{
		m_aTextureBg->Release();
		m_aTextureBg = NULL;
		delete m_aTextureBg;

	}
	if (m_pFade != NULL)
	{
		m_pFade->Uninit();
		m_pFade = NULL;
		delete m_pFade;

	}
	CSound::StopSound();
	CSound::Uninit();
	if (m_pTexture != NULL)
	{
		m_pTexture->Unload();
		m_pTexture = NULL;
		delete m_pTexture;
	}

	if (m_pScene != NULL)
	{
		m_pScene->Uninit();
		m_pScene = NULL;
		delete m_pScene;

	}
}

//====================================================
//�X�V����
//====================================================
void CManager::Update(void)
{
	m_pRenderer->Update();
	m_pFade->Update();
	m_pInputKeyboard->Update();
	m_pScene->Update();
}

//====================================================
//�`�揈��
//====================================================
void CManager::Draw(void)
{
	m_pRenderer->Draw();
	m_pFade->Draw();
	m_pScene->Draw();
}

//====================================================
//�����_���[�̎擾����
//====================================================
CRenderer *CManager::GetRenderer(void)
{
	return m_pRenderer;
}

//====================================================
//�����_���[�̎擾����
//====================================================
CInputKeyboard *CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

CTexture *CManager::GetpTexture(void)
{
	return m_pTexture;
}
CFade *CManager::GetpFade(void)
{
	return m_pFade;
}



//void CManager::CEnemyCreate(void)
//{
//	for (int nCnt = 0; nCnt < 50; nCnt++)
//	{
//		if (m_pEnemy3D[nCnt] == NULL)
//		{
//			m_pEnemy3D[nCnt] = CEnemy3D::Create(nCnt);
//				break;
//
//		}
//	}
//}

void CManager::SetMode(CScene::MODE mode)
{
	m_pScene->Uninit();

	m_pScene->m_mode = mode;
	switch (m_pScene->m_mode)
	{
	case CScene::MODE_GAME:
		CGame::Init();
		break;
	case CScene::MODE_TITLE:
		CTitle::Init();
		break;
	case CScene::MODE_TUTORIAL:
		CTutorial::Init();
		break;
	case CScene::MODE_CLEAR:
		CResult::Init();
		break;
	case CScene::MODE_END:
		CResult::Init();
		break;
	}
}
CScene::MODE CManager::GetMode(void)
{
	return m_pScene->m_mode;
}


//====================================================
//�R���X�g���N�^
//====================================================
CScene::CScene()
{
}

//====================================================
//�f�X�g���N�^
//====================================================
CScene::~CScene()
{

}
HRESULT CScene::Init(void)
{
	return S_OK;
}
void CScene::Uninit(void)
{



	switch (m_mode)
	{
	case CScene::MODE_GAME:
		CGame::Uninit();
		break;
	case CScene::MODE_TITLE:
		CTitle::Uninit();

		break;
	case CScene::MODE_TUTORIAL:
		CTutorial::Uninit();
		break;
	case CScene::MODE_CLEAR:
		CResult::Uninit();
		break;
	case CScene::MODE_END:
		CResult::Uninit();
		break;
	}
}
void CScene::Update(void)
{
	switch (m_mode)
	{
	case CScene::MODE_GAME:
		CGame::Update();
		break;
	case CScene::MODE_TITLE:
		CTitle::Update();

		break;
	case CScene::MODE_TUTORIAL:
		CTutorial::Update();
		break;
	case CScene::MODE_CLEAR:
		CResult::Update();
		break;
	case CScene::MODE_END:
		CResult::Update();
		break;
	}
}
void CScene::Draw(void)
{
	switch (m_mode)
	{
	case CScene::MODE_GAME:
		CGame::Draw();
		break;
	case CScene::MODE_TITLE:
		CTitle::Draw();
		break;
	case CScene::MODE_TUTORIAL:
		CTutorial::Draw();
		break;
	case CScene::MODE_CLEAR:
		CResult::Draw();
		break;
	case CScene::MODE_END:
		CResult::Draw();
		break;
	}
}

CScene *CScene::Create(CScene::MODE mode)
{
	CScene *pObject = NULL;

	pObject = new CScene;
	pObject->Init();

	return pObject;

}
D3DXVECTOR3 CScene::GetPos(void)
{
	D3DXVECTOR3 Nullpos;
	return Nullpos;

}



