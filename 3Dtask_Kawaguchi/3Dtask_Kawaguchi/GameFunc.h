#ifndef GAMEFUNC_H
#define GAMEFUNC_H

#include "../dxlib/dx_lib.h"

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

#define WINDOW_WIDTH 1600
#define WINDOW_HIGHT 900

class GameFunc
{
public:
	GameFunc();
	~GameFunc();
	void Run();
	void Control();																	//	コントロール関数
	void Render();																	//	描画関数
	void FreeDx();																	//	解放関数

private:
	enum SCENE
	{
		TRANSITION_START,
		START,
		TRANSITION_MAIN,
		MAIN
	};
	SCENE					m_Scene;
	D3DXVECTOR3				m_ObjPos;												//	操作艦の座標
	D3DXVECTOR3				m_ObjPos2;												//	固定艦の座標
	D3DXVECTOR2				m_CollisionPos[6];										//	操作艦のあたり判定座標
	D3DXVECTOR2				m_CollisionPos2[6];										//	固定艦のあたり判定座標
	D3DXMATRIX				m_CameraRotation;										//	カメラの回転行列
	float					m_CameraRotateSpeedX;									//	カメラのX軸回転速度
	float					m_CameraRotateSpeedY;									//	カメラのY軸回転速度
	D3DXVECTOR3*			m_CameraPos;											//	カメラ座標
	D3DXVECTOR3*			m_LookatPos;											//	注視点座標
	float*					m_Angle;												//	視野角
	KEYSTATE				m_key[KEY_MAX];											//	入力キー
	bool					m_IsHit;												//	ヒットフラグ
	RECT					m_StartTxt[5];												//	開始画面テキスト表示座標
	RECT					m_StartTxt2;												//	開始画面テキスト表示座標
	RECT					m_StartTxt3;												//	開始画面テキスト表示座標
	RECT					m_StartTxt4;												//	開始画面テキスト表示座標
	RECT					m_StartTxt5;												//	開始画面テキスト表示座標
	RECT					m_Txt;													//	テキスト表示座標
	FbxRelated*				m_Model;												//	モデルデータ
	FbxRelated*				m_Model2;												//	モデルデータ２
	IDirect3DTexture9*		m_pTexture;
	CUSTOMVERTEX			m_OpeTable[4];

	//	以下　あたり判定用関数
	void CreateCollisionPos(D3DXVECTOR3 objPos, D3DXVECTOR2* collisionPos);			
	bool GameFunc::CheckCollision(D3DXVECTOR3 objPos, D3DXVECTOR3 objPos2);			
	D3DXVECTOR2 GameFunc::SubCheckCollision(D3DXVECTOR2 a, D3DXVECTOR2 b);			

};
#endif
