//=============================================================
//
//csvmapの処理
//Autor:堀川萩大
//
//=============================================================
#ifndef _CSVMAP_H_
#define _CSVMAP_H_
#include "main.h"

//マクロ定義
#define MAX_HEIGHT (100)
#define MAX_WHIGHT (100)

class CCsvMap
{
public:
	//列挙型のデータ宣言
	typedef enum
	{
		MAP_NONE = 0,	//空気
		MAP_FLORE,		//床
		MAP_MAX,
	}MAP_KIND; 
	//プロトタイプ宣言
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