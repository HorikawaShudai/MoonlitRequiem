//=========================================================================================================
//
//レンダラーの処理
//Author:堀川萩大
//
//=========================================================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "main.h"


class CRenderer
{
public:
	CRenderer();							//コンストラクタ
	~CRenderer();							//デストラクタ
	HRESULT Init(HWND hWd, BOOL hWinfow);	//初期化処理
	void Uninit(void);						//終了処理
	void Update(void);						//更新処理
	void Draw(void);						//描画処理
	LPDIRECT3DDEVICE9 GetDevice(void);		//デバイス取得処理

private:

	LPDIRECT3D9 m_pD3D;
	LPDIRECT3DDEVICE9 m_pD3DDevice;
};

#endif