//===========================================================
//
//フェードの処理操作
//Author:堀川萩大
//
//===========================================================
#include "fade.h"
#include "main.h"
#include "game.h"
#include "Renderer.h"
//#include "sound.h"


CFade::CFade()
{

}
CFade::~CFade()
{

}
//=========================================================================================================
//フェードの初期化処理
//=========================================================================================================
HRESULT CFade::Init(void)
{
	

	m_Fade = FADE_NONE;
	m_ColorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();


	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffFade,
		NULL);

	VERTEX_2D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	m_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

	//頂点バッファをアンロックする
	m_pVtxBuffFade->Unlock();
	return S_OK;
}

//=========================================================================================================
//フェードの終了処理
//=========================================================================================================
void CFade::Uninit(void)
{
	if (m_pVtxBuffFade != NULL)
	{
		m_pVtxBuffFade->Release();
		m_pVtxBuffFade = NULL;
	}
}

//フェードの更新処理
void CFade::Update(void)
{
	if (m_Fade != FADE_NONE)
	{
		if (m_Fade == FADE_IN)
		{
			m_ColorFade.a -= 0.5f;
			if (m_ColorFade.a <= 0.0f)
			{
				m_ColorFade.a = 0.0f;
				m_Fade = FADE_NONE;
			}
		}
		else if (m_Fade == FADE_OUT)
		{
			m_ColorFade.a += 0.5f;
			if (m_ColorFade.a >= 1.0f)
			{
				m_ColorFade.a = 1.0f;
				m_Fade = FADE_IN;
				CManager::GetInstance()->SetMode(m_ModeNext);
			}
		}

		VERTEX_2D *pVtx;
		//頂点バッファをロックし頂点情報へのポインタを取得
		m_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);
		//頂点カラーの設定
		pVtx[0].col = m_ColorFade;
		pVtx[1].col = m_ColorFade;
		pVtx[2].col = m_ColorFade;
		pVtx[3].col = m_ColorFade;
		//頂点バッファをアンロックする
		m_pVtxBuffFade->Unlock();
	
	}
}

//=========================================================================================================
//フェードの描画処理
//=========================================================================================================
void CFade::Draw(void)
{
	CManager Renderer;
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();


	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetTexture(0, NULL);

	//ポリゴン
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

void CFade::SetFade(CScene::MODE ModeNext, float Fade)
{
	m_Fade = FADE_OUT;
	m_FadeCount = Fade;
	m_ModeNext = ModeNext;
	m_ColorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

CFade::FADE CFade::GetFade(void)
{
	return m_Fade;
}

CFade *CFade::Create(void)
{
	CFade *pObject = NULL;

	pObject = new CFade;
	pObject->Init();

	return pObject;
}