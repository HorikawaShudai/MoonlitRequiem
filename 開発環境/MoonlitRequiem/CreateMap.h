//=============================================================
//
//csvmap�̏���
//Autor:�x�씋��
//
//=============================================================
#ifndef _CSVMAP_H_
#define _CSVMAP_H_
#include "main.h"

//�}�N����`
#define MAX_HEIGHT (100)
#define MAX_WHIGHT (100)

class CCsvMap
{
public:
	//�񋓌^�̃f�[�^�錾
	typedef enum
	{
		MAP_NONE = 0,	//��C
		MAP_FLORE,		//��
		MAP_MAX,
	}MAP_KIND; 
	//�v���g�^�C�v�錾
	static void LoadMap(void);
	static void CreateMap(void);
private:
	typedef struct
	{
		int mapData[MAX_WHIGHT][MAX_HEIGHT];
		int nHeight;
		int nWhight;
	}DATA;
	static DATA m_MapData;
};
#endif