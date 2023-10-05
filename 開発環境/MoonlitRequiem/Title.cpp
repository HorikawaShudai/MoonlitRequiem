//===========================================================
//
//ƒ^ƒCƒgƒ‹‰æ–Êˆ—
//Author:–xì”‹‘å
//
//===========================================================

#include "Title.h"
#include "input.h"
#include "Manager.h"
#include "Object2D.h"
#include "fade.h"
#include "sound.h"

CTitle::CTitle()
{

}
CTitle::~CTitle()
{

}

HRESULT CTitle::Init(void)
{
	CObject2D::Create(TYPE_BG,0);
	CSound::Play(CSound::SOUND_LABEL_BGM000);

	return S_OK;
}
void CTitle::Uninit(void)
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
				if (type != CObject::TYPE_SCENE)
				{
					pObj->Release();
				}

			}
		}
	}
	CSound::StopSound();
}
void CTitle::Update(void)
{
	CInputKeyboard *pKeyboard = CManager::GetInputKeyboard();

	CFade *pFade = CManager::GetpFade();

	CFade::FADE StateFade;
	StateFade = pFade->GetFade();
	if (pKeyboard->GetTrigger(DIK_RETURN) == true && StateFade == CFade::FADE_NONE)
	{

		pFade->SetFade(CScene::MODE_GAME, 0.001f);
	}
}
void CTitle::Draw(void)
{

}