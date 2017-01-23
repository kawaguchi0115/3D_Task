/**	@file	dx_tex.cpp
	@brief	DirectX Twxture�֐�

	@author	��� �D��Y
*/

#include"dx_tex.h"

ID3DXFont*	       pFont;

void Init_Tex()
{
	pD3Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);					//	�A���t�@�u�����h�ɂ�铧������L���ɂ���
	pD3Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);				//	�������u�����f�B���O�̐ݒ�
	pD3Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);			//	�����@�ƃZ�b�g
	pD3Device->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);		//	�f�B�q���[�Y�F�̐ݒ�

	pD3Device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	pD3Device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);		//	�f�B�q���[�Y�F�̐F�����̏�����L��������

	pD3Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);		//	�J���[�u�����f�B���O��������Z�ɂ���

	pD3Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pD3Device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);		//	�f�B�q���[�Y�F�̓��ߐF�����̏�����L��������

	pD3Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);		//	�A���t�@�u�����f�B���O�̏�������Z�ɂ���

}
//------------------------------------------------------------------------------
//
//	RoadTex(��P�����A��Q����)
//	��P���� : �摜�t�@�C�����@"name.xxx"
//	��Q���� : �i�[����ꏊ�ւ̃|�C���^�@&name or &name[NAME]
//
//------------------------------------------------------------------------------
HRESULT RoadTex(LPCTSTR pSrcFile, IDirect3DTexture9* pTexture[])
{
	if(FAILED (D3DXCreateTextureFromFile(pD3Device, pSrcFile, pTexture) ) )
	{
		MessageBox(0, "�摜�̓ǂݍ��݂Ɏ��s���܂����B", NULL, MB_OK);
		return E_FAIL;
	}
	return S_OK;
}

//----------------------------------------------------------------------
//
//	RoadTexEx(��P�����A��Q�����A��R����)
//	��P���� : �摜�t�@�C�����@"name.xxx"
//	��Q���� : �i�[����ꏊ�ւ̃|�C���^�@&name or &name[NAME]
//	��R�S�T���� : A,R,G,B 
//	��U�����摜�T�C�Y���Q�ׂ̂���łȂ���΁@false ��
//
//----------------------------------------------------------------------
HRESULT RoadTexEx(LPCTSTR pSrcFile, IDirect3DTexture9* pTexture[], int alpha, int red, int green, int blue, bool TexSize)
{
	if (TexSize)
	{
		if (FAILED(D3DXCreateTextureFromFileEx(
			pD3Device,			//	�C���^�[�t�F�C�X�ւ̃|�C���^
			pSrcFile,			//	�摜�t�@�C����
			D3DX_DEFAULT,	
			D3DX_DEFAULT,	
			D3DX_DEFAULT,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_DEFAULT,
			D3DX_FILTER_NONE,
			D3DX_DEFAULT,
			D3DCOLOR_ARGB(alpha, red, green, blue),
			NULL,
			NULL,
			pTexture
			)))
		{
			MessageBox(0, "�摜�̓ǂݍ��݂Ɏ��s���܂����B", NULL, MB_OK);
			return E_FAIL;
		}
	}
	else			//	2�ׂ̂���łȂ��ꍇ
	{
		if (FAILED(D3DXCreateTextureFromFileEx(
			pD3Device,			//	�C���^�[�t�F�C�X�ւ̃|�C���^
			pSrcFile,			//	�摜�t�@�C����
			D3DX_DEFAULT_NONPOW2,		
			D3DX_DEFAULT_NONPOW2,		
			D3DX_DEFAULT,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_DEFAULT,
			D3DX_FILTER_NONE,
			D3DX_DEFAULT,
			D3DCOLOR_ARGB(alpha, red, green, blue),
			NULL,
			NULL,
			pTexture
			)))
		{
			MessageBox(0, "�摜�̓ǂݍ��݂Ɏ��s���܂����B", NULL, MB_OK);
			return E_FAIL;
		}
	}
	return S_OK;
}
//-----------------------------------------------------------
//
//	�ݒ肵�� FVF ��n��
//
//-----------------------------------------------------------
void SetGameSceneStart(DWORD FVF)
{

	//	���_���̎w��
	pD3Device->SetFVF(FVF);

	//	��ʏ���
	pD3Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0x00, 0x00, 0x00), 1.0, 0);

	//	�`��J�n
	pD3Device->BeginScene();
}

void SetGameSceneStart3D(DWORD FVF)
{

	//	���_���̎w��
	pD3Device->SetFVF(FVF);

	//	��ʏ���
	pD3Device->Clear(0, NULL, D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0x00, 0x00, 0x00), 1.0, 0);

	//	�`��J�n
	pD3Device->BeginScene();
}

//----------------------------------------------------------------
//
//	1 : �p�ӂ����e�N�X�`�����i�[����z��ւ̃|�C���^
//	2 : �e�N�X�`���� CUSTOMVERTEX
//
//----------------------------------------------------------------

void SetGameScene(IDirect3DTexture9* pTexture, CUSTOMVERTEX TexVertex[])
{
	//	�摜�����蓖�Ă�
	pD3Device->SetTexture(0, pTexture);
	//	�`��
	pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, TexVertex, sizeof(CUSTOMVERTEX));

}

void SetGameSceneEnd()
{
	//	�`��I��
	pD3Device->EndScene();
	//	��ʂɕ\��
	pD3Device->Present(NULL, NULL, NULL, NULL);
}





//------------------------------------------------------------------------------------
//
//	�e�L�X�g�`��֐�
//
//------------------------------------------------------------------------------------

void Init_Txt(int hight, int width)
{
	D3DXCreateFont(
		pD3Device,
		hight,								//	�����̍���
		width,								//	�����̕�
		0,									//	�����̑���
		0,
		false,								//	�C�^���b�N�����̎g�p
		SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		NULL,
		&pFont
		);

}

void DrawTxt(char str[256], RECT range, int alpha, int red, int green, int blue)
{
	pFont->DrawText(
		NULL,
		str,									// �`��e�L�X�g
		-1,										// �S�ĕ\��
		&range,									// �\���͈�
		DT_LEFT,								// ����
		D3DCOLOR_ARGB(alpha, red, green, blue)	// �F
		);
}