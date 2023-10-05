//=============================================================
//
//ƒQ[ƒ€ƒ‚[ƒh
//Autor:–xì”‹‘å
//
//=============================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"
#include "Object.h"

class CGame :public CObject
{
public:
	CGame();
	~CGame();

	static HRESULT Init(void);
	static void Uninit(void);
	static void Update(void);
	static void Draw(void);
	static void SetPouse(bool PouseNext);
	static bool GetPouse(void) { return bPouse; };
private:
	static bool bPouse;
};
#endif