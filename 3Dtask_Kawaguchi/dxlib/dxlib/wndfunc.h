/**	@file	wndfunc.h
	@brief	windows �֐�

	@author	��� �D��Y
*/

#include <windows.h>


/**	@brief	�`�悷��e�L�X�g�̃t�H���g�̏�����
	
	@param[in]		Title	�^�C�g��
	@param[in]		hight	�E�B���h�E�̍���
	@param[in]		width	�E�B���h�E�̕�
*/

HRESULT InitWnd(MSG* msg, HWND* hWnd, HINSTANCE hInstance, char Title[256], int width, int hight);
