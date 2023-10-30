//=========================================================================================================
//
//2DêÍópÇÃíeÇÃèàóù
//Author:ñxêÏîãëÂ
//
//=========================================================================================================
#include "Bullet.h"
#include "Object2D.h"
#include "Manager.h"
#include "Renderer.h"
#include "Player.h"
#include "Enemy.h"
#include "Boss.h"
#include "Game.h"
#include "Block.h"


D3DXVECTOR3 CBullet::m_Createpos;
LPDIRECT3DTEXTURE9 CBullet::m_pTexture;
D3DXVECTOR3 CBullet::m_Createmove;
D3DXVECTOR3 CBullet::m_Createrot;
int CBullet::m_CreateRot;
CBullet::BULLET_TYPE CBullet::m_Createtype;
CBullet::BULLET_OBJ CBullet::m_Createobj;
//====================================================
//ÉRÉìÉXÉgÉâÉNÉ^
//====================================================
CBullet::CBullet()
{


}
//====================================================
//ÉfÉXÉgÉâÉNÉ^
//====================================================
CBullet::~CBullet()
{

}


//====================================================
//íeÇÃèâä˙âªèàóù
//====================================================
HRESULT CBullet::Init(void)
{

	CObject2D::Init();
	m_move = m_Createmove;
	m_type = m_Createtype;
	m_pos = m_Createpos;
	m_nrot = m_CreateRot;
	m_rot = m_Createrot;
	m_Obj = m_Createobj;
	m_posWorld = m_pos;

	if (m_Obj == BULLET_PLAYER)
	{
		SetPos(m_pos, BULLET_HEIGHT, BULLET_WIDTH);

		CTexture *pTexture = CManager::GetInstance()->GetpTexture();
		m_TexId = pTexture->Regist("data\\TEXTURE\\Bow.png");
		SetAnim(m_nrot, 2, 0, 1);

	}
	else if (m_Obj == BULLET_ENEMY)
	{
		SetPos(m_pos, 50.0f, 50.0f);

		CTexture *pTexture = CManager::GetInstance()->GetpTexture();
		m_TexId = pTexture->Regist("data\\TEXTURE\\Bullet.png");
		SetAnim(0, 1, 0, 1);

	}
	//BindTexture(m_pTexture);
	SetType(TYPE_BULLET);
	return S_OK;
}

//====================================================
//íeÇÃèIóπèàóù
//====================================================
void CBullet::Uninit(void)
{
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//====================================================
//íeÇÃçXêVèàóù
//====================================================
void CBullet::Update(void)
{
	/*D3DXVECTOR3 WorldPos = CPlayer::GetWorld();
	m_posWorldOld = CPlayer::GetWorld();

	D3DXVECTOR3 Wpos = CPlayer::GetWorld();
	m_pos += m_move + Wpos;*/

	/*m_pos.x += sinf(m_rot.z) * m_move.x;
	m_pos.y += cosf(m_rot.z) * m_move.y;*/

	CGame::PHASE pPhase = CGame::GetPhase();

	if (m_Obj == BULLET_PLAYER)
	{
		D3DXVECTOR3 WorldPos = CPlayer::GetWorld();
		m_posOld = m_pos;
		//m_pos += m_move;
		m_pos.x += sinf(m_rot.z) * m_move.x;
		m_pos.y += cosf(m_rot.z) * m_move.y;
		SetPos(m_pos, BULLET_HEIGHT, BULLET_WIDTH);

		if (CEnemy::ColisionEnemy(m_pos) == true && pPhase == CGame::PHASE_NORMAL)
		{
			CObject::Release();
		}
		if (CBoss::ColisionBoss(m_pos) == true && pPhase == CGame::PHASE_BOSS)
		{
			CObject::Release();
		}
		if (CBlock::HCollisionBlock(m_posOld, m_pos, BULLET_HEIGHT, BULLET_WIDTH) == TRUE)
		{
			CObject::Release();

			/*m_posWorld = m_pos;
			m_move.x = 0.0f;
			m_mode = BULLET_NONE;*/


		}
	}
	else if (m_Obj == BULLET_ENEMY)
	{
		D3DXVECTOR3 WorldPos = CPlayer::GetWorld();
		m_posOld = m_pos;
		//m_pos += m_move;
		m_pos.x += sinf(m_rot.z) * m_move.x;
		m_pos.y += cosf(m_rot.z) * m_move.y;
		SetPos(m_pos, 50.0f, 50.0f);
		if (CBlock::HCollisionBlock(m_posOld, m_pos, 50.0f, 50.0f) == TRUE)
		{
			CObject::Release();

		}
		if (CPlayer::Collision(m_pos) == true)
		{
			CObject::Release();
		}
	}



	


	
}

//====================================================
//íeÇÃï`âÊèàóù
//====================================================
void CBullet::Draw(void)
{
	CObject2D::Draw();
}

//====================================================
//íeÇÃê∂ê¨èàóù
//====================================================
void CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 mrot, BULLET_TYPE type,int rot,BULLET_OBJ obj)
{

	m_Createmove = move;
	m_Createtype = type;
	m_Createpos = pos;
	m_Createrot= mrot;
	m_CreateRot = rot;
	m_Createobj = obj;
	CObject2D::Create(TYPE_BULLET, 1);

}