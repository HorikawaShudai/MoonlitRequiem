//===========================================================
//
//スコアの処理操作
//Author:堀川萩大
//
//===========================================================

#include "Time.h"
#include "input.h"
#include "Manager.h"
#include "Renderer.h"
#include "Object.h"

LPDIRECT3DTEXTURE9 CNumber::m_pTexture = {};
D3DXVECTOR3 CNumber::m_pos = {};

D3DXVECTOR3 CTime::m_pos = {};
int CTime::m_Time = 0;
CNumber *CNumber::m_pScore[NUM_PLACE] = {};
//====================================================
//コンストラクタ
//====================================================
CNumber::CNumber(int nPriority):CObject2D(nPriority)
{
	SetType(TYPE_NUMBER);
}
//====================================================
//デストラクタ
//====================================================
CNumber::~CNumber()
{

}


//====================================================
//ポリゴンの初期化処理
//====================================================
HRESULT CNumber::Init(void)
{
	for (int nCnt = 0; nCnt < NUM_PLACE; nCnt++)
	{
		if (m_pScore[nCnt]->m_pVtxBuff == NULL)
		{
			m_pScore[nCnt]->CObject2D::Init();
			CTexture *pTexture = CManager::GetInstance()->GetpTexture();
			m_TexId = pTexture->Regist("data\\TEXTURE\\time.png");
			m_pScore[nCnt]->m_TexNum = m_TexId;
			m_pScore[nCnt]->SetPos(m_pos, 20.0f, 35.0f);
			break;
		}
	}

	//CObject2D::Init();

	//CObject2D::BindTexture(m_pTexture);
	//SetPos(m_pos, 15.0f, 35.0f);

	return S_OK;
}

//====================================================
//ポリゴンの終了処理
//====================================================
void CNumber::Uninit(void)
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
	for (int nCnt = 0; nCnt < NUM_PLACE; nCnt++)
	{
		if (m_pScore[nCnt] != NULL)
		{
			m_pScore[nCnt] = NULL;

			delete m_pScore[nCnt];
		}
	}

}

//====================================================
//ポリゴンの更新処理
//====================================================
void CNumber::Update(void)
{

}

//====================================================
//ポリゴンの描画処理
//====================================================
void CNumber::Draw(void)
{


			//m_pScore[nCnt]->CObject2D::Draw();

	CManager Renderer;
	CTexture *pTexture = CManager::GetInstance()->GetpTexture();
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	for (int nCnt = 0; nCnt < NUM_PLACE; nCnt++)
	{
		if (m_pScore[nCnt]->m_pVtxBuff != NULL)
		{
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetTexture(0, pTexture->GetAddress(m_pScore[nCnt]->m_TexNum));

	//ポリゴン
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		}
	}
	
}

void CNumber::Create(D3DXVECTOR3 pos)
{
	m_pos = pos;

	CObject2D::Create(TYPE_NUMBER,0);
}

HRESULT CNumber::Load(void)
{
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\time.png",
		&m_pTexture);
	return S_OK;
}
void CNumber::UnLoad(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}



CTime::CTime()
{

}
CTime::~CTime()
{

}
//=========================================================================================================
//初期化処理
//=========================================================================================================
HRESULT CTime::Init(void)
{
	//m_pScore[nCnt]->m_TexNum
	return S_OK;

}

//=========================================================================================================
//終了処理
//=========================================================================================================
void CTime::Uninit(void)
{

}

//=========================================================================================================
//更新処理
//=========================================================================================================
void CTime::Update(void)
{

}

//=========================================================================================================
//描画処理
//=========================================================================================================
void CTime::Draw(void)
{

}

//=========================================================================================================
//スコアの設定処理
//=========================================================================================================
void CTime::SetScore(int nTime)
{
	int aTexU[NUM_PLACE];
	m_Time = nTime;

	if (m_Time <= 0)
	{
		m_Time = 0;
	}

	for (int nCount = 0, Max = 1000000, Min = 100000; nCount < NUM_PLACE; nCount++, Max /= 10, Min /= 10)
	{
		aTexU[nCount] = m_Time % Max / Min;
		m_pScore[nCount]->SetAnim(aTexU[nCount], 10, 0, 1);
	}

	
}

//=========================================================================================================
//スコアの計算処理
//=========================================================================================================
void CTime::AddScore(int nTime)
{
	int aTexU[NUM_PLACE];
	m_Time += nTime;

	if (m_Time > 999999)
	{
		m_Time = 999999;
	}
	if (m_Time < 0)
	{
		m_Time = 0;
	}
	if (m_Time % 6000 == 0 && m_Time > 0)
	{
		m_Time += 4000;
	}

	for (int nCount = 0, Max = 1000000, Min = 100000; nCount < NUM_PLACE; nCount++, Max /= 10, Min /= 10)
	{
		aTexU[nCount] = m_Time % Max / Min;
		m_pScore[nCount]->SetAnim(aTexU[nCount], 10, 0, 1);
	}
}

CTime *CTime::Create(void)
{
	CTime *pTime;

	pTime = new CTime;
	for (int nCnt = 0; nCnt < NUM_PLACE; nCnt++)
	{
		if (pTime->m_pScore[nCnt] == NULL)
		{
			pTime->m_pScore[nCnt] = new CNumber;
			pTime->m_pScore[nCnt]->Create(D3DXVECTOR3(1080.0f + nCnt* 30.0f,70.0f,0.0f));
		}
	}
	return pTime;
}