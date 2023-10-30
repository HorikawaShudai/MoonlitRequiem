//=========================================================================================================
//
//2DêÍópÇÃÉ|ÉäÉSÉìÇÃèàóù
//Author:ñxêÏîãëÂ
//
//=========================================================================================================
#ifndef _BOSS_H_
#define _BOSS_H_

#include "main.h"
#include "Object2D.h"

#define BOSS_HEIGHT (350.0f)
#define BOSS_WIDTH	 (300.0f)

class CBoss : public CObject2D
{
public:
	CBoss(int nPriority = 2);
	~CBoss();
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_INVISIBLE,
		TYPE_SPAWN,
		TYPE_JUMP,
		TYPE_ATTACK,
		TYPE_ROLL
	}BOSS_TYPE;
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void Create(D3DXVECTOR3 pos);
	void BossContoroll(void);
	static bool ColisionBoss(D3DXVECTOR3 pos);
	static void DamageBoss(int nDamage);
	static D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_posOld;
	static int GetLife(void) { return m_Life; }

private:
	D3DXVECTOR3 m_posWorld;
	D3DXVECTOR3 m_move;
	D3DXCOLOR m_col;
	int m_nCntAnim;
	int m_nCntPattern;
	int BossRot;
	int m_JumpCnt;
	int AttacKCount;
	static int m_Life;
	bool m_bJump;
	static LPDIRECT3DTEXTURE9 m_pTexture;
	static BOSS_TYPE m_Type;
};

#endif