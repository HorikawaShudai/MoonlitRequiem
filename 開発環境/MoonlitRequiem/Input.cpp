//===========================================================
//
//���͂̏�������
//Author:�x�씋��
//
//===========================================================
#include "Input.h"


//=============================================��{�N���X=============================================
//============================================================
//�ÓI�����o�ϐ�
//============================================================
LPDIRECTINPUT8 CInput::m_pInput = NULL;
LPDIRECTINPUT8 CInput:: m_pMouse = NULL;

//============================================================
//�R���X�g���N�^
//============================================================
CInput :: CInput()
{
	m_pDevice = NULL;
	m_pDIMouse = NULL;
}
//============================================================
//�f�X�g���N�^
//============================================================
CInput :: ~CInput()
{

}

//============================================================
//����������
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
//�I������
//============================================================
void  CInput::Uninit(void)
{
	//���̓f�o�C�X(�L�[�{�[�h)�̔j��
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

	//DirectInput�I�u�W�F�N�g�̔j��
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

//=============================================�h���N���X=============================================
//============================================================
//�R���X�g���N�^
//============================================================
CInputKeyboard::CInputKeyboard()
{
	ZeroMemory(&m_aKeyState, sizeof(BYTE));
}
//============================================================
//�f�X�g���N�^
//============================================================
CInputKeyboard::~CInputKeyboard()
{

}

//============================================================
//�L�[�{�[�h�̏���������
//============================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);


	//Direct�I�u�W�F�N�g�̐���

	//���̓f�o�C�X�̐ݒ�
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//�������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
	{
		return E_FAIL;
	}
	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	m_pDevice->Acquire();
	return S_OK;
}

//============================================================
//�L�[�{�[�h�̏I������
//============================================================
void CInputKeyboard::Uninit(void)
{

}

//============================================================
//�L�[�{�[�h�̍X�V����
//============================================================
void CInputKeyboard :: Update(void) 
{
	BYTE aKeyState[NUM_KEY_MAX];
	int nCntKey;

	//���̓f�o�C�X����f�[�^���擾
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
//���͏��̎擾
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
//�Q�[���p�b�h
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

	//�Q�[���p�b�h���ڑ�����Ă�����
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

	// �}�E�X�p�Ƀf�o�C�X�I�u�W�F�N�g���쐬
	if(FAILED( m_pInput->CreateDevice(GUID_SysMouse, &m_pDIMouse, NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDIMouse->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;

	}

	// ���[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	if (FAILED(m_pDIMouse->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
	{
		// �G���[�n���h�����O
		return 1;
	}

	// �f�o�C�X�̐ݒ�
	m_diprop.diph.dwSize = sizeof(m_diprop);
	m_diprop.diph.dwHeaderSize = sizeof(m_diprop.diph);
	m_diprop.diph.dwObj = 0;
	m_diprop.diph.dwHow = DIPH_DEVICE;
	m_diprop.dwData = DIPROPAXISMODE_REL;	// ���Βl���[�h�Őݒ�i��Βl��DIPROPAXISMODE_ABS�j

	if (FAILED (m_pDIMouse->SetProperty(DIPROP_AXISMODE, &m_diprop.diph)))
	{
		return E_FAIL;

	}

	// ���͐���J�n
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

	DIMOUSESTATE m_zdiMouseState_bak;	// �}�E�X���(�ω����m�p)
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