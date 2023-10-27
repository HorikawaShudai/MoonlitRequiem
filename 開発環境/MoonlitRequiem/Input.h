//=========================================================================================================
//
//���͏���
//Author:�x�씋��
//
//=========================================================================================================
#ifndef _INPUT_H_
#define _INPUT_H_
#include "main.h"
#include "Xinput.h"
#pragma comment (lib, "xinput.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")

#define DIRECTINPUT_VERSION (0x0800) //�r���h���̌x���Ώ��p�r���h
#include "dinput.h"

//�}�N����`
#define NUM_KEY_MAX (256)		//�L�[�̍ő吔
#define NUM_MOUSE_MAX (4)

class CInput
{
public:
	CInput();
	virtual ~CInput();
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;

protected:
	static LPDIRECTINPUT8 m_pInput;
	static LPDIRECTINPUT8 m_pMouse;
	LPDIRECTINPUTDEVICE8 m_pDevice;
	LPDIRECTINPUTDEVICE8 m_pDIMouse;

private:
};


class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);

private:
	BYTE m_aKeyState[256];
	BYTE m_aKeyStateTrigger[256];
};

class CInputGamePad : public CInput
{
public:
	CInputGamePad();
	~CInputGamePad();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(WORD nButton);
	bool GetTrigger(WORD nButton);

private:
	XINPUT_STATE m_aGamePadState;
	XINPUT_STATE m_aKeyStateTrigger;
};

class CInputMouse : public CInput
{
public:
	typedef enum
	{
		LEFT_CLLICK = 0,
		RIGHT_CLLICK,
		WHEEL_CLLICK,
		MAX_CLLICK
	}TYPE_CLLICK;
	CInputMouse();
	~CInputMouse();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);

private:
	DIPROPDWORD m_diprop;
	BOOL m_bAppActive = FALSE;
	DIMOUSESTATE m_zdiMouseState;
	DIMOUSESTATE m_zdiMouseStateTrigger;

};
#endif