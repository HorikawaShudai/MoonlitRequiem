//=========================================================================================================
//
//2DêÍópÇÃÉ|ÉäÉSÉìÇÃèàóù
//Author:ñxêÏîãëÂ
//
//=========================================================================================================
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

#include "main.h"
#include "Object.h"
#include "Texture.h"



class CObject2D: public CObject
{
public:
	CObject2D(int nPriority = 3);
	~CObject2D();

	HRESULT Init(void) = 0;
	void Uninit(void);
	void Update(void)= 0;
	void Draw(void) = 0;

	D3DXVECTOR3 GetPos(void);

	void SetPos(D3DXVECTOR3 pos, float Height, float Width);
	void SetPlayerPos(D3DXVECTOR3 pos, float Height, float Width);
	void SetSize(float Height,float Width);
	void SetCol(D3DXCOLOR col);
	void SetRot(float rot);
	void SetAnim(int xCount, int xPuttern, int yCount, int yPuttern);
	void SetTexmove(D3DXVECTOR3 move) { m_moveTex = move; };

	static CObject2D *Create(TYPE type2D,int type);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
	
	void AutoScroll(float hMoveTex, float wMoveTex);
	D3DXVECTOR3 m_moveTex;
	LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;

protected:
private:
	D3DXVECTOR3 m_pos;
	int m_nNumObject2D;
	int m_nCntAnim;
	int m_nCntPattern;

};

#endif