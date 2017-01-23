#include "../dxlib/dx_lib.h"
#include "GameFunc.h"

#pragma comment(lib, "winmm.lib")

#define TITLE		TEXT("3D_TASK")

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	// メモリリーク検出
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	MSG msg;
	HWND hWnd;

	InitWnd(&msg, &hWnd, hInstance, TITLE, WINDOW_WIDTH, WINDOW_HIGHT);

	//	DirectX の初期化
	InitDirect3D(hWnd);
	Init_Dinput();
	Init_Dinput_Key(hWnd);
	Init_Tex();
	pD3Device->SetRenderState(D3DRS_ZENABLE, TRUE);				// Zバッファ処理を有効にする

	GameFunc* pGameFunc = new GameFunc();


	DWORD SyncOld = timeGetTime();
	DWORD SyncNow;

	timeBeginPeriod(1);
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		Sleep(1);
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			SyncNow = timeGetTime();
			if (SyncNow - SyncOld >= 1000 / 60)
			{
				pGameFunc->Run();

				SyncOld = SyncNow;
			}
		}
	}
	timeEndPeriod(1);

	pGameFunc->FreeDx();
	delete pGameFunc;
	return 0;
}
