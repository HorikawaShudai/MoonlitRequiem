//=========================================================================================================
//
//2Dê—p‚Ìƒ|ƒŠƒSƒ“‚Ìˆ—
//Author:–xì”‹‘å
//
//=========================================================================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "main.h"
#include "Object2D.h"

#define BLOCK_HEIGHT	(20.0f)	//’e‚Ì‰¡•
#define BLOCK_WIDTH		(20.0f)	//’e‚Ìc•

class CBlock : public CObject2D
{
public:
	CBlock();
	~CBlock();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void Create(D3DXVECTOR3 pos);
	static bool CollisionBlock(D3DXVECTOR3 oldpos, D3DXVECTOR3 pos, float Height, float Width);
	static bool HCollisionBlock(D3DXVECTOR3 oldpos, D3DXVECTOR3 pos,float Height, float Width);
protected:
	static D3DXVECTOR3 m_pos;
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_posWorld;
	int m_Life;
};

#endif#pragma once
