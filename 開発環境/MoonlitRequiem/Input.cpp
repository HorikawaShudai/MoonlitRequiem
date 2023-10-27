//===========================================================
//
//入力の処理操作
//Author:堀川萩大
//
//===========================================================
#include "Input.h"


//=============================================基本クラス=============================================
//============================================================
//静的メンバ変数
//============================================================
LPDIRECTINPUT8 CInput::m_pInput = NULL;
LPDIRECTINPUT8 CInput:: m_pMouse = NULL;

//============================================================
//コンストラクタ
//============================================================
CInput :: CInput()
{
	m_pDevice = NULL;
	m_pDIMouse = NULL;
}
//============================================================
//デストラクタ
//============================================================
CInput :: ~CInput()
{

}

//============================================================
//初期化処理
//============================================================
HRESULT CInput:: Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
			IID_IDirectInput8,
			(void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}
	if (m_pMouse == NULL)
	{
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
			IID_IDirectInput8,
			(void**)&m_pMouse, NULL)))
		{
			return E_FAIL;
		}
	}
	return S_OK;
}

//============================================================
//終了処理
//============================================================
void  CInput::Uninit(void)
{
	//入力デバイス(キーボード)の破棄
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}
	if (m_pDIMouse != NULL)
	{
		m_pDIMouse->Unacquire();
		m_pDIMouse->Release();
		m_pDIMouse = NULL;
	}

	//DirectInputオブジェクトの破棄
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
	if (m_pMouse != NULL)
	{
		m_pMouse->Release();
		m_pMouse = NULL;
	}
}

//=============================================派生クラス=============================================
//============================================================
//コンストラクタ
//============================================================
CInputKeyboard::CInputKeyboard()
{
	ZeroMemory(&m_aKeyState, sizeof(BYTE));
}
//============================================================
//デストラクタ
//============================================================
CInputKeyboard::~CInputKeyboard()
{

}

//============================================================
//キーボードの初期化処理
//============================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);


	//Directオブジェクトの生成

	//入力デバイスの設定
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	//データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
	{
		return E_FAIL;
	}
	//キーボードへのアクセス権を獲得
	m_pDevice->Acquire();
	return S_OK;
}

//============================================================
//キーボードの終了処理
//============================================================
void CInputKeyboard::Uninit(void)
{

}

//============================================================
//キーボードの更新処理
//============================================================
void CInputKeyboard :: Update(void) 
{
	BYTE aKeyState[NUM_KEY_MAX];
	int nCntKey;

	//入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			m_aKeyState[nCntKey] = aKeyState[nCntKey];
		}
	}
	else
	{
		m_pDevice->Acquire();
	}
}

//============================================================
//入力情報の取得
//============================================================
bool CInputKeyboard ::GetPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}
bool CInputKeyboard::GetTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//============================================================
//ゲームパッド
//============================================================
#if 1
void CInputGamePad::Uninit(void)
{
	XInputEnable(false);
}
void CInputGamePad::Update(void)
{

	ZeroMemory(&m_aGamePadState, sizeof(XINPUT_STATE));

	// Simply get the state of the controller from XInput.
	DWORD dwResult = XInputGetState(0, &m_aGamePadState);

	//ゲームパッドが接続されている状態
	if (dwResult == ERROR_SUCCESS)
	{

	}
	else
	{
		int nData = 0;
	}
}

bool CInputGamePad::GetPress(WORD nButton)
{
	return (m_aGamePadState.Gamepad.wButtons & nButton) ? true : false;

}

bool CInputGamePad::GetTrigger(WORD nButton)
{
	return (nButton & 0x80) ? true : false;
}
#endif

CInputMouse::CInputMouse()
{
	ZeroMemory(&m_zdiMouseState, sizeof(DIMOUSESTATE));
}
CInputMouse::~CInputMouse()
{

}
HRESULT CInputMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	// マウス用にデバイスオブジェクトを作成
	if(FAILED( m_pInput->CreateDevice(GUID_SysMouse, &m_pDIMouse, NULL)))
	{
		return E_FAIL;
	}

	// データフォーマットを設定
	if (FAILED(m_pDIMouse->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;

	}

	// モードを設定（フォアグラウンド＆非排他モード）
	if (FAILED(m_pDIMouse->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
	{
		// エラーハンドリング
		return 1;
	}

	// デバイスの設定
	m_diprop.diph.dwSize = sizeof(m_diprop);
	m_diprop.diph.dwHeaderSize = sizeof(m_diprop.diph);
	m_diprop.diph.dwObj = 0;
	m_diprop.diph.dwHow = DIPH_DEVICE;
	m_diprop.dwData = DIPROPAXISMODE_REL;	// 相対値モードで設定（絶対値はDIPROPAXISMODE_ABS）

	if (FAILED (m_pDIMouse->SetProperty(DIPROP_AXISMODE, &m_diprop.diph)))
	{
		return E_FAIL;

	}

	// 入力制御開始
	m_pDIMouse->Acquire();

	return true;
}
void CInputMouse::Uninit(void)
{
	if (m_pInput != NULL) 
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}
void CInputMouse::Update(void)
{

	DIMOUSESTATE m_zdiMouseState_bak;	// マウス情報(変化検知用)
	m_pDIMouse->Poll();
	if (SUCCEEDED (m_pDIMouse->GetDeviceState(sizeof(DIMOUSESTATE), &m_zdiMouseState_bak)))
	{
		for (int nCnt = 0; nCnt < MAX_CLLICK; nCnt++)
		{
			m_zdiMouseStateTrigger.rgbButtons[nCnt] = (m_zdiMouseState.rgbButtons[nCnt] ^ m_zdiMouseState_bak.rgbButtons[nCnt]) & m_zdiMouseState_bak.rgbButtons[nCnt];

			m_zdiMouseState.rgbButtons[nCnt] = m_zdiMouseState_bak.rgbButtons[nCnt];

		}
	}
	else
	{
		m_pDIMouse->Acquire();
	}
}
bool CInputMouse::GetPress(int nKey)
{
	return (m_zdiMouseState.rgbButtons[nKey] & 0x80) ? true : false;
}
bool CInputMouse::GetTrigger(int nKey)
{
	return (m_zdiMouseStateTrigger.rgbButtons[nKey] & 0x80) ? true : false;
}