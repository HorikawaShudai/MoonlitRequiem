//=========================================================================================================
//
//2D専用のブロックの処理
//Author:堀川萩大
//
//=========================================================================================================
#include "Block.h"
#include "Object2D.h"
#include "Manager.h"
#include "Renderer.h"
#include "Player.h"



D3DXVECTOR3 CBlock::m_pos;
LPDIRECT3DTEXTURE9 CBlock::m_pTexture;
//====================================================
//コンストラクタ
//====================================================
CBlock::CBlock()
{

	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

}
//====================================================
//デストラクタ
//====================================================
CBlock::~CBlock()
{

}


//====================================================
//ブロックの初期化処理
//====================================================
HRESULT CBlock::Init(void)
{

	CObject2D::Init();
	m_move = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	SetPos(m_pos, BLOCK_HEIGHT, BLOCK_WIDTH);
	m_posWorld = m_pos;

	CTexture *pTexture = CManager::GetInstance()->GetpTexture();
	m_TexId = pTexture->Regist("data\\TEXTURE\\tuti001.jpg");
	//BindTexture(m_pTexture);
	SetType(TYPE_BLOCK);

	return S_OK;
}

//====================================================
//ブロックの終了処理
//====================================================
void CBlock::Uninit(void)
{
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//====================================================
//ブロックの更新処理
//====================================================
void CBlock::Update(void)
{
	D3DXVECTOR3 WorldPos = CPlayer::GetWorld();
	m_pos = m_posWorld+ WorldPos;
	SetPos(m_pos, BLOCK_HEIGHT, BLOCK_WIDTH);
}

//====================================================
//ブロックの描画処理
//====================================================
void CBlock::Draw(void)
{
	CObject2D::Draw();
}

//====================================================
//ブロックの生成処理
//====================================================
void CBlock::Create(D3DXVECTOR3 pos)
{
	m_pos = pos;
	CObject2D::Create(TYPE_BLOCK,1);

}

//====================================================
//縦の当たり判定
//====================================================
bool CBlock::CollisionBlock(D3DXVECTOR3 oldpos, D3DXVECTOR3 pos,float Height,float Width)
{
	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		for (int nCntObj = 0; nCntObj < NUM_POLYGON; nCntObj++)
		{
			CObject *pObj;
			pObj = GetObject(nCntPri, nCntObj);
			if (pObj != NULL)
			{
				TYPE type;
				type = pObj->GetType();
				if (type == TYPE_BLOCK)
				{
					D3DXVECTOR3 p_pos = pObj->GetPos();

					//着地
					if (p_pos.y - BLOCK_HEIGHT <= pos.y && pos.y <= p_pos.y && p_pos.x - BLOCK_WIDTH <= pos.x && pos.x <= p_pos.x + BLOCK_WIDTH) 
					{
						return TRUE;
					}
					if (p_pos.y - BLOCK_HEIGHT <= pos.y && pos.y <= p_pos.y && p_pos.x - BLOCK_WIDTH <= pos.x- Width && pos.x- Width <= p_pos.x + BLOCK_WIDTH)
					{
						return TRUE;
					}
					if (p_pos.y - BLOCK_HEIGHT <= pos.y && pos.y <= p_pos.y && p_pos.x - BLOCK_WIDTH <= pos.x+ Width && pos.x+ Width <= p_pos.x + BLOCK_WIDTH)
					{
						return TRUE;
					}
					//頭ぶつける
					else if ((p_pos.y + BLOCK_HEIGHT) > pos.y- Height && (p_pos.x - BLOCK_WIDTH) < pos.x && (p_pos.x + BLOCK_WIDTH) > pos.x && (p_pos.y + BLOCK_HEIGHT) < oldpos.y - Height)
					{
						return TRUE;
					}
					//頭ぶつける
					else if ((p_pos.y + BLOCK_HEIGHT) > pos.y - Height && (p_pos.x - BLOCK_WIDTH) < pos.x - Width && (p_pos.x + BLOCK_WIDTH) > pos.x - Width && (p_pos.y + BLOCK_HEIGHT) < oldpos.y - Height)
					{
						return TRUE;
					}
					//頭ぶつける
					else if ((p_pos.y + BLOCK_HEIGHT) > pos.y - Height && (p_pos.x - BLOCK_WIDTH) < pos.x + Width && (p_pos.x + BLOCK_WIDTH) > pos.x + Width && (p_pos.y + BLOCK_HEIGHT) < oldpos.y - Height)
					{
						return TRUE;
					}
					//if (p_pos.y + BLOCK_HEIGHT >= pos.y - Height && p_pos.y  BLOCK_HEIGHT >= pos.y - Height &&
					//	p_pos.x - BLOCK_WIDTH <= pos.x && pos.x <= p_pos.x + BLOCK_WIDTH) // ブロックの横幅内にいることを確認
					//{
					//	return TRUE; // 頭をぶつけた
					//}
					
				}
			}
		}
	}
	return FALSE;

}

//====================================================
//横の当たり判定
//====================================================
bool CBlock::HCollisionBlock(D3DXVECTOR3 oldpos, D3DXVECTOR3 pos, float Height, float Width)
{
	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		for (int nCntObj = 0; nCntObj < NUM_POLYGON; nCntObj++)
		{
			CObject *pObj;
			pObj = GetObject(nCntPri, nCntObj);
			if (pObj != NULL)
			{
				TYPE type;
				type = pObj->GetType();
				if (type == TYPE_BLOCK)
				{
					D3DXVECTOR3 p_pos = pObj->GetPos();
					if ((p_pos.y - BLOCK_WIDTH) < pos.y && (p_pos.y + BLOCK_WIDTH) >= pos.y && (p_pos.x + BLOCK_HEIGHT) >= pos.x - Width && (p_pos.x + BLOCK_HEIGHT) <= oldpos.x- Width)
					{
						return TRUE;
					}
					else if ((p_pos.y - BLOCK_WIDTH) < pos.y && (p_pos.y + BLOCK_WIDTH) >= pos.y && (p_pos.x - BLOCK_HEIGHT) <= pos.x + Width &&  (p_pos.x - BLOCK_HEIGHT) >= oldpos.x + Width)
					{
						return TRUE;
					}
					else if ((p_pos.y - BLOCK_WIDTH) < pos.y- Height && (p_pos.y + BLOCK_WIDTH) >= pos.y- Height && (p_pos.x + BLOCK_HEIGHT) >= pos.x - Width && (p_pos.x + BLOCK_HEIGHT) <= oldpos.x - Width)
					{
						return TRUE;
					}
					else if ((p_pos.y - BLOCK_WIDTH) < pos.y - Height && (p_pos.y + BLOCK_WIDTH) >= pos.y - Height && (p_pos.x - BLOCK_HEIGHT) <= pos.x + Width && (p_pos.x - BLOCK_HEIGHT) >= oldpos.x + Width)
					{
						return TRUE;
					}
					else if ((p_pos.y - BLOCK_WIDTH) < (pos.y - (Height / 3)) && (p_pos.y + BLOCK_WIDTH) >= (pos.y - (Height / 3)) && (p_pos.x + BLOCK_HEIGHT) >= pos.x - Width && (p_pos.x + BLOCK_HEIGHT) <= oldpos.x - Width)
					{
						return TRUE;
					}
					else if ((p_pos.y - BLOCK_WIDTH) < (pos.y - (Height / 3)) && (p_pos.y + BLOCK_WIDTH) >= (pos.y - (Height / 3)) && (p_pos.x - BLOCK_HEIGHT) <= pos.x + Width && (p_pos.x - BLOCK_HEIGHT) >= oldpos.x + Width)
					{
						return TRUE;
					}
					else if ((p_pos.y - BLOCK_WIDTH) < (pos.y - (Height / 2)) && (p_pos.y + BLOCK_WIDTH) >= (pos.y - (Height / 2)) && (p_pos.x + BLOCK_HEIGHT) >= pos.x - Width && (p_pos.x + BLOCK_HEIGHT) <= oldpos.x - Width)
					{
						return TRUE;
					}
					else if ((p_pos.y - BLOCK_WIDTH) < (pos.y - (Height / 2)) && (p_pos.y + BLOCK_WIDTH) >= (pos.y - (Height / 2)) && (p_pos.x - BLOCK_HEIGHT) <= pos.x + Width && (p_pos.x - BLOCK_HEIGHT) >= oldpos.x + Width)
					{
						return TRUE;
					}
					else if ((p_pos.y - BLOCK_WIDTH) < (pos.y - (Height / 4)) && (p_pos.y + BLOCK_WIDTH) >= (pos.y - (Height / 4)) && (p_pos.x + BLOCK_HEIGHT) >= pos.x - Width && (p_pos.x + BLOCK_HEIGHT) <= oldpos.x - Width)
					{
						return TRUE;
					}
					else if ((p_pos.y - BLOCK_WIDTH) < (pos.y - (Height / 4)) && (p_pos.y + BLOCK_WIDTH) >= (pos.y - (Height / 4)) && (p_pos.x - BLOCK_HEIGHT) <= pos.x + Width && (p_pos.x - BLOCK_HEIGHT) >= oldpos.x + Width)
					{
						return TRUE;
					}

				}
			}
		}
	}
	return FALSE;

}

