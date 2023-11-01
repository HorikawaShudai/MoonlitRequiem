//=========================================================================================================
//
//2D��p�̃|���S���̏���
//Author:�x�씋��
//
//=========================================================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"
#include "Object2D.h"

//�}�N����`
#define NUM_PLACE (6) //�X�R�A�̍ő吔
class CNumber :public CObject2D
{
public:
	CNumber(int nPriority = 7);
	~CNumber();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void UnLoad(void);
	void Create(D3DXVECTOR3 pos);
	static LPDIRECT3DTEXTURE9 m_pTexture;
	static CNumber *m_pScore[NUM_PLACE];
	int m_TexNum;

private:
	static D3DXVECTOR3 m_pos;
};

class CTime : public CNumber
{
public:
	CTime();
	~CTime();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CTime *Create(void);
	static void SetScore(int nTime);
	static void AddScore(int nTime);

private:
	static D3DXVECTOR3 m_pos;
	static int m_Time;
};
#endif