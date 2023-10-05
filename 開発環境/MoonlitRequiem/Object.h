//=========================================================================================================
//
//ポリゴンの共有処理
//Author:堀川萩大
//
//=========================================================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "main.h"

#define NUM_POLYGON (2048)
#define NUM_PRIORITY (8)

class CObject
{
public:

	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_PLAYER,
		TYPE_BG,
		TYPE_BGS,
		TYPE_BULLET,
		TYPE_EXPLOSION,
		TYPE_ENEMY,
		TYPE_EFFECT,
		TYPE_NUMBER,
		TYPE_BLOCK,
		TYPE_ITEM,
		TYPE_FIELD,
		TYPE_CYLINDER,
		TYPE_SNOWWALL,
		TYPE_3DBLOCK,
		TYPE_GUAGE,
		TYPE_SCENE,
		TYPE_FADE,
		TYPE_BOSS,
		TYPE_MAX
	}TYPE;

	CObject(int nPriority = 3);		//コンストラクタ
	virtual ~CObject();				//デストラクタ
	virtual HRESULT Init(void) = 0;	//初期化処理
	virtual void Uninit(void) = 0;	//終了処理
	virtual void Update(void) = 0;	//更新処理
	virtual void Draw(void) = 0;	//描画処理

	virtual void SetPos(D3DXVECTOR3 pos, float Height, float Width) = 0;
	virtual D3DXVECTOR3 GetPos(void) = 0;
	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);
	void Release(void);
	void SetType(TYPE type) { m_type = type; };
	TYPE GetType(void) { return m_type; };
	static CObject *GetObject(int nPriority,int nIdx) {return m_apObject[nPriority][nIdx];};
	static void Reset(void);
	int m_TexId;

protected:

private:
	static CObject *m_apObject[NUM_PRIORITY][NUM_POLYGON];
	static int m_nNumAll;
	int m_nID;
	TYPE m_type;
	int m_nPriority;
};

#endif