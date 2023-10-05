//=============================================================
//
//ƒŠƒUƒ‹ƒg
//Autor:–xì”‹‘å
//
//=============================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"
#include "Object.h"

class CTutorial :public CObject
{
public:
	CTutorial();
	~CTutorial();

	static HRESULT Init(void);
	static void Uninit(void);
	static void Update(void);
	static void Draw(void);
private:

};
#endif