//===========================================================
//
//�^�C�g����ʏ���
//Author:�x�씋��
//
//===========================================================

#include "Tutorial.h"
#include "input.h"
#include "Manager.h"
#include "fade.h"

CTutorial::CTutorial()
{

}
CTutorial::~CTutorial()
{

}

HRESULT CTutorial::Init(void)
{
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
}
void CTutorial::Update(void)
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
void CTutorial::Draw(void)
{

}