//=========================================================================================================
//
//2DêÍópÇÃÉ|ÉäÉSÉìÇÃèàóù
//Author:ñxêÏîãëÂ
//
//=========================================================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
#include "Object2D.h"

#define BULLET_HEIGHT	(25.0f)	//íeÇÃâ°ïù
#define BULLET_WIDTH	(10.0f)	//íeÇÃècïù

class CBullet : public CObject2D
{
public:
	CBullet();
	~CBullet();

	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_BOW,
		TYPE_KNIFE,
		TYPE_MAX
	}BULLET_TYPE;
	typedef enum
	{
		BULLET_NONE = 0,
		BULLET_MOVE,
		BULLET_MAX
	}BULLET_MODE;

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, BULLET_TYPE type,int rot);

protected:
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	static D3DXVECTOR3 m_Createmove;
	static BULLET_TYPE m_Createtype;
	static D3DXVECTOR3 m_Createpos;
	static int m_CreateRot;
	D3DXVECTOR3 m_move;
	BULLET_TYPE m_type;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_posOld;
	D3DXVECTOR3 m_posWorld;
	D3DXVECTOR3 m_posWorldOld;
	int m_rot;
	BULLET_MODE m_mode;
};

#endif#pragma once
