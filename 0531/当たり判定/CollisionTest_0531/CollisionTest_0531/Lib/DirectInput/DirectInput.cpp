#include<dinput.h>
#include<d3d9.h>
#include"Main\Main.h"
#include"DirectInput.h"


LPDIRECTINPUT8 pDinput = NULL; //設定
LPDIRECTINPUTDEVICE8 pKeyDevice = NULL;		// キーデバイス.
LPDIRECTINPUTDEVICE8 g_pDIMouse = NULL;
DIMOUSESTATE g_zdiMouseState;

HRESULT InitDinput()
{
	HRESULT hr;

	//DirectInputオブジェクトの作成
	if (FAILED(hr = DirectInput8Create(GetModuleHandle(NULL),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,  //生成
		(VOID**)&pDinput,
		NULL)))
	{
		return hr;
	}

	return S_OK;
}

HRESULT InitDinputKey(HWND hWnd)
{
	HRESULT hr;

	if (FAILED(hr = pDinput->CreateDevice(
		GUID_SysKeyboard,
		&pKeyDevice,
		NULL)))
	{
		return hr;
	}

	if (FAILED(hr = pKeyDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return hr;
	}

	if (FAILED(hr = pKeyDevice->SetCooperativeLevel(
		hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
	{
		return hr;
	}

	pKeyDevice->Acquire();
	return S_OK;
}

void KeyCheckDinput(KEYSTATE* Key, int DIK)
{
	BYTE diks[256];
	static int old_diks[256] = { OFF };

	HRESULT hr = pKeyDevice->Acquire();
	if ((hr == DI_OK) || (hr == S_FALSE))
	{

		pKeyDevice->GetDeviceState(sizeof(diks), &diks);
		if (diks[DIK] & 0x80)
		{
			if (old_diks[DIK] == OFF)
			{
				*Key = PUSH;
			}
			else
			{
				*Key = ON;
			}

			old_diks[DIK] = ON;
		}
		else
		{
			if (old_diks[DIK] == ON)
			{
				*Key = RELEASE;
			}
			else
			{
				*Key = OFF;
			}
			old_diks[DIK] = OFF;
		}
	}
}

HRESULT InitDinputMouse(HWND hWnd)
{
	HRESULT hr;
	if (FAILED(hr = pDinput->CreateDevice(
		GUID_SysMouse,
		&g_pDIMouse,
		NULL)))
	{
		return hr;
	}

	if (FAILED(hr = g_pDIMouse->SetDataFormat(&c_dfDIMouse)))
	{
		return hr;
	}

	if (FAILED(hr = g_pDIMouse->SetCooperativeLevel(hWnd,
		DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
	{
		return hr;
	}

	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;

	if (FAILED(hr = g_pDIMouse->SetProperty(
		DIPROP_AXISMODE,
		&diprop.diph)))
	{
		return hr;
	}

	g_pDIMouse->Acquire();

	return S_OK;
}

void ReleaseDiput()
{
	SAFE_RELEASE(pDinput);
}

void ReleaseKey()
{
	if (pKeyDevice)
	{
		pKeyDevice->Unacquire();
	}
	SAFE_RELEASE(pKeyDevice);
}

void ReleaseMouse()
{
	if (g_pDIMouse)
	{
		g_pDIMouse->Unacquire();
	}
	SAFE_RELEASE(g_pDIMouse);
}