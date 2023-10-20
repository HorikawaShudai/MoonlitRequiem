//=========================================================================================================
//
//2DêÍópÇÃÉ|ÉäÉSÉìÇÃèàóù
//Author:ñxêÏîãëÂ
//
//=========================================================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "Object2D.h"

#define ENEMY_HEIGHT (70.0f)
#define ENEMY_WIDTH	 (40.0f)

class CEnemy : public CObject2D
{
public:
	CEnemy();
	~CEnemy();
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_WALK,
		TYPE_JUMP,
		TYPE_ATTACK,
		TYPE_ROLL
	}ENEMY_TYPE;
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void Create(D3DXVECTOR3 pos);
	void EnemyContoroll(void);
	void EnemyTexture(void);
	static bool ColisionEnemy(D3DXVECTOR3 pos);
	static D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_posOld;

private:
	D3DXVECTOR3 m_posWorld;
	D3DXVECTOR3 m_move;
	int m_nCntAnim;
	int m_nCntPattern;
	int EnemyRot;
	int m_JumpCnt;
	bool m_bJump;
	static LPDIRECT3DTEXTURE9 m_pTexture;
	ENEMY_TYPE m_Type;
};

#endif