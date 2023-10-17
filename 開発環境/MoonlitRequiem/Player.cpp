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


	if (m_pos.y > 720.0f)
	{
		/*m_move.y = 0.0f;
		m_pos.y = m_posOld.y;
		m_bJump = false;
		m_JumpCnt = 0;*/
	}
	if (m_pos.y - PLAYER_HEIGHT < 0.0f)
	{
		m_move.y = 0.0f;
		m_pos.y = m_posOld.y;
	}
	if (m_pos.x - PLAYER_WIDTH < 0.0f)
	{
		m_move.x = 0.0f;
		m_pos.x = m_posOld.x;
	}
	if (m_pos.x + PLAYER_WIDTH > 1280.0f)
	{
		m_move.x = 0.0f;
		m_pos.x = m_posOld.x;
	}
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
	//CItem::CollisionItem(m_pos, PLAYER_HEIGHT, PLAYER_WIDTH);
	m_move.x *= 0.06f;
	PlayerTexture();
	ScloolWorld();
	SetPlayerPos(m_pos, PLAYER_HEIGHT, PLAYER_WIDTH);

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
	if (pKeyboard->GetTrigger(DIK_B) == true && m_Type != TYPE_JUMP)
	{//Bのみ押された場合
	}
	if (pKeyboard->GetTrigger(DIK_N) == true && m_Type != TYPE_JUMP)
	{//Nのみ押された場合
	}

	
	
	if (pKeyboard->GetTrigger(DIK_R) == true)
	{//Wのみ押された場合
		m_pos = D3DXVECTOR3(640.0f, 600.0f, 0.0f);
		m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_WorldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
//攻撃がヒットしてしまったとき
//========================================================================================================
void CPlayer::ScloolWorld(void)
{
	if (m_pos.x > 920.0f)
	{

		m_WorldPos.x -= m_move.x *10.0f;
		m_pos.x = 920.0f;


	}
	else if (m_pos.x < 360.0f)
	{
		m_pos.x = 360.0f;

		m_WorldPos.x -= m_move.x*10.0f;

	}
	if (m_pos.y >  500.0f)
	{
		m_pos.y = 500.0f;

		m_WorldPos.y -= m_move.y;

	}
	else if (m_pos.y < 220.0f)
	{
		m_pos.y = 220.0f;

		m_WorldPos.y -= m_move.y;

	}
}

D3DXVECTOR3 CPlayer::GetWorld(void)
{
	return m_WorldPos;
}