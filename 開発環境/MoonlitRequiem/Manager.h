//=========================================================================================================
//
//ÉåÉìÉ_ÉâÅ[ÇÃèàóù
//Author:ñxêÏîãëÂ
//
//=========================================================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"
#include "Object2D.h"
#include "Input.h"
#include "Texture.h"


class CScene
{
public:
	typedef enum
	{
		MODE_NONE = 0,
		MODE_TITLE,
		MODE_TUTORIAL,
		MODE_GAME,
		MODE_CLEAR,
		MODE_END,
		MODE_MAX
	}MODE;
	CScene();
	~CScene();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPos(D3DXVECTOR3 pos, float Height, float Width) {};
	D3DXVECTOR3 GetPos(void);
	static CScene *Create(CScene::MODE mode);
	MODE m_mode;
private:
};

class CManager
{
public:
	CManager();
	~CManager();

	HRESULT Init(HINSTANCE hInstance, HWND hWd, BOOL hWinfow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CRenderer *GetRenderer(void);
	static CInputKeyboard *GetInputKeyboard(void);
	static CTexture *GetpTexture(void);
	static CFade *GetpFade(void);
	static LPDIRECT3DTEXTURE9 m_aTextureBg;
	static void SetMode(CScene::MODE mode);
	static CScene::MODE GetMode(void);
private:
	static CRenderer *m_pRenderer;
	static CInputKeyboard *m_pInputKeyboard;
	static CTexture  *m_pTexture;
	static CScene *m_pScene;
	static CFade *m_pFade;

};





#endif