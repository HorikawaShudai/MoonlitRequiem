//===========================================================
//
//タイトル画面処理
//Author:堀川萩大
//
//===========================================================

#include "Game.h"
#include "input.h"
#include "Manager.h"
#include "fade.h"
#include "Manager.h"
#include "sound.h"
#include "Object2D.h"
#include "CreateMap.h"


//====================================================
//静的メンバ変数の初期化
//====================================================
bool CGame::bPouse =false;
CGame::PHASE CGame::pPhase  =PHASE_NORMAL;

CGame::CGame()
{

}
CGame::~CGame()
{

}

HRESULT CGame::Init(void)
{
	CSound::Play(CSound::SOUND_LABEL_BGM001);
	CObject2D::Create(CObject::TYPE_PLAYER, 1);
	CCsvMap::LoadMap();
	return S_OK;
}
void CGame::Uninit(void)
{
	CObject *pObj;

	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		for (int nCntObj = 0; nCntObj < NUM_POLYGON; nCntObj++)
		{
			pObj = CObject::GetObject(nCntPri, nCntObj);
			if (pObj != NULL)
			{
				CObject::TYPE type;
				type = pObj->GetType();
					pObj->Release();

			}
		}
	}
	CSound::StopSound();
}
void CGame::Update(void)
{
	CInputKeyboard *pKeyboard = CManager::GetInstance()->GetInputKeyboard();

	CFade *pFade = CManager::GetInstance()->GetpFade();

	CFade::FADE StateFade;
	StateFade = pFade->GetFade();
	//if (pKeyboard->GetTrigger(DIK_RETURN) == true && StateFade == CFade::FADE_NONE)
	//{

	//	pFade->SetFade(CScene::MODE_CLEAR, 0.001f);
	//}
}
void CGame::Draw(void)
{

}



void CGame::SetPouse(bool PouseNext)
{
	bPouse = PouseNext;
}