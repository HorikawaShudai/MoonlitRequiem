//=============================================================
//
//ÉQÅ[ÉÄÉÇÅ[Éh
//Autor:ñxêÏîãëÂ
//
//=============================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"
#include "Object.h"
#include "Time.h"

class CGame :public CObject
{
public:
	CGame();
	~CGame();

	typedef enum
	{
		PHASE_NORMAL  =0,
		PHASE_BOSS,
		PHASE_MAX
	}PHASE;
	static HRESULT Init(void);
	static void Uninit(void);
	static void Update(void);
	static void Draw(void);
	static void SetPouse(bool PouseNext);
	static bool GetPouse(void) { return bPouse; };
	static void SetPhase(PHASE phase) { pPhase = phase; };
	static PHASE GetPhase(void) { return pPhase; };
private:
	static bool bPouse;
	static PHASE pPhase;
	//static CTime *TimeAttack;
};
#endif