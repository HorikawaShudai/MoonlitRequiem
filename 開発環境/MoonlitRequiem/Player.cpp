//=========================================================================================================
//
//2D専用のポリゴンの処理
//Author:堀川萩大
//
//=========================================================================================================
#include "Player.h"
#include "Object2D.h"
#include "Manager.h"
#include "Renderer.h"
#include "Input.h"
#include "Block.h"
#include "CreateMap.h"
#include "Bullet.h"
#include "LifeGuage.h"
#include "Bg.h"
#include "fade.h"

#define PLAYER_HEIGHT	(100.0f)
#define PLAYER_WIDTH	(30.0f)
#define PLAYER_SPEED	(3.8f)
#define PLAYER_JUMP (11.0f)
#define  GRAVITY (0.27665f)
#define COUNT_SPEED (15)
#define PLAYER_MAXTEX (6)
#define PLAYER_MAXJUMP (2)

LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;
D3DXVECTOR3 CPlayer::m_WorldPos = D3DXVECTOR3(0.0f,0.0f,0.0f);
int CPlayer::m_Life = 10;
CPlayer::STATE CPlayer::m_State;
//====================================================
//コンストラクタ
//====================================================
CPlayer::CPlayer()
{
	m_pos = D3DXVECTOR3(640.0f, 60.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCntAnim = 0;
	m_nCntPattern = 0;
	PlayerRot = 0;
	m_pTexture = NULL;
	m_Type = TYPE_NONE;
	m_bJump = false;
	m_JumpCnt = 0;
	m_ScloolMove = true;
	m_Life = 10;
	m_State = STATE_NONE;
	m_WorldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//====================================================
//デストラクタ
//====================================================
CPlayer::~CPlayer()
{

}


//====================================================
//ポリゴンの初期化処理
//====================================================
HRESULT CPlayer::Init(void)
{
	CObject2D::Init();
	SetAnim(m_nCntPattern % 4, 4, 0, 2);
	SetPlayerPos(m_pos, PLAYER_HEIGHT, PLAYER_WIDTH);
	CTexture *pTexture = CManager::GetInstance()->GetpTexture();
	m_TexId = pTexture->Regist("data\\TEXTURE\\player001.png");
	BindTexture(pTexture->GetAddress(m_TexId));
	SetType(TYPE_PLAYER);
	CObject2D::Create(TYPE_GUAGE,0);
	return S_OK;
}

//====================================================
//ポリゴンの終了処理
//====================================================
void CPlayer::Uninit(void)
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
void CPlayer::Update(void)
{
	m_posOld = GetPos();

	m_pos = GetPos();
	PlayerContoroll();

	m_move.y += GRAVITY;
	if (m_move.y >= GRAVITY * 24)
	{
		m_move.y = GRAVITY * 24;
	}

	if (m_move.y < -PLAYER_JUMP)
	{
		m_move.y = -PLAYER_JUMP;
	}
	
	m_pos += m_move;
	SetPlayerPos(m_pos, PLAYER_HEIGHT, PLAYER_WIDTH);


	//if (m_pos.y > 720.0f)
	//{
	//	/*m_move.y = 0.0f;
	//	m_pos.y = m_posOld.y;
	//	m_bJump = false;
	//	m_JumpCnt = 0;*/
	//}
	//if (m_pos.y - PLAYER_HEIGHT < 0.0f)
	//{
	//	m_move.y = 0.0f;
	//	m_pos.y = m_posOld.y;
	//}
	//if (m_pos.x - PLAYER_WIDTH < 0.0f)
	//{
	//	m_move.x = 0.0f;
	//	m_pos.x = m_posOld.x;
	//}
	//if (m_pos.x + PLAYER_WIDTH > 1280.0f)
	//{
	//	m_move.x = 0.0f;
	//	m_pos.x = m_posOld.x;
	//}

	if (CBlock::CollisionBlock(m_posOld, m_pos,PLAYER_HEIGHT, PLAYER_WIDTH) == TRUE)
	{

		m_pos.y = m_posOld.y;
		m_move.y = 0.0f;

		SetPlayerPos(m_pos, PLAYER_HEIGHT, PLAYER_WIDTH);

		m_bJump = false;
		m_JumpCnt = 0;

	}
	
	if (CBlock::HCollisionBlock(m_posOld, m_pos, PLAYER_HEIGHT, PLAYER_WIDTH) == TRUE)
	{

		m_pos.x = m_posOld.x;
		m_move.x = 0.0f;

		SetPlayerPos(m_pos, PLAYER_HEIGHT, PLAYER_WIDTH);

	}
	
	//エリア移動処理
	{
		//D3DXVECTOR3 KeepPos = CCsvMap::CollisionTp(m_pos, m_WorldPos);
		//if (KeepPos != m_pos)
		//{
		//	int nPuttern = CCsvMap::GetType(KeepPos);
		//	switch (nPuttern)
		//	{
		//	case CCsvMap::TP_LEFT:
		//		m_WorldPos.x += 1280.0f;
		//		m_pos = D3DXVECTOR3(1210.0f, m_pos.y, 0.0f);
		//		//SetPlayerPos(D3DXVECTOR3(1210.0f, m_pos.y, 0.0f), PLAYER_HEIGHT, PLAYER_WIDTH);
		//		break;
		//	case CCsvMap::TP_RIGHT:
		//		m_WorldPos.x -= 1280.0f;
		//		m_pos = D3DXVECTOR3(70.0f, m_pos.y, 0.0f);
		//		//SetPlayerPos(D3DXVECTOR3(70.0f, m_pos.y, 0.0f), PLAYER_HEIGHT, PLAYER_WIDTH);
		//		break;
		//	case CCsvMap::TP_UP:
		//		break;
		//	case CCsvMap::TP_DOWN:
		//		break;
		//	}
		//	
		//}
	}
	
	
	if (CCsvMap::BossSpown(m_pos, m_WorldPos) == true)
	{
		SetScloolMove(false);
	}


	//CItem::CollisionItem(m_pos, PLAYER_HEIGHT, PLAYER_WIDTH);
	m_move.x *= 0.06f;
	PlayerTexture();
	if (m_ScloolMove == true)
	{
		ScloolWorld();

	}
	SetPlayerPos(m_pos, PLAYER_HEIGHT, PLAYER_WIDTH);
	StateControl();
}

//====================================================
//ポリゴンの描画処理
//====================================================
void CPlayer::Draw(void)
{
	CObject2D::Draw();
}

//====================================================
//プレイヤーの操作処理
//====================================================
void CPlayer::PlayerContoroll(void)
{
	CInputKeyboard *pKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputMouse *pMouse = CManager::GetInstance()->GetInputMouse();
	

	
	if (pKeyboard->GetPress(DIK_A) == true)
	{//Aのみ押された場
		m_move.x += cosf(D3DX_PI *1.0f)*PLAYER_SPEED;
		m_move.y += sinf(D3DX_PI *1.0f)*PLAYER_SPEED;
		PlayerRot = 1;
		if (m_bJump == false)
		{
			m_Type = TYPE_WALK;
		}
	}
	else if (pKeyboard->GetPress(DIK_D) == true)
	{//Dのみ押された場合
		m_move.x += cosf(D3DX_PI *0.0f)*PLAYER_SPEED;
		m_move.y += sinf(D3DX_PI *0.0f)*PLAYER_SPEED;
		PlayerRot = 0;
		if (m_bJump == false)
		{
			m_Type = TYPE_WALK;
		}
	}
	if (pKeyboard->GetTrigger(DIK_DOWN) == true)
	{//↓のみ押された場合
	}
	if (pKeyboard->GetTrigger(DIK_UP) == true)
	{//↑のみ押された場合
	}
	if (pKeyboard->GetTrigger(DIK_SPACE) == true && m_JumpCnt < PLAYER_MAXJUMP)
	{//スペースのみ押された場合
		m_move.y -= PLAYER_JUMP;
		m_Type = TYPE_JUMP;
		m_bJump = true;
		m_JumpCnt++;
	}
	//攻撃操作
	if (pKeyboard->GetTrigger(DIK_B) == true  || pMouse->GetTrigger(pMouse->LEFT_CLLICK))
	{//Bのみ押された場合
		if (PlayerRot == 0)
		{
			CBullet::Create(D3DXVECTOR3(m_pos.x +15.0f, m_pos.y - 50.0f, 0.0f), D3DXVECTOR3(14.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), CBullet::TYPE_BOW, PlayerRot,CBullet::BULLET_PLAYER);

		}
		else
		{
			CBullet::Create(D3DXVECTOR3(m_pos.x - 15.0f, m_pos.y - 50.0f, 0.0f), D3DXVECTOR3(-14.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), CBullet::TYPE_BOW, PlayerRot, CBullet::BULLET_PLAYER);

		}
	}
	if (pKeyboard->GetPress(DIK_W) == false && pKeyboard->GetPress(DIK_A) == false && pKeyboard->GetPress(DIK_D) == false && m_bJump == false)
	{
		m_Type = TYPE_NONE;
	}
}


void CPlayer::PlayerTexture(void)
{
	if (m_Type == TYPE_NONE)
	{
		if (PlayerRot == 1)
		{
			SetAnim(PlayerRot, PLAYER_MAXTEX, 0, PLAYER_MAXTEX);

		}
		if (PlayerRot == 0)
		{
			SetAnim(PlayerRot, PLAYER_MAXTEX, 0, PLAYER_MAXTEX);

		}
	}
	if (m_Type == TYPE_WALK)
	{
		m_nCntAnim++;
		if (m_nCntAnim % COUNT_SPEED == 0)
		{
			m_nCntPattern++;
			if (PlayerRot == 1)
			{
				SetAnim(m_nCntPattern % PLAYER_MAXTEX, PLAYER_MAXTEX, 2, PLAYER_MAXTEX);

			}
			if (PlayerRot == 0)
			{
				SetAnim(m_nCntPattern % PLAYER_MAXTEX, PLAYER_MAXTEX, 1, PLAYER_MAXTEX);

			}
		}
	}
	if (m_Type == TYPE_JUMP)
	{
		if (m_posOld.y < m_pos.y)
		{//下に降りてる

			if (PlayerRot == 1)
			{//左
				SetAnim(5, PLAYER_MAXTEX, 0, PLAYER_MAXTEX);

			}
			if (PlayerRot == 0)
			{//右
				SetAnim(4 , PLAYER_MAXTEX, 0, PLAYER_MAXTEX);

			}
		}
		else if (m_posOld.y > m_pos.y)
		{//上に上がっている時

			if (PlayerRot == 1)
			{//左
				SetAnim(3, PLAYER_MAXTEX, 0, PLAYER_MAXTEX);

			}
			if (PlayerRot == 0)
			{//右
				SetAnim(2, PLAYER_MAXTEX, 0, PLAYER_MAXTEX);

			}
		}
	}
}

//========================================================================================================
//画面スクロール
//========================================================================================================
void CPlayer::ScloolWorld(void)
{
	if (m_pos.x > 800.0f)
	{

		m_WorldPos.x -= m_move.x *10.0f;
		m_pos.x = 800.0f;

		CBg::AddMove(0.001f, 0.0f);
	}
	else if (m_pos.x < 480.0f)
	{
		m_pos.x = 480.0f;

		m_WorldPos.x -= m_move.x*10.0f;
		CBg::AddMove(-0.001f, 0.0f);

	}
	if (m_pos.y >  500.0f &&m_WorldPos.y > -2490.0f)
	{
		m_pos.y = 500.0f;

		m_WorldPos.y -= m_move.y;
		CBg::AddMove(0.0f, 0.003f);

	}
	else if (m_pos.y < 220.0f)
	{
		m_pos.y = 220.0f;
		CBg::AddMove(0.0f, -0.003f);

		m_WorldPos.y -= m_move.y;

	}
}

D3DXVECTOR3 CPlayer::GetWorld(void)
{
	return m_WorldPos;
}
void CPlayer::SetScloolMove(bool CanMove)
{
	m_ScloolMove = CanMove;
}

bool CPlayer::Collision(D3DXVECTOR3 pos)
{

	if (m_State == STATE_NONE)
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
					if (type == CObject::TYPE_PLAYER)
					{
						D3DXVECTOR3 pPos = pObj->GetPos();
						if (pPos.x - PLAYER_WIDTH < pos.x&& pPos.y - PLAYER_HEIGHT < pos.y && pPos.x + PLAYER_WIDTH> pos.x&& pPos.y > pos.y)
						{
							Damage(1);
							m_State = STATE_DAMAGE;
							return true;
						}
					}
				}
			}
		}
	}

	return false;
}

void CPlayer::Damage(int nDamage)
{
	m_Life -= nDamage;
	if (m_Life <= 0)
	{
		CFade *pFade = CManager::GetInstance()->GetpFade();

		CFade::FADE StateFade;
		StateFade = pFade->GetFade();
		if (StateFade == CFade::FADE_NONE)
		{

			pFade->SetFade(CScene::MODE_END, 0.001f);
		}
	}
}

void CPlayer::StateControl(void)
{
	if (m_State == STATE_DAMAGE)
	{
		m_StateCnt++;
		if (m_StateCnt % 120 == 0 && m_StateCnt >0)
		{
			m_State = STATE_NONE;
			m_StateCnt = 0;

		}
		SetCol(D3DXCOLOR(0.8f, 0.2f, 0.2f, 1.0f));
	}
	else
	{
		SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}