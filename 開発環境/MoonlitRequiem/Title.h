//=============================================================
//
//ƒŠƒUƒ‹ƒg
//Autor:–xì”‹‘å
//
//=============================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"
#include "Object.h"

class CTitle :public CObject
{
public:
	CTitle();
	~CTitle();

	static HRESULT Init(void);
	static void Uninit(void);
	static void Update(void);
	static void Draw(void);
private:

};
#endif