//=========================================================================================================
//
//2Dê—p‚Ìƒ|ƒŠƒSƒ“‚Ìˆ—
//Author:–xì”‹‘å
//
//=========================================================================================================
#ifndef _BG_H_
#define _BG_H_

#include "main.h"
#include "Object2D.h"



class CBg : public CObject2D
{
public:
	CBg(int nPriority = 0);
	~CBg();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void AddMove(float Xmove, float Ymove) { m_texMove += D3DXVECTOR3(Xmove, Ymove, 0.0f); };
	D3DXVECTOR3 m_move;
	static D3DXVECTOR3 m_texMove;
private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_Texpos;
};

#endif