//=========================================================================================================
//
//2D専用のポリゴンの処理
//Author:堀川萩大
//
//=========================================================================================================
#include "Boss.h"
#include "Object2D.h"
#include "Manager.h"
#include "Renderer.h"
#include "Input.h"
#include "Block.h"
#include "CreateMap.h"
#include "Player.h"
#include "fade.h"


#define BOSS_SPEED	(3.8f)
#define BOSS_JUMP (11.0f)
#define  GRAVITY (0.27665f)
#define COUNT_SPEED (15)
#define BOSS_MAXTEX (6)
#define BOSS_MAXJUMP (2)

LPDIRECT3DTEXTURE9 CBoss::m_pTexture = NULL;
D3DXVECTOR3 CBoss::m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
int CBoss::m_Life = 20;
//====================================================
//コンストラクタ
//====================================================
CBoss::CBoss(int nPriority) :CObject2D(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCntAnim = 0;
	m_nCntPattern = 0;
	BossRot = 0;
	m_pTexture = NULL;
	m_Type = TYPE_NONE;
	m_bJump = false;
	m_JumpCnt = 0;
}
//====================================================
//デストラクタ
//====================================================
CBoss::~CBoss()
{

}


//====================================================
//ポリゴンの初期化処理
//====================================================
HRESULT CBoss::Init(void)
{
	CObject2D::Init();
	SetAnim(0, 1, 0, 1);
	m_posWorld = m_pos;
	CTexture *pTexture = CManager::GetInstance()->GetpTexture();
	m_TexId = pTexture->Regist("data\\TEXTURE\\Boss.png");
	BindTexture(pTexture->GetAddress(m_TexId));
	SetType(TYPE_BOSS);

	return S_OK;
}

//====================================================
//ポリゴンの終了処理
//====================================================
void CBoss::Uninit(void)
{
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

}

//====================================================
//ポリゴンの更新処理
//====================================================
void CBoss::Update(void)
{
	m_posOld = GetPos();

	m_pos = GetPos();
	BossContoroll();

	m_move.y += GRAVITY;
	if (m_move.y >= GRAVITY * 24)
	{
		m_move.y = GRAVITY * 24;
	}

	if (m_move.y < -BOSS_JUMP)
	{
		m_move.y = -BOSS_JUMP;
	}

	m_pos += m_move;

	if (CBlock::CollisionBlock(m_posOld, m_pos, BOSS_HEIGHT, BOSS_WIDTH) == TRUE)
	{

		m_pos.y = m_posOld.y;
		SetPlayerPos(m_pos, BOSS_HEIGHT, BOSS_WIDTH);

		m_move.y = 0.0f;
		m_bJump = false;
		m_JumpCnt = 0;

	}

	if (CBlock::HCollisionBlock(m_posOld, m_pos, BOSS_HEIGHT, BOSS_WIDTH) == TRUE)
	{
		SetPlayerPos(m_pos, BOSS_HEIGHT, BOSS_WIDTH);

		m_pos.x = m_posOld.x;
		m_move.x = 0.0f;
	}


	D3DXVECTOR3 WorldPos = CPlayer::GetWorld();
	m_pos = m_posWorld + WorldPos;
	SetPlayerPos(m_pos, BOSS_HEIGHT, BOSS_WIDTH);

	//CItem::CollisionItem(m_pos, BOSS_HEIGHT, BOSS_WIDTH);
	m_move.x *= 0.06f;
	BossTexture();

}

//====================================================
//ポリゴンの描画処理
//====================================================
void CBoss::Draw(void)
{
	CObject2D::Draw();
}

//====================================================
//ブロックの生成処理
//====================================================
void CBoss::Create(D3DXVECTOR3 pos)
{
	m_pos = pos;
	CObject2D::Create(TYPE_BOSS, 1);

}

//====================================================
//プレイヤーの操作処理
//====================================================
void CBoss::BossContoroll(void)
{

}


void CBoss::BossTexture(void)
{
	//if (m_Type == TYPE_NONE)
	//{
	//	if (BossRot == 1)
	//	{
	//		SetAnim(BossRot, Boss_MAXTEX, 0, Boss_MAXTEX);

	//	}
	//	if (BossRot == 0)
	//	{
	//		SetAnim(BossRot, Boss_MAXTEX, 0, Boss_MAXTEX);

	//	}
	//}
	//if (m_Type == TYPE_WALK)
	//{
	//	m_nCntAnim++;
	//	if (m_nCntAnim % COUNT_SPEED == 0)
	//	{
	//		m_nCntPattern++;
	//		if (BossRot == 1)
	//		{
	//			SetAnim(m_nCntPattern % Boss_MAXTEX, Boss_MAXTEX, 2, Boss_MAXTEX);

	//		}
	//		if (BossRot == 0)
	//		{
	//			SetAnim(m_nCntPattern % Boss_MAXTEX, Boss_MAXTEX, 1, Boss_MAXTEX);

	//		}
	//	}
	//}
	//if (m_Type == TYPE_JUMP)
	//{
	//	if (m_posOld.y < m_pos.y)
	//	{//下に降りてる

	//		if (BossRot == 1)
	//		{//左
	//			SetAnim(5, Boss_MAXTEX, 0, Boss_MAXTEX);

	//		}
	//		if (BossRot == 0)
	//		{//右
	//			SetAnim(4, Boss_MAXTEX, 0, Boss_MAXTEX);

	//		}
	//	}
	//	else if (m_posOld.y > m_pos.y)
	//	{//上に上がっている時

	//		if (BossRot == 1)
	//		{//左
	//			SetAnim(3, Boss_MAXTEX, 0, Boss_MAXTEX);

	//		}
	//		if (BossRot == 0)
	//		{//右
	//			SetAnim(2, Boss_MAXTEX, 0, Boss_MAXTEX);

	//		}
	//	}
	//}
}

bool CBoss::ColisionBoss(D3DXVECTOR3 pos)
{

	if (m_pos.x - BOSS_HEIGHT < pos.x&& m_pos.y - BOSS_WIDTH < pos.y && m_pos.x + BOSS_HEIGHT> pos.x&& m_pos.y + BOSS_WIDTH > pos.y)
	{
		
		DamageBoss(1);
		return true;
	}
	return false;
}
void CBoss::DamageBoss(int nDamage)
{
	m_Life -= nDamage;
	if (m_Life <= 0)
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
					if (type == CObject::TYPE_BOSS)
					{
						pObj->Release();
						CFade *pFade = CManager::GetInstance()->GetpFade();

						CFade::FADE StateFade;
						StateFade = pFade->GetFade();
						if (StateFade == CFade::FADE_NONE)
						{

							pFade->SetFade(CScene::MODE_CLEAR, 0.001f);
						}
					}

				}
			}
		}
	}
}