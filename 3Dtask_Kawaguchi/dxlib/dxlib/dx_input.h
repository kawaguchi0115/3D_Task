/**	@file	dx_input.h
	@brief	DirectInput�֐�

	@author	��� �D��Y
*/

#ifndef DX_INPUT
#define DX_INPUT

#include<dinput.h>
#include"dx_Init.h"

//!	@brief	�L�[�̏��
enum KEYSTATE
{
	ON,				//!<	�L�[��������Ă�����
	OFF,			//!<	�L�[��������Ă�����
	PUSH,			//!<	�L�[���������u��
	RELEASE			//!<	�L�[�𗣂����u��

};

//!	@brief	�L�[�̎��
enum KEYKIND
{
	ESC,
	F1,
	F2,
	F3,
	F4,
	F5,
	F6,
	F7,
	F8,
	F9,
	F10,
	F11,
	F12,

	_1,
	_2,
	_3,
	_4,
	_5,
	_6,
	_7,
	_8,
	_9,
	_0,
	BACK,

	TAB,
	Q,
	W,
	E,
	R,
	T,
	Y,
	U,
	I,
	O,
	P,
	RETURN,			//!<	ENTER

	A,
	S,
	D,
	F,
	G,
	H,
	J,
	K,
	L,

	LSHIFT,
	Z,
	X,
	C,
	V,
	B,
	N,
	M,
	RSHIFT,

	LCTRL,
	LALT,
	SPACE,
	RALT,
	RCTRL,

	UP,
	DOWN,
	LEFT,
	RIGHT,

	PGUP,
	PGDN,

	SHIFT,			//!<	���E����Ȃ�
	ALT,			//!<	���E����Ȃ�

	KEY_MAX			//!<	�L�[�̐�
};

#endif

//--------------------------------------------------------------------
//
/**	@brief	�_�C���N�g�C���v�b�g�̏������֐�

		main�֐����ň�x�Ăяo�������ł���

	@retval	S_OK	����
	@retval	hr		�n���h����Ԃ�
*/
//
//--------------------------------------------------------------------
HRESULT Init_Dinput();

//--------------------------------------------------------------------
//
/**	@brief	�L�[�{�[�h�̏�����

		main�֐����ň�x�Ăяo�������ł���

	@param[in]		hWnd	�E�B���h�E�̃n���h��

	@retval	S_OK	����
	@retval	hr		�n���h����Ԃ�
*/
//--------------------------------------------------------------------
HRESULT Init_Dinput_Key(HWND hWnd);


//-------------------------------------------------------------------------
//
/**	@brief	�L�[�{�[�h�̏�Ԃ��擾����֐�

	@attention	DirectX�̐�p���z�L�[									<br>
				dinput.h�@2032�`2175�s�@�Q��							<br>
					��	�K���� DIK_1 �Ɠ��͂��� F12 �Ŕ�ׂ�

	@param[out]		key		�L�[�{�[�h�̏�Ԃ��i�[����ϐ��̃|�C���^
	@param[in]		DIK		DirectX�̐�p���z�L�[

	@return		�Ȃ�
*/
//-------------------------------------------------------------------------
void KeyCheck(KEYSTATE* Key, int DIK);