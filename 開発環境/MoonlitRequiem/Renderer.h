//=========================================================================================================
//
//�����_���[�̏���
//Author:�x�씋��
//
//=========================================================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "main.h"


class CRenderer
{
public:
	CRenderer();							//�R���X�g���N�^
	~CRenderer();							//�f�X�g���N�^
	HRESULT Init(HWND hWd, BOOL hWinfow);	//����������
	void Uninit(void);						//�I������
	void Update(void);						//�X�V����
	void Draw(void);						//�`�揈��
	LPDIRECT3DDEVICE9 GetDevice(void);		//�f�o�C�X�擾����

private:

	LPDIRECT3D9 m_pD3D;
	LPDIRECT3DDEVICE9 m_pD3DDevice;
};

#endif