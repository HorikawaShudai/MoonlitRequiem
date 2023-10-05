//=============================================================
//
//ƒŠƒUƒ‹ƒg
//Autor:–xì”‹‘å
//
//=============================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"
#include "Object.h"

class CResult :public CObject
{
public:
	CResult();
	~CResult();

	static HRESULT Init(void);
	static void Uninit(void);
	static void Update(void);
	static void Draw(void);
private:

};
#endif