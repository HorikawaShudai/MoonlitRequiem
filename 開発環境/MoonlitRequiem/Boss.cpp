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
#include "LifeGuage.h"
#include "Bullet.h"
#include "sound.h"

#define BOSS_SPEED	(3.8f)
#define BOSS_JUMP (11.0f)
#define  GRAVITY (0.27665f)
#define COUNT_SPEED (15)
#define BOSS_MAXTEX (6)
#define BOSS_MAXJUMP (2)

LPDIRECT3DTEXTURE9 CBoss::m_pTexture = NULL;
D3DXVECTOR3 CBoss::m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
int CBoss::m_Life = 20;
CBoss::BOSS_TYPE CBoss::m_Type;
CBoss::STATE CBoss::m_State;

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
	m_Life = 35;
	AttacKCount = 0;
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
	m_Type = TYPE_SPAWN;
	SetType(TYPE_BOSS);
	CObject2D::Create(TYPE_GUAGE,1);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
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
	if (m_Type == TYPE_SPAWN)
	{
		m_col.a += 0.02f;
		CObject2D::SetCol(m_col);
		if (m_col.a > 1.0f)
		{
			m_Type = TYPE_NONE;
		}
	}
	if (m_Type == TYPE_INVISIBLE)
	{
		m_col.a -= 0.02f;
		if (m_col.a < 0.0f)
		{
			m_col.a = 0.0f;
		}
		CObject2D::SetCol(m_col);
	}


	D3DXVECTOR3 WorldPos = CPlayer::GetWorld();
	m_pos = m_posWorld + WorldPos;
	SetPlayerPos(m_pos, BOSS_HEIGHT, BOSS_WIDTH);
	StateControl();
	//CItem::CollisionItem(m_pos, BOSS_HEIGHT, BOSS_WIDTH);
	m_move.x *= 0.06f;

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
	m_pos = D3DXVECTOR3(pos.x+170.0f, pos.y+80.0f , pos.z);
	CObject2D::Create(TYPE_BOSS, 1);

}

//====================================================
//プレイヤーの操作処理
//====================================================
void CBoss::BossContoroll(void)
{
	if (AttacKCount % 660 == 0 && AttacKCount > 0)
	{
		m_Type = TYPE_INVISIBLE;
	}
	if (m_Type == TYPE_NONE)
	{
		AttacKCount++;

		if (AttacKCount % 120 == 0 && AttacKCount > 0)
		{
			D3DXVECTOR3 aPos;
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
						if (type == CObject::TYPE_PLAYER)
						{
							aPos = pObj->GetPos();
						}
					}

				}
			}
			CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y - 160.0f, 0.0f),
				D3DXVECTOR3(-10.0f, -10.0f, 0.0f),
				D3DXVECTOR3(0.0f, 0.0f, atan2f((m_pos.x - 20.0f) - aPos.x, (m_pos.y- 160.0f) - aPos.y+50.0f)),
				CBullet::TYPE_BULL,
				1,
				CBullet::BULLET_ENEMY);

		}
		
	}
	if (m_Type == TYPE_INVISIBLE)
	{
		AttacKCount++;

		if (AttacKCount == 760)
		{
			CBullet::Create(D3DXVECTOR3(-50.0f, 160.0f, 0.0f),
				D3DXVECTOR3(+5.5f, 0.0f, 0.0f),
				D3DXVECTOR3(0.0f, 0.0f, 1.0f),
				CBullet::TYPE_BULL,
				0,
				CBullet::BULLET_ENEMY);
			CBullet::Create(D3DXVECTOR3(-120.0f, 160.0f, 0.0f),
				D3DXVECTOR3(+5.5f, 0.0f, 0.0f),
				D3DXVECTOR3(0.0f, 0.0f, 1.0f),
				CBullet::TYPE_BULL,
				0,
				CBullet::BULLET_ENEMY);
			CBullet::Create(D3DXVECTOR3(-190.0f, 160.0f, 0.0f),
				D3DXVECTOR3(+5.5f, 0.0f, 0.0f),
				D3DXVECTOR3(0.0f, 0.0f, 1.0f),
				CBullet::TYPE_BULL,
				0,
				CBullet::BULLET_ENEMY);
			CBullet::Create(D3DXVECTOR3(-260.0f, 160.0f, 0.0f),
				D3DXVECTOR3(+5.5f, 0.0f, 0.0f),
				D3DXVECTOR3(0.0f, 0.0f, 1.0f),
				CBullet::TYPE_BULL,
				0,
				CBullet::BULLET_ENEMY);
			CBullet::Create(D3DXVECTOR3(1380.0f, 320.0f, 0.0f),
				D3DXVECTOR3(-5.5f, 0.0f, 0.0f),
				D3DXVECTOR3(0.0f, 0.0f, 1.0f),
				CBullet::TYPE_BULL,
				0,
				CBullet::BULLET_ENEMY);
			CBullet::Create(D3DXVECTOR3(1450.0f, 320.0f, 0.0f),
				D3DXVECTOR3(-5.5f, 0.0f, 0.0f),
				D3DXVECTOR3(0.0f, 0.0f, 1.0f),
				CBullet::TYPE_BULL,
				0,
				CBullet::BULLET_ENEMY);
			CBullet::Create(D3DXVECTOR3(1520.0f, 320.0f, 0.0f),
				D3DXVECTOR3(-5.5f, 0.0f, 0.0f),
				D3DXVECTOR3(0.0f, 0.0f, 1.0f),
				CBullet::TYPE_BULL,
				0,
				CBullet::BULLET_ENEMY);
			CBullet::Create(D3DXVECTOR3(1590.0f, 320.0f, 0.0f),
				D3DXVECTOR3(-5.5f, 0.0f, 0.0f),
				D3DXVECTOR3(0.0f, 0.0f, 1.0f),
				CBullet::TYPE_BULL,
				0,
				CBullet::BULLET_ENEMY);
		}
		if (AttacKCount % 1000 == 0)
		{
			m_Type = TYPE_SPAWN;
			AttacKCount = 0;
		}
	}
}

bool CBoss::ColisionBoss(D3DXVECTOR3 pos)
{
	if (m_Type == TYPE_NONE)
	{
		if (m_pos.x - 200.0f < pos.x&& m_pos.y - BOSS_WIDTH < pos.y && m_pos.x + 250.0f> pos.x&& m_pos.y +200.0f > pos.y)
		{

			DamageBoss(1);
			m_State = STATE_DAMAGE;
			return true;
		}
	}
	
	return false;
}
void CBoss::DamageBoss(int nDamage)
{
	m_Life -= nDamage;
	CSound::Play(CSound::SOUND_LABEL_SE000);
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

void CBoss::StateControl(void)
{
	if (m_State == STATE_DAMAGE)
	{
		m_StateCnt++;
		if (m_StateCnt % 5 == 0 && m_StateCnt >0)
		{
			m_State = STATE_NONE;
			m_StateCnt = 0;

		}
		SetCol(D3DXCOLOR(0.8f, 0.2f, 0.2f, m_col.a));
	}
	else
	{
		SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_col.a));
	}
}