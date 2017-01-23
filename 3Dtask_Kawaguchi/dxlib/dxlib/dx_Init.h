/**	@file	dx_Init.h
	@brief	DirectX の初期化関数

	@author	川口 颯一郎
*/

#include<d3dx9.h>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")


//-------------------------------------------------------
//
/**	@brief	解放関数に使用する関数

		＜使用例＞							<br>
		void FreeDx()						<br>
		{									<br>
			SAFE_RELEASE(pTexture);			<br>
					・						<br>
					・						<br>
					・						<br>
		}
*/
//-------------------------------------------------------
# define SAFE_RELEASE(p) {if(p){(p)->Release(); (p)=NULL;}}


extern IDirect3D9*			  pDirect3D;				//!<	インターフェイスへのポインタ
extern IDirect3DDevice9*	  pD3Device;				//!<	デバイスへのポインタ
extern D3DPRESENT_PARAMETERS  D3dPresentParameters;		//!<	説明が難しいので詳しくはMSDSへ→ https://msdn.microsoft.com/ja-jp/library/cc323931.aspx
extern D3DDISPLAYMODE		  D3DdisplayMode;			//!<	ディスプレイモードを所得するためのもの


/**	@brief	DirectX の初期化関数

		main関数内で一度呼び出すだけでいい

	@attention		(42行目) フルスクリーンにしたい場合は false

	@note	MassageBox -> https://msdn.microsoft.com/ja-jp/library/cc410914.aspx
	@note	GetAdapterMode　-> https://msdn.microsoft.com/ja-jp/library/cc324298.aspx

	@param[in]		hWnd	ウィンドウのハンドル

	@retval		S_OK	成功
	@retval		E_FAIL	エラー

*/

HRESULT InitDirect3D(HWND hWnd);