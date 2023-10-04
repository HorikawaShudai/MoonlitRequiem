#ifndef _MAIN_H_
#define _MAIN_H_

#include <windows.h>
#include "d3dx9.h"

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")	//システム時刻の取得
#include "xaudio2.h"


#define SCREEN_WIDTH			(1280)	 //ウィンドウサイズ（幅）
#define SCREEN_HEIGHT			(720)	 //ウィンドウサイズ（高さ）
#define FVF_VERTEX_2D (D3DFVF_XYZRHW |D3DFVF_DIFFUSE |D3DFVF_TEX1) //頂点フォーマット
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)

typedef struct
{
	D3DXVECTOR3 pos; //頂点座標	
	float rhw;		 //座標変換用係数(1.0fで固定)
	D3DCOLOR col;	 //頂点カラー
	D3DXVECTOR2 tex; //テクスチャ座標
}VERTEX_2D;

typedef struct
{
	D3DXVECTOR3 pos;		//頂点座標
	D3DXVECTOR3 nor;		//法線ベクトル
	D3DCOLOR col;			//頂点カラー
	D3DXVECTOR2 tex;		//テクスチャ座標
}VERTEX_3D;

//前方宣言
class  CRenderer;
class  CObject;
class  CInputKeyboard;
class CManager;
class CBullet;
//プロタイプ宣言
//CRenderer *GetRenderer(void);
//CObject  **GetObject(void);

#endif