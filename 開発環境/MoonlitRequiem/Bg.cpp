//=========================================================================================================
//
//2D専用のポリゴンの処理
//Author:堀川萩大
//
//=========================================================================================================
#include "Bg.h"
#include "Object2D.h"
#include "Manager.h"
#include "Renderer.h"
#include "Texture.h"

#define BG_HEIGHT	(640.0f)
#define BG_WIDTH	(360.0f)


D3DXVECTOR3 CBg::m_texMove;
//====================================================
//コンストラクタ
//====================================================
CBg::CBg(int nPriority):CObject2D(nPriority)
{
	m_pos = D3DXVECTOR3 (0.0f,0.0f,0.0f);
	m_move = D3DXVECTOR3 (0.0f,0.0f,0.0f);
	m_Texpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_texMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//====================================================
//デストラクタ
//====================================================
CBg::~CBg()
{
	
}


//====================================================
//ポリゴンの初期化処理
//====================================================
HRESULT CBg::Init(void)
{
	CManager Renderer;
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	CObject2D::Init();

	m_pos = D3DXVECTOR3(640.0f, 360.0f, 0.0f);
	CManager pManager;
	CScene::MODE mode;
	mode = CManager::GetInstance()->GetMode();

	CTexture *pTexture = CManager::GetInstance()->GetpTexture();

	
	
	if (mode == CScene::MODE_TITLE)
	{
		m_TexId = pTexture->Regist("data\\TEXTURE\\SampleTitle.jpg");
		BindTexture(pTexture->GetAddress(m_TexId));

	}
	if (mode == CScene::MODE_TUTORIAL)
	{
		m_TexId = pTexture->Regist("data\\TEXTURE\\ContorolBG.jpg");
		BindTexture(pTexture->GetAddress(m_TexId));

	}
	if (mode == CScene::MODE_GAME)
	{
		m_TexId = pTexture->Regist("data\\TEXTURE\\GameBg.png");
		BindTexture(pTexture->GetAddress(m_TexId));

	}
	else if (mode == CScene::MODE_CLEAR)
	{
		m_TexId = pTexture->Regist("data\\TEXTURE\\gameclear.jpg");
		BindTexture(pTexture->GetAddress(m_TexId));

	}
	else if (mode == CScene::MODE_END)
	{
		m_TexId = pTexture->Regist("data\\TEXTURE\\gameover.jpg");
		BindTexture(pTexture->GetAddress(m_TexId));

	}
	else
	{
		CObject2D::BindTexture(pManager.m_aTextureBg);

	}
	
	SetType(TYPE_BG);

	SetPos(m_pos, BG_HEIGHT, BG_WIDTH);
	return S_OK;
}

//====================================================
//ポリゴンの終了処理
//====================================================
void CBg::Uninit(void)
{
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	//if (m_pTexture != NULL)
	//{
	//	m_pTexture->Release();
	//	m_pTexture = NULL;
	//}

}

//====================================================
//ポリゴンの更新処理
//====================================================
void CBg::Update(void)
{

	m_Texpos += m_move;
	m_Texpos += m_moveTex;
	AutoScroll(m_texMove.x, m_texMove.y);
	//SetScroll(m_Texpos.x, m_Texpos.y);
}

//====================================================
//ポリゴンの描画処理
//====================================================
void CBg::Draw(void)
{
	CObject2D::Draw();
}

