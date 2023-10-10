//=========================================================================================================
//
//2D��p�̃|���S���̏���
//Author:�x�씋��
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
//�R���X�g���N�^
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
//�f�X�g���N�^
//====================================================
CPlayer::~CPlayer()
{

}


//====================================================
//�|���S���̏���������
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
//�|���S���̏I������
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
//�|���S���̍X�V����
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
//�|���S���̕`�揈��
//====================================================
void CPlayer::Draw(void)
{
	CObject2D::Draw();
}

//====================================================
//�v���C���[�̑��쏈��
//====================================================
void CPlayer::PlayerContoroll(void)
{
	CInputKeyboard *pKeyboard = CManager::GetInputKeyboard();
	

	if (pKeyboard->GetPress(DIK_W) == false && pKeyboard->GetPress(DIK_A) == false && pKeyboard->GetPress(DIK_D) == false && m_Type != TYPE_JUMP)
	{
		m_Type = TYPE_NONE;
	}
	if (pKeyboard->GetPress(DIK_LEFT) == true)
	{//A�̂݉����ꂽ��
		m_move.x += cosf(D3DX_PI *1.0f)*PLAYER_SPEED;
		m_move.y += sinf(D3DX_PI *1.0f)*PLAYER_SPEED;
		PlayerRot = 1;
		m_Type = TYPE_WALK;
	}
	else if (pKeyboard->GetPress(DIK_RIGHT) == true)
	{//D�̂݉����ꂽ�ꍇ
		m_move.x += cosf(D3DX_PI *0.0f)*PLAYER_SPEED;
		m_move.y += sinf(D3DX_PI *0.0f)*PLAYER_SPEED;
		PlayerRot = 0;
		m_Type = TYPE_WALK;
	}
	if (pKeyboard->GetTrigger(DIK_DOWN) == true)
	{//���̂݉����ꂽ�ꍇ
	}
	if (pKeyboard->GetTrigger(DIK_UP) == true)
	{//���̂݉����ꂽ�ꍇ
	}
	if (pKeyboard->GetTrigger(DIK_SPACE) == true)
	{//�X�y�[�X�̂݉����ꂽ�ꍇ
		m_move.y -= 15.0f;
	}
	//�U������
	if (pKeyboard->GetTrigger(DIK_B) == true && m_Type != TYPE_JUMP)
	{//B�̂݉����ꂽ�ꍇ
	}
	if (pKeyboard->GetTrigger(DIK_N) == true && m_Type != TYPE_JUMP)
	{//N�̂݉����ꂽ�ꍇ
	}

	
	
	if (pKeyboard->GetTrigger(DIK_R) == true)
	{//W�̂݉����ꂽ�ꍇ
		CObject::Reset();
	}
}