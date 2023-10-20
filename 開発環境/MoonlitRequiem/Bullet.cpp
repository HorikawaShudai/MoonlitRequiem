//=========================================================================================================
//
//2D��p�̒e�̏���
//Author:�x�씋��
//
//=========================================================================================================
#include "Bullet.h"
#include "Object2D.h"
#include "Manager.h"
#include "Renderer.h"
#include "Player.h"
#include "Enemy.h"
#include "Boss.h"



D3DXVECTOR3 CBullet::m_Createpos;
LPDIRECT3DTEXTURE9 CBullet::m_pTexture;
D3DXVECTOR3 CBullet::m_Createmove;
int CBullet::m_CreateRot;
CBullet::BULLET_TYPE CBullet::m_Createtype;
//====================================================
//�R���X�g���N�^
//====================================================
CBullet::CBullet()
{


}
//====================================================
//�f�X�g���N�^
//====================================================
CBullet::~CBullet()
{

}


//====================================================
//�e�̏���������
//====================================================
HRESULT CBullet::Init(void)
{

	CObject2D::Init();
	m_move = m_Createmove;
	m_type = m_Createtype;
	m_pos = m_Createpos;
	m_rot = m_CreateRot;

	SetPos(m_pos, BULLET_HEIGHT, BULLET_WIDTH);
	m_posWorld = m_pos;

	CTexture *pTexture = CManager::GetInstance()->GetpTexture();
	m_TexId = pTexture->Regist("data\\TEXTURE\\Bow.png");
	//BindTexture(m_pTexture);
	SetType(TYPE_BULLET);
	SetAnim(m_rot,2,0,1);
	return S_OK;
}

//====================================================
//�e�̏I������
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
//�e�̍X�V����
//====================================================
void CBullet::Update(void)
{
	D3DXVECTOR3 WorldPos = CPlayer::GetWorld();
	m_posWorldOld = CPlayer::GetWorld();

	D3DXVECTOR3 Wpos = CPlayer::GetWorld() - m_posWorldOld;
	m_pos += m_move + Wpos;
	SetPos(m_pos, BULLET_HEIGHT, BULLET_WIDTH);

	if (CEnemy::ColisionEnemy(m_pos) == true)
	{
		CObject:: Release();
	}

	if (CBoss::ColisionBoss(m_pos) == true)
	{
		CObject::Release();
	}
}

//====================================================
//�e�̕`�揈��
//====================================================
void CBullet::Draw(void)
{
	CObject2D::Draw();
}

//====================================================
//�e�̐�������
//====================================================
void CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, BULLET_TYPE type,int rot)
{

	m_Createmove = move;
	m_Createtype = type;
	m_Createpos = pos;
	m_CreateRot = rot;

	CObject2D::Create(TYPE_BULLET, 1);

}