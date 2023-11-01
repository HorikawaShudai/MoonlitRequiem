//===========================================================
//
//É^ÉCÉgÉãâÊñ èàóù
//Author:ñxêÏîãëÂ
//
//===========================================================

#include "Tutorial.h"
#include "input.h"
#include "Manager.h"
#include "fade.h"
#include "sound.h"

CTutorial::CTutorial()
{

}
CTutorial::~CTutorial()
{

}

HRESULT CTutorial::Init(void)
{
	CSound::Play(CSound::SOUND_LABEL_BGM002);

	CObject2D::Create(TYPE_BG, 0);

	return S_OK;
}
void CTutorial::Uninit(void)
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
void CTutorial::Update(void)
{
	CInputKeyboard *pKeyboard = CManager::GetInstance()->GetInputKeyboard();

	CFade *pFade = CManager::GetInstance()->GetpFade();

	CFade::FADE StateFade;
	StateFade = pFade->GetFade();
	if (pKeyboard->GetTrigger(DIK_RETURN) == true && StateFade == CFade::FADE_NONE)
	{

		pFade->SetFade(CScene::MODE_GAME, 0.001f);
	}
}
void CTutorial::Draw(void)
{

}