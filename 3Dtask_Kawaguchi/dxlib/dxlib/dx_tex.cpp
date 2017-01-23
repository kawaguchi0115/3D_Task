/**	@file	dx_tex.cpp
	@brief	DirectX Twxture関数

	@author	川口 颯一郎
*/

#include"dx_tex.h"

ID3DXFont*	       pFont;

void Init_Tex()
{
	pD3Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);					//	アルファブレンドによる透明化を有効にする
	pD3Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);				//	半透明ブレンディングの設定
	pD3Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);			//	↑↑　とセット
	pD3Device->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);		//	ディヒューズ色の設定

	pD3Device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	pD3Device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);		//	ディヒューズ色の色引数の処理を有効化する

	pD3Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);		//	カラーブレンディング処理を乗算にする

	pD3Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pD3Device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);		//	ディヒューズ色の透過色引数の処理を有効化する

	pD3Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);		//	アルファブレンディングの処理を乗算にする

}
//------------------------------------------------------------------------------
//
//	RoadTex(第１引数、第２引数)
//	第１引数 : 画像ファイル名　"name.xxx"
//	第２引数 : 格納する場所へのポインタ　&name or &name[NAME]
//
//------------------------------------------------------------------------------
HRESULT RoadTex(LPCTSTR pSrcFile, IDirect3DTexture9* pTexture[])
{
	if(FAILED (D3DXCreateTextureFromFile(pD3Device, pSrcFile, pTexture) ) )
	{
		MessageBox(0, "画像の読み込みに失敗しました。", NULL, MB_OK);
		return E_FAIL;
	}
	return S_OK;
}

//----------------------------------------------------------------------
//
//	RoadTexEx(第１引数、第２引数、第３引数)
//	第１引数 : 画像ファイル名　"name.xxx"
//	第２引数 : 格納する場所へのポインタ　&name or &name[NAME]
//	第３４５引数 : A,R,G,B 
//	第６引数画像サイズが２のべき乗でなければ　false を
//
//----------------------------------------------------------------------
HRESULT RoadTexEx(LPCTSTR pSrcFile, IDirect3DTexture9* pTexture[], int alpha, int red, int green, int blue, bool TexSize)
{
	if (TexSize)
	{
		if (FAILED(D3DXCreateTextureFromFileEx(
			pD3Device,			//	インターフェイスへのポインタ
			pSrcFile,			//	画像ファイル名
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
			MessageBox(0, "画像の読み込みに失敗しました。", NULL, MB_OK);
			return E_FAIL;
		}
	}
	else			//	2のべき乗でない場合
	{
		if (FAILED(D3DXCreateTextureFromFileEx(
			pD3Device,			//	インターフェイスへのポインタ
			pSrcFile,			//	画像ファイル名
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
			MessageBox(0, "画像の読み込みに失敗しました。", NULL, MB_OK);
			return E_FAIL;
		}
	}
	return S_OK;
}
//-----------------------------------------------------------
//
//	設定した FVF を渡す
//
//-----------------------------------------------------------
void SetGameSceneStart(DWORD FVF)
{

	//	頂点情報の指定
	pD3Device->SetFVF(FVF);

	//	画面消去
	pD3Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0x00, 0x00, 0x00), 1.0, 0);

	//	描画開始
	pD3Device->BeginScene();
}

void SetGameSceneStart3D(DWORD FVF)
{

	//	頂点情報の指定
	pD3Device->SetFVF(FVF);

	//	画面消去
	pD3Device->Clear(0, NULL, D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0x00, 0x00, 0x00), 1.0, 0);

	//	描画開始
	pD3Device->BeginScene();
}

//----------------------------------------------------------------
//
//	1 : 用意したテクスチャを格納する配列へのポインタ
//	2 : テクスチャの CUSTOMVERTEX
//
//----------------------------------------------------------------

void SetGameScene(IDirect3DTexture9* pTexture, CUSTOMVERTEX TexVertex[])
{
	//	画像を割り当てる
	pD3Device->SetTexture(0, pTexture);
	//	描画
	pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, TexVertex, sizeof(CUSTOMVERTEX));

}

void SetGameSceneEnd()
{
	//	描画終了
	pD3Device->EndScene();
	//	画面に表示
	pD3Device->Present(NULL, NULL, NULL, NULL);
}





//------------------------------------------------------------------------------------
//
//	テキスト描画関数
//
//------------------------------------------------------------------------------------

void Init_Txt(int hight, int width)
{
	D3DXCreateFont(
		pD3Device,
		hight,								//	文字の高さ
		width,								//	文字の幅
		0,									//	文字の太さ
		0,
		false,								//	イタリック文字の使用
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
		str,									// 描画テキスト
		-1,										// 全て表示
		&range,									// 表示範囲
		DT_LEFT,								// 左寄せ
		D3DCOLOR_ARGB(alpha, red, green, blue)	// 色
		);
}