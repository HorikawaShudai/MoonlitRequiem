//============================================================================
//
//CSVファイルのデータ読み込みと出力」
//Author:堀川萩大
//
//============================================================================
#include "CreateMap.h"
#include "Block.h"
#include "Player.h"
#include <stdio.h>
#include <cstdlib>

#define CSVMAP "data\\MAP\\Map.csv"


CCsvMap::DATA CCsvMap::m_MapData;

//============================================================================
//読み込み処理
//============================================================================
void CCsvMap::LoadMap(void)
{
	FILE *pFile;

	pFile = fopen(CSVMAP, "r");

	if (pFile != NULL)
	{
		m_MapData.nWhight = 0;

		char line[1024];
		while (fgets(line, sizeof(line), pFile) != NULL)
		{
			char *token = strtok(line, ",");
			m_MapData.nHeight = 0;
			while (token != NULL)
			{
				if (m_MapData.nHeight >= 100)
				{
					break;
				}
				m_MapData.mapData[m_MapData.nWhight][m_MapData.nHeight] = atoi(token);
				m_MapData.nHeight++;
				token = strtok(NULL, ",");

			}
			m_MapData.nWhight++;
		}
	}
	else
	{

	}
	CreateMap();

}

void CCsvMap::CreateMap(void)
{
	for (int nWCnt = 0; nWCnt < MAX_WHIGHT; nWCnt++)
	{
		for (int nCntH = 0; nCntH < MAX_HEIGHT; nCntH++)
		{

			switch (m_MapData.mapData[nWCnt][nCntH])
			{
			case MAP_NONE:
				break;
			case MAP_FLORE:
				CBlock::Create(D3DXVECTOR3(BLOCK_HEIGHT*2 *nCntH, BLOCK_WIDTH*2 *nWCnt, 0.0f));
				break;
			}
		}
	}
}