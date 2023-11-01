//============================================================================
//
//CSVファイルのデータ読み込みと出力」
//Author:堀川萩大
//
//============================================================================
#include "CreateMap.h"
#include "Block.h"
#include "Player.h"
#include "Enemy.h"
#include "Boss.h"
#include "Game.h"
#include <stdio.h>
#include <cstdlib>
#include "sound.h"

#define CSVMAP "data\\MAP\\Map.csv"


CCsvMap::DATA CCsvMap::m_MapData;
D3DXVECTOR3 CCsvMap::m_BossTrigger;
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
				m_BossTrigger = D3DXVECTOR3(BLOCK_HEIGHT * 2 * nCntH, BLOCK_WIDTH * 2 * nWCnt, 0.0f);
				break;
			case 21:
				CEnemy::Create(D3DXVECTOR3(BLOCK_HEIGHT * 2 * nCntH, BLOCK_WIDTH * 2 * nWCnt + 15.0f, 0.0f));
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

bool CCsvMap::BossSpown(D3DXVECTOR3 pPos, D3DXVECTOR3 pWorldpos)
{
	if (pPos.x - pWorldpos.x > m_BossTrigger.x - TP_WHIGHT && pPos.x - pWorldpos.x <m_BossTrigger.x + TP_WHIGHT && pPos.y - pWorldpos.y > m_BossTrigger.y - TP_HEIGHT&& pPos.y - pWorldpos.y < m_BossTrigger.y + 20.0f)
	{
		if (CGame::GetPhase() == CGame::PHASE_NORMAL)
		{
			CBoss::Create(m_BossTrigger);
			CGame::SetPhase(CGame::PHASE_BOSS);
			CSound::StopSound();
			CSound::Play(CSound::SOUND_LABEL_BGM003);
		}
		return  true;
	}
	return false;
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