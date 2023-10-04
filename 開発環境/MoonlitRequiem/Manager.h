//=========================================================================================================
//
//ÉåÉìÉ_ÉâÅ[ÇÃèàóù
//Author:ñxêÏîãëÂ
//
//=========================================================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"
#include "Input.h"
//#include "Camera.h"
//#include "Object2D.h"
//#include "Light.h"
//#include "Field.h"
//#include "Texture.h"
//#include "3DPlayer.h"


class CManager
{
public:
	CManager();
	~CManager();

	HRESULT Init(HINSTANCE hInstance ,HWND hWd, BOOL hWinfow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CRenderer *GetRenderer(void);
	//static CCamera *GetCamera(void);
	static CInputKeyboard *GetInputKeyboard(void);
	//static CTexture *GetpTexture(void);
	//static CPlayer3D *GetPlayer(void);
	static LPDIRECT3DTEXTURE9 m_aTextureBg;
	static LPDIRECT3DTEXTURE9 m_aTexturePlayer;
	static LPDIRECT3DTEXTURE9 m_aTextureEnemy;

private:
	static CRenderer *m_pRenderer;
	static CInputKeyboard *m_pInputKeyboard;
	//static CLight   *m_pLight;
	//static CCamera  *m_pCamera;
	//static CField  *m_pField;
	//static CTexture  *m_pTexture;
	//static CPlayer3D *m_pPlayer3D;
};

#endif