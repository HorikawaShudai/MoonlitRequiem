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
		BULLET_PLAYER,
		BULLET_ENEMY,
		BULLET_MAX
	}BULLET_OBJ;

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 mrot, BULLET_TYPE type,int rot, BULLET_OBJ Obj);

protected:
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	static D3DXVECTOR3 m_Createmove;
	static BULLET_TYPE m_Createtype;
	static D3DXVECTOR3 m_Createpos;
	static D3DXVECTOR3 m_Createrot;
	static BULLET_OBJ m_Createobj;
	static int m_CreateRot;
	D3DXVECTOR3 m_move;
	BULLET_TYPE m_type;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_posOld;
	D3DXVECTOR3 m_posWorld;
	D3DXVECTOR3 m_posWorldOld;
	D3DXVECTOR3 m_rot;
	int m_nrot;
	BULLET_OBJ m_Obj;
};

#endif#pragma once
