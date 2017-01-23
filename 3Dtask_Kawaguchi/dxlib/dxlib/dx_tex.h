/**	@file	dx_tex.h
	@brief	DirectX Twxture�֐�

	@author	��� �D��Y
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
/**	@brief	�`����@��ݒ肷��֐�

	@attention	�ڂ����ݒ�̓\�[�X���R�����g�Q��

	@return		�Ȃ�
*/
//-------------------------------------------------------------------------------
void Init_Tex();







//-------------------------------------------------------------------------------
//	
/**	@brief	�摜��ǂݍ��ފ֐�	���̂P
	
		D3DXCreateTextureFromFile ���ȗ��������֐�							<br>
	
	@attention	���ߐF�̎w�肪����摜�͂������ő��v
	
	@param		pSrcFile	�摜�t�@�C�����@"name.xxx"
	@param		pTexture	�i�[����ꏊ�ւ̃|�C���^�@&name or &name[NAME]

	@retval		S_OK	����
	@retval		E_FAIL	�G���[
*/
//------------------------------------------------------------------------------
HRESULT RoadTex(LPCTSTR pSrcFile, IDirect3DTexture9* pTexture[]);







//------------------------------------------------------------------------------
//
/**	@brief	�摜��ǂݍ��ފ֐�	���̂Q
	
		D3DXCreateTextureFromFileEX ���ȗ��������֐�						<br>
	
	@attention	��ȊO�̉摜�͓��ߐF�̎w������Ȃ���΂����Ȃ��̂ł�����
	@attention	�摜�T�C�Y���Q�ׂ̂���łȂ���Ηv�ύX	�\�[�X���Q��


	@param[in]		pSrcFile	�摜�t�@�C�����@"name.xxx"
	@param[in]		pTexture	�i�[����ꏊ�ւ̃|�C���^�@&name or &name[NAME]
	@param[in]		alpha		ALPHA�l	���ߓx
	@param[in]		red			RED		�Ԃ̔Z��
	@param[in]		green		GREEN	�΂̔Z��
	@param[in]		blue		BLUE	�̔Z��
	@param[in]		TexSize		�摜�̃T�C�Y���Q�ׂ̂���łȂ��ꍇ�� false ��

	@retval		S_OK	����
	@retval		E_FAIL	�G���[
*/
//------------------------------------------------------------------------------
HRESULT RoadTexEx(LPCTSTR pSrcFile, IDirect3DTexture9* pTexture[], int alpha, int red, int green, int blue, bool TexSize);







/**	@brief	�`��J�n���Ɉ�x����

	@param[in]		FVF		�ݒ肵�� FVF

	@return		�Ȃ�
*/
void SetGameSceneStart(DWORD FVF);

void SetGameSceneStart3D(DWORD FVF);





/**	@brief	�摜��p�ӂ����񋓂Ɋ��蓖�Ă�

	@param[in]		pTexture	�i�[����ꏊ�ւ̃|�C���^�@&name or &name[NAME]
	@param[in]		TexVertex	�ݒ肵���摜�� CUSTOMVERTEX �̕ϐ�
*/
void SetGameScene(IDirect3DTexture9* pTexture, CUSTOMVERTEX TexVertex[]);







/**	@brief	�`��I�����Ɉ�x����

	@return		�Ȃ�
*/
void SetGameSceneEnd();





/**	@brief	�`�悷��e�L�X�g�̃t�H���g�̏�����

	@param[in]		hight	�����̍���
	@param[in]		width	�����̕�
*/
void Init_Txt(int hight, int width);


/**	@brief	�e�L�X�g�`��֐�

	@param[in]		str		�`�悷��e�L�X�g
	@param[in]		range	�\���͈�
	@param[in]		alpha	ALPHA�l	���ߓx
	@param[in]		red		RED		�Ԃ̔Z��
	@param[in]		green	GREEN	�΂̔Z��
	@param[in]		blue	BLUE	�̔Z��
*/
void DrawTxt(char str[256], RECT range, int alpha, int red, int green, int blue);