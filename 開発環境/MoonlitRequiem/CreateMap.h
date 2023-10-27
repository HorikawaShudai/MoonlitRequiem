//=============================================================
//
//csvmapÇÃèàóù
//Autor:ñxêÏîãëÂ
//
//=============================================================
#ifndef _CSVMAP_H_
#define _CSVMAP_H_
#include "main.h"

//É}ÉNÉçíËã`
#define MAX_HEIGHT (200)
#define MAX_WHIGHT (200)
#define TP_WHIGHT (20)
#define TP_HEIGHT (300)
#define MAX_TP (10)

class CCsvMap
{
public:
	typedef enum
	{
		TP_RIGHT = 0,
		TP_LEFT,
		TP_UP,
		TP_DOWN,
		TP_NONE
	}TPVEC;
	typedef struct
	{
		int NextNum;
		TPVEC TpVec;
		D3DXVECTOR3 TpPos;
		D3DXVECTOR3 NextTp;
	}TELEPORT;

	static void LoadMap(void);
	static void CreateMap(void);
	static D3DXVECTOR3 CollisionTp(D3DXVECTOR3 Pos, D3DXVECTOR3 Worldpos);
	static bool BossSpown(D3DXVECTOR3 pPos, D3DXVECTOR3 pWorldpos);
	static D3DXVECTOR3 GetNextTp(int NextNum) { return m_TpData[NextNum].TpPos; };
	static TPVEC GetType(D3DXVECTOR3 TpPos);
	
private:
	typedef struct
	{
		int mapData[MAX_WHIGHT][MAX_HEIGHT];
		int nHeight;
		int nWhight;
	}DATA;
	static TELEPORT m_TpData[MAX_TP];
	static DATA m_MapData;
	static D3DXVECTOR3 m_BossTrigger;
};
#endif