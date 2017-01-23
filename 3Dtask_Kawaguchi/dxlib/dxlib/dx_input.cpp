/**	@file	dx_input.cpp
	@brief	DirectInput�֐�

	@author	��� �D��Y
*/

#include"dx_input.h"


LPDIRECTINPUT8 pDinput = NULL;
LPDIRECTINPUTDEVICE8 pKeyDevice = NULL;

//--------------------------------------------------
//
//	�_�C���N�g�C���v�b�g�̏������֐�
//
//--------------------------------------------------
HRESULT Init_Dinput()
{
	HRESULT hr;

	//	DirectInput �I�u�W�F�N�g�̍쐬
	if (FAILED(hr = DirectInput8Create(GetModuleHandle(NULL),
		DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDinput, NULL)))
	{
		return hr;
	}

	return S_OK;
}

//-------------------------------------------------
//
//	�L�[�{�[�h������
//	�����̓E�B���h�E�̃n���h��
//
//-------------------------------------------------
HRESULT Init_Dinput_Key(HWND hWnd)
{
	HRESULT hr;

	//	�L�[�{�[�h�̏�����
	if (FAILED(hr = pDinput->CreateDevice(GUID_SysKeyboard,
		&pKeyDevice, NULL)))
	{
		return hr;
	}

	//	�f�[�^�t�H�[�}�b�g
	if (FAILED(hr = pKeyDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return hr;
	}

	//	�������x��
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
//	�L�[�{�[�h�̏�Ԃ��擾
//	1 : �L�[�{�[�h�̏�Ԃ��i�[����ϐ��̃|�C���^
//	2 : �_�C���N�gX�̐�p���z�L�[�@�@-->> dinput.h 2032�`2175�s�@�Q��
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

		if (diks[DIK] & 0x80)				//	�L�[��������Ă��邩�̔���
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