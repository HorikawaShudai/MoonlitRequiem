//=========================================================================================================
//
//2D��p�̃|���S���̏���
//Author:�x�씋��
//
//=========================================================================================================
#include "Object2D.h"
#include "Renderer.h"
#include "Manager.h"
#include "Player.h"
#include "Block.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Boss.h"
#include "Bg.h"
#include "LifeGuage.h"


#define POLYGON_HEIGHT	(30.0f)
#define POLYGON_WIDTH	(50.0f)
//====================================================
//�R���X�g���N�^
//====================================================
CObject2D::CObject2D(int nPriority):CObject(nPriority)
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_moveTex = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//====================================================
//�f�X�g���N�^
//====================================================
CObject2D::~CObject2D()
{

}


//====================================================
//�|���S���̏���������
//====================================================
HRESULT CObject2D::Init(void)
{
	//m_pos = D3DXVECTOR3(640.0f, 600.0f, 0.0f);

	CManager Renderer;
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - POLYGON_HEIGHT, m_pos.y - POLYGON_WIDTH, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + POLYGON_HEIGHT, m_pos.y - POLYGON_WIDTH, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - POLYGON_HEIGHT, m_pos.y + POLYGON_WIDTH, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + POLYGON_HEIGHT, m_pos.y + POLYGON_WIDTH, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//====================================================
//�|���S���̏I������
//====================================================
void CObject2D::Uninit(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//====================================================
//�|���S���̕`�揈��
//====================================================
void CObject2D::Draw(void)
{
	CManager Renderer;
	CTexture *pTexture = CManager::GetInstance()->GetpTexture();
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	m_pTexture = pTexture->GetAddress(m_TexId);
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));
	
	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetTexture(0, m_pTexture);

	//�|���S��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//====================================================
//�|���S���̍X�V����
//====================================================
void CObject2D::Update(void)
{

}

//====================================================
//�|���S���̈ʒu�̐ݒ�
//====================================================
void CObject2D::SetPos(D3DXVECTOR3 pos, float Height, float Width)
{
	m_pos = pos;

	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x- Height, m_pos.y- Width, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x+ Height, m_pos.y- Width, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x- Height, m_pos.y+ Width, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x+ Height, m_pos.y+ Width, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
//====================================================
//�|���S���̈ʒu�̐ݒ�
//====================================================
void CObject2D::SetPlayerPos(D3DXVECTOR3 pos, float Height, float Width)
{
	m_pos = pos;

	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - Width, m_pos.y - Height, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + Width, m_pos.y - Height, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - Width, m_pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + Width, m_pos.y, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
//====================================================
//�|���S���̈ʒu�̐ݒ�
//====================================================
void CObject2D::SetEnemyPos(D3DXVECTOR3 pos, float Height, float Width)
{
	m_pos = pos;

	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - Width, m_pos.y - Height, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + Width, m_pos.y - Height, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - Width, m_pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + Width, m_pos.y, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}


//====================================================
//�|���S���̌����̐ݒ�
//====================================================
void CObject2D::SetRot(float rot)
{
	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - (cosf(D3DX_PI *rot)* POLYGON_HEIGHT), m_pos.y-(cosf(D3DX_PI * rot)* POLYGON_WIDTH), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (cosf(D3DX_PI *rot)* POLYGON_HEIGHT), m_pos.y-(cosf(D3DX_PI * rot)* POLYGON_WIDTH), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - (cosf(D3DX_PI *rot)* POLYGON_HEIGHT), m_pos.y+(cosf(D3DX_PI * rot)* POLYGON_WIDTH), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (cosf(D3DX_PI *rot)* POLYGON_HEIGHT), m_pos.y+(cosf(D3DX_PI * rot)* POLYGON_WIDTH), 0.0f);
	float  frot  = sinf(D3DX_PI *rot)* POLYGON_HEIGHT;
	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//====================================================
//�I�u�W�F�N�g�̐�������
//====================================================
CObject2D *CObject2D::Create(TYPE type2D,int type)
{
	CObject2D *pObject2D = NULL;

	switch (type2D)
	{
	case TYPE_PLAYER:
		pObject2D = new CPlayer;

		pObject2D->Init();
		break;
	case TYPE_BLOCK:
		pObject2D = new CBlock;

		pObject2D->Init();
		break;

	case TYPE_ENEMY:
		pObject2D = new CEnemy;

		pObject2D->Init();
		break;
	case TYPE_BULLET:
		pObject2D = new CBullet;

		pObject2D->Init();
		break;
	case TYPE_BOSS:
		pObject2D = new CBoss;

		pObject2D->Init();
		break;
	case TYPE_BG:
		pObject2D = new CBg;

		pObject2D->Init();
		break;
	case TYPE_GUAGE:
		pObject2D = CLifeGuage::Create(type);

		pObject2D->Init();
		break;
	}


	return pObject2D;
}

//====================================================
//�e�N�X�`���̐ݒ菈��
//====================================================
void CObject2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//====================================================
//�e�N�X�`�����W�̐ݒ菈��
//====================================================
void CObject2D::SetAnim(int xCount,int xPuttern,int yCount,int yPuttern)
{
	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	

	//�e�N�X�`�����W�̐ݒ� 
	pVtx[0].tex = D3DXVECTOR2(0.0f +            1.0f / xPuttern*xCount, 0.0f			+ 1.0f / yPuttern*yCount);
	pVtx[1].tex = D3DXVECTOR2(1.0f / xPuttern + 1.0f / xPuttern*xCount, 0.0f			+ 1.0f / yPuttern*yCount);
	pVtx[2].tex = D3DXVECTOR2(0.0f +			1.0f / xPuttern*xCount, 1.0f / yPuttern + 1.0f / yPuttern*yCount);
	pVtx[3].tex = D3DXVECTOR2(1.0f / xPuttern + 1.0f / xPuttern*xCount, 1.0f / yPuttern + 1.0f / yPuttern*yCount);
	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//====================================================
//�ʒu�̎擾����
//====================================================
D3DXVECTOR3 CObject2D::GetPos(void)
{
	return m_pos;
}

//====================================================
//�e�N�X�`���̎����J��
//====================================================
void CObject2D::AutoScroll(float hMoveTex, float wMoveTex)
{
	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ� 
	pVtx[0].tex = D3DXVECTOR2(0.0f + hMoveTex, 0.0f + wMoveTex);
	pVtx[1].tex = D3DXVECTOR2(1.0f + hMoveTex, 0.0f + wMoveTex);
	pVtx[2].tex = D3DXVECTOR2(0.0f + hMoveTex, 1.0f + wMoveTex);
	pVtx[3].tex = D3DXVECTOR2(1.0f + hMoveTex, 1.0f + wMoveTex);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

void CObject2D::SetSize(float Height, float Width)
{

	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - Height, m_pos.y - Width, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + Height, m_pos.y - Width, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - Height, m_pos.y + Width, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + Height, m_pos.y + Width, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

void CObject2D::SetCol(D3DXCOLOR col)
{
	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�̐ݒ�
	pVtx[0].col = D3DXCOLOR(col);
	pVtx[1].col = D3DXCOLOR(col);
	pVtx[2].col = D3DXCOLOR(col);
	pVtx[3].col = D3DXCOLOR(col);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

