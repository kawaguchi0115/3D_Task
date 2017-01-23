/**	@file	wndfunc.cpp
@brief	windows 関数

@author	川口 颯一郎
*/


#include "wndfunc.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT mes, WPARAM wParam, LPARAM lParam)
{
	if (mes == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}

	switch ((CHAR)wParam)
	{
	case VK_ESCAPE:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, mes, wParam, lParam);
}


HRESULT InitWnd(MSG* msg, HWND* hWnd, HINSTANCE hInstance, char Title[256], int width, int hight)
{
	WNDCLASSEX wndc;
	//MSG msg;
	//HWND hWnd;
	//HINSTANCE hInstance;

	//	ウィンドウの初期化
	//
	//	http://gurigumi.s349.xrea.com/programming/visualcpp/index.html
	//
	wndc.cbSize = sizeof(wndc);
	wndc.style = CS_HREDRAW | CS_VREDRAW;
	wndc.lpfnWndProc = WndProc;
	wndc.cbClsExtra = 0;
	wndc.cbWndExtra = 0;
	wndc.hInstance = hInstance;
	wndc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndc.lpszMenuName = NULL;
	wndc.lpszClassName = Title;
	wndc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wndc)) return 0;

	*hWnd = CreateWindow(
		Title,
		Title,
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		width,
		hight,
		NULL,
		NULL,
		hInstance,
		NULL
		);


	RECT window_size, client_size;
	GetWindowRect(*hWnd, &window_size);
	GetClientRect(*hWnd, &client_size);

	int new_width = (window_size.right - window_size.left) - (client_size.right - client_size.left) + width;
	int new_height = (window_size.bottom - window_size.top) - (client_size.bottom - client_size.top) + hight;

	SetWindowPos(*hWnd, NULL, 0, 0, new_width, new_height, SWP_NOMOVE | SWP_NOZORDER);

	return 0;
}