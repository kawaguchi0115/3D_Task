/**	@file	dx_Init.cpp
	@brief	DirectX �̏������֐�

	@author	��� �D��Y
*/

#include"dx_Init.h"

IDirect3D9*			  pDirect3D;
IDirect3DDevice9*	  pD3Device;
D3DPRESENT_PARAMETERS D3dPresentParameters;
D3DDISPLAYMODE		  D3DdisplayMode;

HRESULT InitDirect3D (HWND hWnd)
{
	//	DirectX �I�u�W�F�N�g�쐬
	if (NULL == (pDirect3D = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		MessageBox(0, "Direct3D�̐����Ɏ��s���܂����B", NULL, MB_OK);		//	https://msdn.microsoft.com/ja-jp/library/cc410914.aspx
		return E_FAIL;														//	Windows �̃G���[�\��
	}

	// �f�o�C�X�̍쐬
	ZeroMemory(&D3dPresentParameters,
		sizeof(D3DPRESENT_PARAMETERS));
	
	pDirect3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &D3DdisplayMode);	//	https://msdn.microsoft.com/ja-jp/library/cc324298.aspx
	D3dPresentParameters.BackBufferFormat = D3DdisplayMode.Format;
	D3dPresentParameters.BackBufferCount = 1;
	D3dPresentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	D3dPresentParameters.Windowed = TRUE;									//	�t���X�N���[���ɂ������ꍇ�� false

	D3dPresentParameters.EnableAutoDepthStencil = TRUE;
	D3dPresentParameters.AutoDepthStencilFormat = D3DFMT_D24S8;			// Z�o�b�t�@24�r�b�g�A�X�e���V���o�b�t�@8�r�b�g �Ȃ̂�OK
	D3dPresentParameters.Flags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;	// �_�u���X�e���V��

	if (FAILED(pDirect3D->CreateDevice(D3DADAPTER_DEFAULT,
								D3DDEVTYPE_HAL,
								hWnd,
								D3DCREATE_SOFTWARE_VERTEXPROCESSING,
								&D3dPresentParameters, &pD3Device) ) )
	{
		MessageBox(0, "Direct3D �f�o�C�X�̍쐬�Ɏ��s���܂����B", NULL, MB_OK);
		return E_FAIL;
	}
	return S_OK;
}
