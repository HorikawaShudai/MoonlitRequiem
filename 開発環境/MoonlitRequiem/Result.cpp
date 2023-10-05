//===========================================================
//
//ƒ^ƒCƒgƒ‹‰æ–Êˆ—
//Author:–xì”‹‘å
//
//===========================================================

#include "Result.h"
#include "input.h"
#include "Manager.h"
#include "fade.h"

CResult::CResult()
{

}
CResult::~CResult()
{

}

HRESULT CResult::Init(void)
{
	CObject2D::Create(TYPE_BG,0);

	return S_OK;
}
void CResult::Uninit(void)
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
void CResult::Update(void)
{
	CInputKeyboard *pKeyboard = CManager::GetInputKeyboard();

	CFade *pFade = CManager::GetpFade();

	CFade::FADE StateFade;
	StateFade = pFade->GetFade();
	if (pKeyboard->GetTrigger(DIK_RETURN) == true && StateFade == CFade::FADE_NONE)
	{

		pFade->SetFade(CScene::MODE_TITLE, 0.001f);
	}
}
void CResult::Draw(void)
{

}