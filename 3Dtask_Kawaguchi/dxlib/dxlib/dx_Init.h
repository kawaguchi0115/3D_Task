/**	@file	dx_Init.h
	@brief	DirectX �̏������֐�

	@author	��� �D��Y
*/

#include<d3dx9.h>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")


//-------------------------------------------------------
//
/**	@brief	����֐��Ɏg�p����֐�

		���g�p�၄							<br>
		void FreeDx()						<br>
		{									<br>
			SAFE_RELEASE(pTexture);			<br>
					�E						<br>
					�E						<br>
					�E						<br>
		}
*/
//-------------------------------------------------------
# define SAFE_RELEASE(p) {if(p){(p)->Release(); (p)=NULL;}}


extern IDirect3D9*			  pDirect3D;				//!<	�C���^�[�t�F�C�X�ւ̃|�C���^
extern IDirect3DDevice9*	  pD3Device;				//!<	�f�o�C�X�ւ̃|�C���^
extern D3DPRESENT_PARAMETERS  D3dPresentParameters;		//!<	����������̂ŏڂ�����MSDS�ց� https://msdn.microsoft.com/ja-jp/library/cc323931.aspx
extern D3DDISPLAYMODE		  D3DdisplayMode;			//!<	�f�B�X�v���C���[�h���������邽�߂̂���


/**	@brief	DirectX �̏������֐�

		main�֐����ň�x�Ăяo�������ł���

	@attention		(42�s��) �t���X�N���[���ɂ������ꍇ�� false

	@note	MassageBox -> https://msdn.microsoft.com/ja-jp/library/cc410914.aspx
	@note	GetAdapterMode�@-> https://msdn.microsoft.com/ja-jp/library/cc324298.aspx

	@param[in]		hWnd	�E�B���h�E�̃n���h��

	@retval		S_OK	����
	@retval		E_FAIL	�G���[

*/

HRESULT InitDirect3D(HWND hWnd);