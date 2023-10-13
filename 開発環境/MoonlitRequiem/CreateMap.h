//=============================================================
//
//csvmapÌ
//Autor:xìå
//
//=============================================================
#ifndef _CSVMAP_H_
#define _CSVMAP_H_
#include "main.h"

//}Nè`
#define MAX_HEIGHT (100)
#define MAX_WHIGHT (100)

class CCsvMap
{
public:
	//ñ^Ìf[^é¾
	typedef enum
	{
		MAP_NONE = 0,	//óC
		MAP_FLORE,		//°
		MAP_MAX,
	}MAP_KIND; 
	//vg^Cvé¾
	static void LoadMap(void);
	static void CreateMap(void);
private:
	typedef struct
	{
		int mapData[MAX_WHIGHT][MAX_HEIGHT];
		int nHeight;
		int nWhight;
	}DATA;
	static DATA m_MapData;
};
#endif