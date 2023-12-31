//=========================================================================================================
//
//2D��p�̃|���S���̏���
//Author:�x�씋��
//
//=========================================================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "Object2D.h"


class CPlayer : public CObject2D
{
public:
	CPlayer();
	~CPlayer();
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_WALK,
		TYPE_JUMP,
		TYPE_ATTACK,
		TYPE_ROLL
	}PLAYER_TYPE;
	typedef enum
	{
		STATE_NONE =0,
		STATE_DAMAGE,
		STATE_MAX
	}STATE;

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void PlayerContoroll(void);
	void PlayerTexture(void);
	void ScloolWorld(void);
	void SetScloolMove(bool CanMove);
	void StateControl(void);
	static bool Collision(D3DXVECTOR3 pos);
	static void Damage(int nDamage);
	static  D3DXVECTOR3 GetWorld(void);
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_posOld;
	static int GetLife(void) { return m_Life; };
	D3DXVECTOR3 getPos(void) { return m_pos; };
private:
	D3DXVECTOR3 m_move;
	int m_nCntAnim;
	int m_nCntPattern;
	int PlayerRot;
	int m_JumpCnt;
	int m_StateCnt;
	static int m_Life;
	static STATE m_State;
	bool m_bJump;
	bool m_ScloolMove;
	static LPDIRECT3DTEXTURE9 m_pTexture;
	PLAYER_TYPE m_Type;
	static D3DXVECTOR3 m_WorldPos;
};

#endif