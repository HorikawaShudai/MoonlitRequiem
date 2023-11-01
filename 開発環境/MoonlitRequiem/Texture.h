//===========================================================
//
//playerÇÃèàóùëÄçÏ
//Author:ñxêÏîãëÂ
//
//===========================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_
#include "main.h"
#include "Object.h"

class CTexture
{
public:
	CTexture();
	~CTexture();
	typedef enum
	{
		TEX_NUM1 = 0,
		TEX_NUM2,
		TEX_NUM3,
		TEX_NUM4,
		TEX_NUM5,
		TEX_NUM6,
		TEX_NUM7,
		TEX_NUM8,
		TEX_NUM9,
		TEX_NUM10,
		TEX_NUM11,
		TEX_NUM12,
		TEX_MAX
	}TEXTURENUM;
	HRESULT Load();
	void Unload();
	int Regist(const char *pFilename);
	LPDIRECT3DTEXTURE9 GetAddress(int nIdx);
private:
	typedef struct
	{
		char *pFilename;	// ÉtÉ@ÉCÉãñº
	} TEXINFO;

	static TEXINFO m_aTexInfo[TEX_MAX];

	LPDIRECT3DTEXTURE9 m_pTexture[50] = {};
	static int m_nNumAll;
};
#endif
