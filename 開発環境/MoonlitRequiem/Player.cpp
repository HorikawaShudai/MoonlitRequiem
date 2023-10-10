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


#define PLAYER_HEIGHT	(30.0f)
#define PLAYER_WIDTH	(100.0f)
#define PLAYER_SPEED	(6.2f)
#define  GRAVITY (0.27665f)

LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;

//====================================================
//コンストラクタ
//====================================================
CPlayer::CPlayer()
{
	m_pos = D3DXVECTOR3(640.0f, 600.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCntAnim = 0;
	m_nCntPattern = 0;
	PlayerRot = 0;
	m_pTexture = NULL;
	m_Type = TYPE_NONE;
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
	CTexture *pTexture = CManager::GetpTexture();
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
	
	m_pos += m_move;


	if (m_pos.y > 720.0f)
	{
		m_move.y = 0.0f;
		m_pos.y = m_posOld.y;
	}
	if (m_pos.y - PLAYER_WIDTH < 0.0f)
	{
		m_move.y = 0.0f;
		m_pos.y = m_posOld.y;
	}
	if (m_pos.x - PLAYER_HEIGHT < 0.0f)
	{
		m_move.x = 0.0f;
		m_pos.x = m_posOld.x;
	}
	if (m_pos.x + PLAYER_HEIGHT > 1280.0f)
	{
		m_move.x = 0.0f;
		m_pos.x = m_posOld.x;
	}
	//if (CBlock::CollisionBlock(m_posOld, m_pos,PLAYER_HEIGHT, PLAYER_WIDTH) == TRUE)
	//{
	//	m_move.y = 0.0f;

	//	m_pos.y = m_posOld.y;

	//}
	//if (CBlock::HCollisionBlock(m_posOld, m_pos, PLAYER_HEIGHT, PLAYER_WIDTH) == TRUE)
	//{
	//	m_move.x = 0.0f;

	//	m_pos.x = m_posOld.x;

	//}
	//CItem::CollisionItem(m_pos, PLAYER_HEIGHT, PLAYER_WIDTH);
	SetPlayerPos(m_pos, PLAYER_HEIGHT, PLAYER_WIDTH);
	m_move.x *= 0.05f;
	
	if (m_Type == TYPE_WALK)
	{
		m_nCntAnim++;
		if (m_nCntAnim % 30 == 0)
		{
			m_nCntPattern++;
			SetAnim(m_nCntPattern % 4, 4, PlayerRot, 2);
		}
	}
	
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
	CInputKeyboard *pKeyboard = CManager::GetInputKeyboard();
	

	if (pKeyboard->GetPress(DIK_W) == false && pKeyboard->GetPress(DIK_A) == false && pKeyboard->GetPress(DIK_D) == false && m_Type != TYPE_JUMP)
	{
		m_Type = TYPE_NONE;
	}
	if (pKeyboard->GetPress(DIK_LEFT) == true)
	{//Aのみ押された場
		m_move.x += cosf(D3DX_PI *1.0f)*PLAYER_SPEED;
		m_move.y += sinf(D3DX_PI *1.0f)*PLAYER_SPEED;
		PlayerRot = 1;
		m_Type = TYPE_WALK;
	}
	else if (pKeyboard->GetPress(DIK_RIGHT) == true)
	{//Dのみ押された場合
		m_move.x += cosf(D3DX_PI *0.0f)*PLAYER_SPEED;
		m_move.y += sinf(D3DX_PI *0.0f)*PLAYER_SPEED;
		PlayerRot = 0;
		m_Type = TYPE_WALK;
	}
	if (pKeyboard->GetTrigger(DIK_DOWN) == true)
	{//↓のみ押された場合
	}
	if (pKeyboard->GetTrigger(DIK_UP) == true)
	{//↑のみ押された場合
	}
	if (pKeyboard->GetTrigger(DIK_SPACE) == true)
	{//スペースのみ押された場合
		m_move.y -= 15.0f;
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
		CObject::Reset();
	}
}