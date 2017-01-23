/**	@file	wndfunc.h
	@brief	windows 関数

	@author	川口 颯一郎
*/

#include <windows.h>


/**	@brief	描画するテキストのフォントの初期化
	
	@param[in]		Title	タイトル
	@param[in]		hight	ウィンドウの高さ
	@param[in]		width	ウィンドウの幅
*/

HRESULT InitWnd(MSG* msg, HWND* hWnd, HINSTANCE hInstance, char Title[256], int width, int hight);
