/**	@file	dx_input.cpp
	@brief	DirectInput関数

	@author	川口 颯一郎
*/

#include"dx_input.h"


LPDIRECTINPUT8 pDinput = NULL;
LPDIRECTINPUTDEVICE8 pKeyDevice = NULL;

//--------------------------------------------------
//
//	ダイレクトインプットの初期化関数
//
//--------------------------------------------------
HRESULT Init_Dinput()
{
	HRESULT hr;

	//	DirectInput オブジェクトの作成
	if (FAILED(hr = DirectInput8Create(GetModuleHandle(NULL),
		DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDinput, NULL)))
	{
		return hr;
	}

	return S_OK;
}

//-------------------------------------------------
//
//	キーボード初期化
//	引数はウィンドウのハンドル
//
//-------------------------------------------------
HRESULT Init_Dinput_Key(HWND hWnd)
{
	HRESULT hr;

	//	キーボードの初期化
	if (FAILED(hr = pDinput->CreateDevice(GUID_SysKeyboard,
		&pKeyDevice, NULL)))
	{
		return hr;
	}

	//	データフォーマット
	if (FAILED(hr = pKeyDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return hr;
	}

	//	協調レベル
	if (FAILED(hr = pKeyDevice->SetCooperativeLevel(
		hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
	{
		return hr;
	}

	pKeyDevice->Acquire();
	return S_OK;
}

//-------------------------------------------------------------------------
//
//	キーボードの状態を取得
//	1 : キーボードの状態を格納する変数のポインタ
//	2 : ダイレクトXの専用仮想キー　　-->> dinput.h 2032～2175行　参照
//
//-------------------------------------------------------------------------
void KeyCheck(KEYSTATE* Key, int DIK)
{
	HRESULT hr = pKeyDevice->Acquire();

	if ((hr == DI_OK) || (hr == S_FALSE))
	{
		BYTE diks[256];
		static BYTE KeyDiks[256] = { OFF };

		pKeyDevice->GetDeviceState(sizeof(diks), &diks);

		if (diks[DIK] & 0x80)				//	キーが押されているかの判定
		{
			if (KeyDiks[DIK] == OFF)
			{
				*Key = PUSH;
			}
			else
			{
				*Key = ON;
			}
			KeyDiks[DIK] = ON;
		}
		else
		{
			if (KeyDiks[DIK] == ON)
			{
				*Key = RELEASE;
			}
			else
			{
				*Key = OFF;
			}
			KeyDiks[DIK] = OFF;
		}
	}
}