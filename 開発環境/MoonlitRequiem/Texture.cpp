//===========================================================
//
//playerの処理操作
//Author:堀川萩大
//
//===========================================================
#include "Texture.h"
#include "Manager.h"
#include "Renderer.h"


CTexture::TEXINFO CTexture::m_aTexInfo[TEX_MAX] =
{
	{ "data\\TEXTURE\\player001.png" },
    { "data\\TEXTURE\\tuti001.jpg" }
};


CTexture::CTexture()
{

}
CTexture::~CTexture()
{

}

//====================================================
//テクスチャ読み込み処理
//====================================================
HRESULT CTexture::Load()
{

	CRenderer *pRenderer = CManager::GetRenderer();
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	for (int nCntTex = 0; nCntTex < TEX_MAX; nCntTex++)
	{
		for (int nCnt = 0; nCnt < 50; nCnt++)
		{
			if (m_pTexture[nCnt] == NULL)
			{
				//テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice, m_aTexInfo[nCntTex].pFilename, &m_pTexture[nCnt]);
				break;
			}
		}
	}
	return S_OK;
}

//====================================================
//テクスチャの破棄
//====================================================
void CTexture::Unload()
{
	for (int nCnt = 0; nCnt < 50; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}

//====================================================
//テクスチャ番号を取得
//====================================================
int CTexture::Regist(const char *pFilename)
{
	for (int nCnt = 0; nCnt < TEX_MAX; nCnt++)
	{
			if (m_aTexInfo[nCnt].pFilename == pFilename)
			{
				return nCnt;
			}
	}
	return 0;
}
//====================================================
//テクスチャアドレス取得
//====================================================
LPDIRECT3DTEXTURE9 CTexture::GetAddress(int nIdx)
{
	return m_pTexture[nIdx];
}