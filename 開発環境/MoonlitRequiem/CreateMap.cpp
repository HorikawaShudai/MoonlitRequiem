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
CCsvMap::TELEPORT CCsvMap::m_TpData[MAX_TP];
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

		char line[10048];
		while (fgets(line, sizeof(line), pFile) != NULL)
		{
			char *token = strtok(line, ",");
			m_MapData.nHeight = 0;
			while (token != NULL)
			{
				if (m_MapData.nHeight >= 300)
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
			case 0:
				break;
			case 1:
				m_TpData[0].NextNum = 1;
				m_TpData[0].TpPos = D3DXVECTOR3(BLOCK_HEIGHT * 2 * nCntH, BLOCK_WIDTH * 2 * nWCnt, 0.0f);
				m_TpData[0].TpVec = TP_RIGHT;
				break;
			case 2:
				m_TpData[1].NextNum = 0;
				m_TpData[1].TpPos = D3DXVECTOR3(BLOCK_HEIGHT * 2 * nCntH, BLOCK_WIDTH * 2 * nWCnt, 0.0f);
				m_TpData[1].TpVec = TP_LEFT;

			case 3:
				m_TpData[2].NextNum = 3;
				m_TpData[2].TpPos = D3DXVECTOR3(BLOCK_HEIGHT * 2 * nCntH, BLOCK_WIDTH * 2 * nWCnt, 0.0f);
				m_TpData[2].TpVec = TP_RIGHT;

				break;
			case 4:
				m_TpData[3].NextNum = 2;
				m_TpData[3].TpPos = D3DXVECTOR3(BLOCK_HEIGHT * 2 * nCntH, BLOCK_WIDTH * 2 * nWCnt, 0.0f);
				m_TpData[3].TpVec = TP_LEFT;

				break;
			case 11:
				CBlock::Create(D3DXVECTOR3(BLOCK_HEIGHT*2 *nCntH, BLOCK_WIDTH*2 *nWCnt, 0.0f));
				break;
			}
		}
	}
}

D3DXVECTOR3 CCsvMap::CollisionTp(D3DXVECTOR3 Pos, D3DXVECTOR3 Worldpos)
{
	for (int Cnt = 0; Cnt < MAX_TP; Cnt++)
	{
		if (Pos.x - Worldpos.x > m_TpData[Cnt].TpPos.x - TP_WHIGHT && Pos.x - Worldpos.x < m_TpData[Cnt].TpPos.x + TP_WHIGHT && Pos.y- Worldpos.y > m_TpData[Cnt].TpPos.y - TP_HEIGHT&& Pos.y- Worldpos.y < m_TpData[Cnt].TpPos.y + 20.0f)
		{
			return  GetNextTp(m_TpData[Cnt].NextNum);
		}

	}
	return Pos;
}

CCsvMap::TPVEC CCsvMap::GetType(D3DXVECTOR3 TpPos)
{
	for (int Cnt = 0; Cnt < MAX_TP; Cnt++)
	{
		D3DXVECTOR3 KeepPos = GetNextTp(m_TpData[Cnt].NextNum);
		if (KeepPos == TpPos)
		{
			return m_TpData[Cnt].TpVec;
		}

	}
	return TP_NONE;
}