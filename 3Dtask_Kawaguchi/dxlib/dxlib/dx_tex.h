/**	@file	dx_tex.h
	@brief	DirectX Twxture関数

	@author	川口 颯一郎
*/

#ifndef DX_TEX
#define DX_TEX

#include "dx_Init.h"


struct CUSTOMVERTEX
{
	FLOAT	x, y, z, rhw;
	DWORD	color;
	FLOAT	tu, tv;
};

extern ID3DXFont*	       pFont;

#endif

//-------------------------------------------------------------------------------
//
/**	@brief	描画方法を設定する関数

	@attention	詳しい設定はソース内コメント参照

	@return		なし
*/
//-------------------------------------------------------------------------------
void Init_Tex();







//-------------------------------------------------------------------------------
//	
/**	@brief	画像を読み込む関数	その１
	
		D3DXCreateTextureFromFile を簡略化した関数							<br>
	
	@attention	透過色の指定がある画像はこっちで大丈夫
	
	@param		pSrcFile	画像ファイル名　"name.xxx"
	@param		pTexture	格納する場所へのポインタ　&name or &name[NAME]

	@retval		S_OK	成功
	@retval		E_FAIL	エラー
*/
//------------------------------------------------------------------------------
HRESULT RoadTex(LPCTSTR pSrcFile, IDirect3DTexture9* pTexture[]);







//------------------------------------------------------------------------------
//
/**	@brief	画像を読み込む関数	その２
	
		D3DXCreateTextureFromFileEX を簡略化した関数						<br>
	
	@attention	上以外の画像は透過色の指定をしなければいけないのでこっち
	@attention	画像サイズが２のべき乗でなければ要変更	ソース内参照


	@param[in]		pSrcFile	画像ファイル名　"name.xxx"
	@param[in]		pTexture	格納する場所へのポインタ　&name or &name[NAME]
	@param[in]		alpha		ALPHA値	透過度
	@param[in]		red			RED		赤の濃さ
	@param[in]		green		GREEN	緑の濃さ
	@param[in]		blue		BLUE	青の濃さ
	@param[in]		TexSize		画像のサイズが２のべき乗でない場合は false を

	@retval		S_OK	成功
	@retval		E_FAIL	エラー
*/
//------------------------------------------------------------------------------
HRESULT RoadTexEx(LPCTSTR pSrcFile, IDirect3DTexture9* pTexture[], int alpha, int red, int green, int blue, bool TexSize);







/**	@brief	描画開始時に一度だけ

	@param[in]		FVF		設定した FVF

	@return		なし
*/
void SetGameSceneStart(DWORD FVF);

void SetGameSceneStart3D(DWORD FVF);





/**	@brief	画像を用意した列挙に割り当てる

	@param[in]		pTexture	格納する場所へのポインタ　&name or &name[NAME]
	@param[in]		TexVertex	設定した画像の CUSTOMVERTEX の変数
*/
void SetGameScene(IDirect3DTexture9* pTexture, CUSTOMVERTEX TexVertex[]);







/**	@brief	描画終了時に一度だけ

	@return		なし
*/
void SetGameSceneEnd();





/**	@brief	描画するテキストのフォントの初期化

	@param[in]		hight	文字の高さ
	@param[in]		width	文字の幅
*/
void Init_Txt(int hight, int width);


/**	@brief	テキスト描画関数

	@param[in]		str		描画するテキスト
	@param[in]		range	表示範囲
	@param[in]		alpha	ALPHA値	透過度
	@param[in]		red		RED		赤の濃さ
	@param[in]		green	GREEN	緑の濃さ
	@param[in]		blue	BLUE	青の濃さ
*/
void DrawTxt(char str[256], RECT range, int alpha, int red, int green, int blue);