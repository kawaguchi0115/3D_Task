/**	@file	dx_input.h
	@brief	DirectInput関数

	@author	川口 颯一郎
*/

#ifndef DX_INPUT
#define DX_INPUT

#include<dinput.h>
#include"dx_Init.h"

//!	@brief	キーの状態
enum KEYSTATE
{
	ON,				//!<	キーが押されている状態
	OFF,			//!<	キーが離されている状態
	PUSH,			//!<	キーを押した瞬間
	RELEASE			//!<	キーを離した瞬間

};

//!	@brief	キーの種類
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

	SHIFT,			//!<	左右を問わない
	ALT,			//!<	左右を問わない

	KEY_MAX			//!<	キーの数
};

#endif

//--------------------------------------------------------------------
//
/**	@brief	ダイレクトインプットの初期化関数

		main関数内で一度呼び出すだけでいい

	@retval	S_OK	成功
	@retval	hr		ハンドルを返す
*/
//
//--------------------------------------------------------------------
HRESULT Init_Dinput();

//--------------------------------------------------------------------
//
/**	@brief	キーボードの初期化

		main関数内で一度呼び出すだけでいい

	@param[in]		hWnd	ウィンドウのハンドル

	@retval	S_OK	成功
	@retval	hr		ハンドルを返す
*/
//--------------------------------------------------------------------
HRESULT Init_Dinput_Key(HWND hWnd);


//-------------------------------------------------------------------------
//
/**	@brief	キーボードの状態を取得する関数

	@attention	DirectXの専用仮想キー									<br>
				dinput.h　2032～2175行　参照							<br>
					→	適当に DIK_1 と入力して F12 で飛べる

	@param[out]		key		キーボードの状態を格納する変数のポインタ
	@param[in]		DIK		DirectXの専用仮想キー

	@return		なし
*/
//-------------------------------------------------------------------------
void KeyCheck(KEYSTATE* Key, int DIK);