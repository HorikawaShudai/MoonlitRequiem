//=========================================================================================================
//
//2D専用のポリゴンの処理
//Author:堀川萩大
//
//=========================================================================================================
#include "Enemy.h"
#include "Object2D.h"
#include "Manager.h"
#include "Renderer.h"
#include "Input.h"
#include "Block.h"
#include "CreateMap.h"
#include "Player.h"
#include "Bullet.h"



#define ENEMY_SPEED	(3.8f)
#define ENEMY_JUMP (11.0f)
#define  GRAVITY (0.27665f)
#define COUNT_SPEED (15)
#define ENEMY_MAXTEX (6)
#define ENEMY_MAXJUMP (2)

LPDIRECT3DTEXTURE9 CEnemy::m_pTexture = NULL;
D3DXVECTOR3 CEnemy::m_Createpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//====================================================
//コンストラクタ
//====================================================
CEnemy::CEnemy()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCntAnim = 0;
	m_nCntPattern = 0;
	EnemyRot = 0;
	m_pTexture = NULL;
	m_Type = TYPE_NONE;
	m_bJump = false;
	m_JumpCnt = 0;
	EnemyRot = 0;
}
//====================================================
//デストラクタ
//====================================================
CEnemy::~CEnemy()
{

}


//====================================================
//ポリゴンの初期化処理
//====================================================
HRESULT CEnemy::Init(void)
{
	CObject2D::Init();
	SetAnim(EnemyRot, 2, 0, 1);
	m_pos = m_Createpos;
	m_posWorld = m_pos;
	CTexture *pTexture = CManager::GetInstance()->GetpTexture();
	m_TexId = pTexture->Regist("data\\TEXTURE\\Enemy.png");
	D3DXVECTOR3 WorldPos = CPlayer::GetWorld();

	m_pos = m_posWorld + WorldPos;
	SetPlayerPos(m_pos, ENEMY_HEIGHT, ENEMY_WIDTH);

	BindTexture(pTexture->GetAddress(m_TexId));
	SetType(TYPE_ENEMY);

	return S_OK;
}

//====================================================
//ポリゴンの終了処理
//====================================================
void CEnemy::Uninit(void)
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
void CEnemy::Update(void)
{
	m_posOld = GetPos();
	m_pos = GetPos();

	

	EnemyContoroll();

	m_move.y += GRAVITY;
	if (m_move.y >= GRAVITY * 24)
	{
		m_move.y = GRAVITY * 24;
	}

	if (m_move.y < -ENEMY_JUMP)
	{
		m_move.y = -ENEMY_JUMP;
	}

	m_posWorld += m_move;

	if (CBlock::CollisionBlock(m_posOld, m_pos, ENEMY_HEIGHT, ENEMY_WIDTH) == TRUE)
	{

		m_pos.y = m_posOld.y;
		SetPlayerPos(m_pos, ENEMY_HEIGHT, ENEMY_WIDTH);

		m_move.y = 0.0f;
		m_bJump = false;

	}

	if (CBlock::HCollisionBlock(m_posOld, m_pos, ENEMY_HEIGHT, ENEMY_WIDTH) == TRUE)
	{
		SetPlayerPos(m_pos, ENEMY_HEIGHT, ENEMY_WIDTH);

		m_pos.x = m_posOld.x;
		m_move.x = 0.0f;
	}
	CPlayer::Collision(m_pos);

	D3DXVECTOR3 WorldPos = CPlayer::GetWorld();
	m_pos = m_posWorld + WorldPos;
	SetPlayerPos(m_pos, ENEMY_HEIGHT, ENEMY_WIDTH);


	m_move.x *= 0.06f;
	EnemyTexture();

}

//====================================================
//ポリゴンの描画処理
//====================================================
void CEnemy::Draw(void)
{
	CObject2D::Draw();
}

//====================================================
//ブロックの生成処理
//====================================================
void CEnemy::Create(D3DXVECTOR3 pos)
{
	m_Createpos = pos;
	CObject2D::Create(TYPE_ENEMY, 1);

}

//====================================================
//プレイヤーの操作処理
//====================================================
void CEnemy::EnemyContoroll(void)
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
					D3DXVECTOR3 pPos = pObj->GetPos();
					aPos = pPos;
					if (m_pos.x > pPos.x)
					{
						EnemyRot = 1;
					}
					else
					{
						EnemyRot = 0;
					}
					
				}
			}

		}
	}

	if (m_bJump == false)
	{
		m_move.y = -8.0f;
		m_bJump = true;
		if (m_JumpCnt % 2 == 0)
		{
			m_move.x = 20.0f;
		}
		else if (m_JumpCnt % 2 == 1)
		{
			m_move.x = -20.0f;
		}

		
		m_JumpCnt++;
	}

}


void CEnemy::EnemyTexture(void)
{

	SetAnim(EnemyRot, 2, 0, 1);
	//if (m_Type == TYPE_NONE)
	//{
	//	if (EnemyRot == 1)
	//	{
	//		SetAnim(EnemyRot, Enemy_MAXTEX, 0, Enemy_MAXTEX);

	//	}
	//	if (EnemyRot == 0)
	//	{
	//		SetAnim(EnemyRot, Enemy_MAXTEX, 0, Enemy_MAXTEX);

	//	}
	//}
	//if (m_Type == TYPE_WALK)
	//{
	//	m_nCntAnim++;
	//	if (m_nCntAnim % COUNT_SPEED == 0)
	//	{
	//		m_nCntPattern++;
	//		if (EnemyRot == 1)
	//		{
	//			SetAnim(m_nCntPattern % Enemy_MAXTEX, Enemy_MAXTEX, 2, Enemy_MAXTEX);

	//		}
	//		if (EnemyRot == 0)
	//		{
	//			SetAnim(m_nCntPattern % Enemy_MAXTEX, Enemy_MAXTEX, 1, Enemy_MAXTEX);

	//		}
	//	}
	//}
	//if (m_Type == TYPE_JUMP)
	//{
	//	if (m_posOld.y < m_pos.y)
	//	{//下に降りてる

	//		if (EnemyRot == 1)
	//		{//左
	//			SetAnim(5, Enemy_MAXTEX, 0, Enemy_MAXTEX);

	//		}
	//		if (EnemyRot == 0)
	//		{//右
	//			SetAnim(4, Enemy_MAXTEX, 0, Enemy_MAXTEX);

	//		}
	//	}
	//	else if (m_posOld.y > m_pos.y)
	//	{//上に上がっている時

	//		if (EnemyRot == 1)
	//		{//左
	//			SetAnim(3, Enemy_MAXTEX, 0, Enemy_MAXTEX);

	//		}
	//		if (EnemyRot == 0)
	//		{//右
	//			SetAnim(2, Enemy_MAXTEX, 0, Enemy_MAXTEX);

	//		}
	//	}
	//}
}

bool CEnemy::ColisionEnemy(D3DXVECTOR3 pos)
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
				if (type == CObject::TYPE_ENEMY)
				{
					D3DXVECTOR3 pPos = pObj->GetPos();
					if (pPos.x - ENEMY_WIDTH < pos.x&& pPos.y - ENEMY_HEIGHT < pos.y && pPos.x + ENEMY_WIDTH> pos.x&& pPos.y > pos.y)
					{
						pObj->Release();
						return true;
					}
				}
			}
		}
	}
	return false;
}