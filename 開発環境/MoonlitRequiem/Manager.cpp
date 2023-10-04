//=========================================================================================================
//
//マネージャの処理
//Author:堀川萩大
//
//=========================================================================================================
#include "Manager.h"
#include "Renderer.h"
#include "Input.h"
#include "Object.h"
//#include "Bullet.h"
//#include "Explosion.h"
//#include "Textures.h"
//#include "Effect.h"
//#include "Enemy.h"
#include "Sound.h"
//#include "Score.h"
//#include "Block.h"
//#include "Item.h"
//#include "Model.h"
//#include "Billboard.h"

//====================================================
//静的メンバ変数の初期化
//====================================================
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
//CLight *CManager::m_pLight = NULL;
//CCamera *CManager::m_pCamera = NULL;
//CTexture *CManager::m_pTexture = NULL;
//CPlayer3D *CManager::m_pPlayer3D = NULL;
LPDIRECT3DTEXTURE9 CManager::m_aTextureBg = NULL;
LPDIRECT3DTEXTURE9 CManager::m_aTexturePlayer = NULL;
LPDIRECT3DTEXTURE9 CManager::m_aTextureEnemy = NULL;
//====================================================
//コンストラクタ
//====================================================
CManager::CManager()
{

}

//====================================================
//デストラクタ
//====================================================
CManager::~CManager()
{

}

//====================================================
//初期化処理
//====================================================
HRESULT CManager::Init(HINSTANCE hInstance ,HWND hWnd, BOOL bWindow)
{
	m_pRenderer = new CRenderer;
	m_pRenderer->Init(hWnd, TRUE);
	CSound::Init(hWnd);

	m_pInputKeyboard = new CInputKeyboard;
	m_pInputKeyboard->Init(hInstance, hWnd);

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = m_pRenderer->GetDevice();

	//m_pTexture = new CTexture;
	//m_pTexture->Load();

	////テクスチャの読み込み
	//D3DXCreateTextureFromFile(pDevice,
	//	"data\\TEXTURE\\player001.png",
	//	&m_aTexturePlayer);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\BG000.jpg",
		&m_aTextureBg);
	//CBullet::Load();
	//CExplosion::Load();
	//CEffect::Load();
	//CNumber::Load();
	//CBlock::Load();
	//CItem::Load();
	//CField::Load();

	////テクスチャの読み込み
	//D3DXCreateTextureFromFile(pDevice,
	//	"data\\TEXTURE\\enemy004.png",
	//	&m_aTextureEnemy);
	//CObject2D::Create(CObject::TYPE_BG);
	//CTextures::Create(CObject::TYPE_BGS);

	//m_pLight = new CLight;
	//m_pLight->Init();
	//m_pCamera = new CCamera;
	//m_pCamera->Init();
	//CBillboard::CreateBillboard();
	//CObject3D::Create(CObject::TYPE_FIELD);
	//CObject2D::Create(CObject::TYPE_PLAYER);
	//CEnemy::Create(D3DXVECTOR3(900.0f, 500.0f, 0.0f));
	//CItem::Create(D3DXVECTOR3(400.0f, 200.0f, 0.0f));
	//CItem::Create(D3DXVECTOR3(100.0f, 700.0f, 0.0f));
	//m_pPlayer3D = CPlayer3D::Create();

	//CScore::Create();
	//CScore::SetScore(0);
	CSound::Play(CSound::SOUND_LABEL_BGM001);
	return S_OK;
}

//====================================================
//終了処理
//====================================================
void CManager::Uninit(void)
{
	//すべてのオブジェクトを破棄
	CObject::ReleaseAll();
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		//delete m_pRenderer;
		m_pRenderer = NULL;
	}

	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();
		//delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	if (m_aTextureBg != NULL)
	{
		m_aTextureBg->Release();
		m_aTextureBg = NULL;

	}

	//if (m_pCamera != NULL)
	//{
	//	m_pCamera->Uninit();
	//	m_pCamera = NULL;

	//}
	//if (m_pLight != NULL)
	//{
	//	m_pLight->Uninit();
	//	m_pLight = NULL;

	//}
	//CField::UnLoad();
	if (m_aTextureEnemy != NULL)
	{
		m_aTextureEnemy->Release();
		m_aTextureEnemy = NULL;
	}
	CSound::StopSound();
	CSound::Uninit();
	//if (m_pTexture != NULL)
	//{
	//	m_pTexture->Unload();
	//	m_pTexture = NULL;

	//}
	//if (m_pPlayer3D != NULL)
	//{
	//	m_pPlayer3D = NULL;
	//}
}

//====================================================
//更新処理
//====================================================
void CManager::Update(void)
{
	m_pRenderer->Update();
	m_pInputKeyboard->Update();
	//m_pCamera->Update();
	//m_pPlayer3D->Update();
}

//====================================================
//描画処理
//====================================================
void CManager::Draw(void)
{
	m_pRenderer->Draw();
	//m_pPlayer3D->Draw();
}

//====================================================
//レンダラーの取得処理
//====================================================
CRenderer *CManager:: GetRenderer(void)
{
	return m_pRenderer;
}

//====================================================
//レンダラーの取得処理
//====================================================
CInputKeyboard *CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

//====================================================
//カメラの取得処理
//====================================================
//CCamera *CManager::GetCamera(void)
//{
//	return m_pCamera;
//}
//
//CTexture *CManager::GetpTexture(void)
//{
//	return m_pTexture;
//}
//CPlayer3D *CManager::GetPlayer(void)
//{
//	return m_pPlayer3D;
//}
