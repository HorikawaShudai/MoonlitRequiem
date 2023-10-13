//=========================================================================================================
//
//2DêÍópÇÃÉ|ÉäÉSÉìÇÃèàóù
//Author:ñxêÏîãëÂ
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
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void PlayerContoroll(void);
	void PlayerTexture(void);
	void ScloolWorld(void);
	static  D3DXVECTOR3 GetWorld(void);
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_posOld;

private:
	D3DXVECTOR3 m_move;
	int m_nCntAnim;
	int m_nCntPattern;
	int PlayerRot;
	int m_JumpCnt;
	bool m_bJump;
	static LPDIRECT3DTEXTURE9 m_pTexture;
	PLAYER_TYPE m_Type;
	static D3DXVECTOR3 m_WorldPos;
};

#endif