#include "GameFunc.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	コンストラクタ
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
GameFunc::GameFunc()
	: m_Model(new FbxRelated(pD3Device))
	, m_Model2(new FbxRelated(pD3Device))
	, m_CameraPos(new D3DXVECTOR3({0.0f, 20.0f, -150.0f}))
	, m_LookatPos(new D3DXVECTOR3({ 0.0f, 0.0f, 0.0f }))
	, m_Angle(new float(100.f))
	, m_Scene(TRANSITION_START)
{
	if (!m_Model->LoadFbx("fbx/kongou.fbx"))
	{
		// 読み込み失敗したらエラー
		MessageBox(0, "FBXファイルの読み込みに失敗しました。", NULL, MB_OK);
	}
	if (!m_Model2->LoadFbx("fbx/kongou.fbx"))
	{
		// 読み込み失敗したらエラー
		MessageBox(0, "FBXファイルの読み込みに失敗しました。", NULL, MB_OK);
	}

	RoadTexEx("ui.png",
		&m_pTexture,
		255, 0, 255, 0,
		false);
	
	m_OpeTable[0] = {   0.f, 0.f, 0.5f, 1.f, 0xFFFFFFFF, 0.f, 0.f };
	m_OpeTable[1] = { 600.f, 0.f, 0.5f, 1.f, 0xFFFFFFFF, 1.f, 0.f };
	m_OpeTable[2] = { 600.f, 250.f, 0.5f, 1.f, 0xFFFFFFFF, 1.f, 1.f };
	m_OpeTable[3] = { 0.f, 250.f, 0.5f, 1.f, 0xFFFFFFFF, 0.f, 1.f };

	for (int i = 0; i < 5; i++)
	{
		m_StartTxt[i].left = 10;
		m_StartTxt[i].top = 50 + 150 * i;
		m_StartTxt[i].right = 1590;
		m_StartTxt[i].bottom = 150 + 150 * i;
	}

	m_Txt.left = 10;
	m_Txt.top = 250;
	m_Txt.right = 1600;
	m_Txt.bottom = 900;

	m_ObjPos.x = 0.f;
	m_ObjPos.y = 0.f;
	m_ObjPos.z = 0.f;

	m_ObjPos2.x = 50.f;
	m_ObjPos2.y = 0.f;
	m_ObjPos2.z = 0.f;


}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	デストラクタ
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
GameFunc::~GameFunc()
{
	delete m_Model;
	delete m_Model2;
	delete m_CameraPos;
	delete m_LookatPos;
	delete m_Angle;
}

void GameFunc::Run()
{
	switch (m_Scene)
	{
	case TRANSITION_START:
		Init_Txt(100, 50);
		m_Scene = START;
	case START:
	{
		static int count = 0;
		static int alpha = 110;
		static int alpha2 = 0;
		static int alpha3 = 0;
		static int alpha4 = 0;

		if (count <= 150)
		{
			static int num = 5;
			if (alpha == 105 || alpha == 255)
			{
				num *= -1;
			}
			alpha += num;
		}
		else if (count <= 270)
		{
			alpha2 += 2;
		}
		else
		{
			if (alpha3 < 200)
			{
				alpha3 += 2;
			}
			KeyCheck(&m_key[RETURN], DIK_RETURN);
			
			if (m_key[RETURN] == PUSH)
			{
				m_Scene = TRANSITION_MAIN;
			}
		}
		SetGameSceneStart(D3DFVF_CUSTOMVERTEX);

		DrawTxt("            WORNING!!", m_StartTxt[0], alpha, 255, 225, 0);
		DrawTxt("    この課題のソースコードは", m_StartTxt[1], alpha2, 255, 225, 255);
		DrawTxt("     クソ雑魚2Dライブラリで", m_StartTxt[2], alpha2, 255, 0, 0);
		DrawTxt("     無理やり作ったものです。", m_StartTxt[3], alpha2, 255, 225, 255);
		DrawTxt("          PRESS ENTER", m_StartTxt[4], alpha3, 255, 165, 0);
		SetGameSceneEnd();

		count++;
		break;
	}
	case TRANSITION_MAIN:
		Init_Txt(200, 100);
		m_Scene = MAIN;
	case MAIN:
		Control();
		Render();
		break;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	コントロール関数
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
void GameFunc::Control()
{
	D3DXVECTOR3 nextPos = m_ObjPos;
	KeyCheck(&m_key[UP], DIK_UP);
	KeyCheck(&m_key[DOWN], DIK_DOWN);
	KeyCheck(&m_key[RIGHT], DIK_RIGHT);
	KeyCheck(&m_key[LEFT], DIK_LEFT);
	KeyCheck(&m_key[W], DIK_W);
	KeyCheck(&m_key[A], DIK_A);
	KeyCheck(&m_key[S], DIK_S);
	KeyCheck(&m_key[D], DIK_D);
	KeyCheck(&m_key[I], DIK_I);
	KeyCheck(&m_key[J], DIK_J);
	KeyCheck(&m_key[K], DIK_K);
	KeyCheck(&m_key[L], DIK_L);
	KeyCheck(&m_key[U], DIK_U);
	KeyCheck(&m_key[O], DIK_O);
	KeyCheck(&m_key[Z], DIK_Z);
	KeyCheck(&m_key[X], DIK_X);

	m_CameraRotateSpeedX = 0.f;
	m_CameraRotateSpeedY = 0.f;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	船の操作
	//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
	if (m_key[W] == ON)										//	W	船が前進
	{
		nextPos.z += 1.f;
	}
	if (m_key[A] == ON)										//	A	船が左へ
	{
		nextPos.x -= 1.f;
	}
	if (m_key[S] == ON)										//	S	船が後退
	{
		nextPos.z -= 1.f;
	}
	if (m_key[D] == ON)										//	D	船が右へ
	{
		nextPos.x += 1.f;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	注視点を中心にカメラが回転する操作
	//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
	if (m_key[UP] == ON && m_key[DOWN] == ON)				//	↑と↓の同時入力で相殺
	{
	}
	else if (m_key[UP] == ON)								//	↑	注視点を中心にカメラが上方向へ移動
	{
		m_CameraRotateSpeedX = 1.f;
	}
	else if (m_key[DOWN] == ON)								//	↓	注視点を中心にカメラが下方向へ移動
	{
		m_CameraRotateSpeedX = -1.f;
	}
	if (m_key[RIGHT] == ON && m_key[LEFT] == ON)			//	→と←の同時入力で相殺
	{
	}
	else if (m_key[RIGHT] == ON)							//	→	注視点を中心にカメラが右方向へ移動
	{
		m_CameraRotateSpeedY = -1.f;
	}
	else if (m_key[LEFT] == ON)								//	←	注視点を中心にカメラが左方向へ移動
	{
		m_CameraRotateSpeedY = 1.f;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	カメラの平行移動系操作
	//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
	if (m_key[I] == ON)										//	I	カメラが前進
	{
		m_CameraPos->z += 1.f;
		m_LookatPos->z += 1.f;
	}
	if (m_key[J] == ON)										//	J	カメラが左へ
	{
		m_CameraPos->x -= 1.f;
		m_LookatPos->x -= 1.f;
	}
	if (m_key[K] == ON)										//	K	カメラが後退
	{
		m_CameraPos->z -= 1.f;
		m_LookatPos->z -= 1.f;
	}
	if (m_key[L] == ON)										//	L	カメラが右へ
	{
		m_CameraPos->x += 1.f;
		m_LookatPos->x += 1.f;
	}
	if (m_key[U] == ON)										//	U	カメラが上昇
	{
		m_CameraPos->y += 1.f;
		m_LookatPos->y += 1.f;
	}
	if (m_key[O] == ON)										//	O	カメラが下降
	{
		m_CameraPos->y -= 1.f;
		m_LookatPos->y -= 1.f;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	ズーム系
	//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
	if (m_key[Z] == ON)										//	Z	ズームイン
	{
		*m_Angle -= 0.1f;
	}
	if (m_key[X] == ON)										//	X	ズームアウト
	{
		*m_Angle += 0.1f;
	}

	static int hitCount;
	if (!CheckCollision(nextPos, m_ObjPos2))
	{
		m_ObjPos = nextPos;
	}
	else
	{
		hitCount = 0;
		m_IsHit = true;
	}
	if (m_IsHit)
	{
		hitCount++;
		if (hitCount > 60)
		{
			m_IsHit = false;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	描画関数
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
void GameFunc::Render()
{
	D3DXMatrixRotationY(&m_CameraRotation, m_CameraRotateSpeedY * 3.141592f / 180.f);		//	円周率
	D3DXVec3TransformCoord(m_CameraPos, m_CameraPos, &m_CameraRotation);
	D3DXMatrixRotationX(&m_CameraRotation, m_CameraRotateSpeedX * 3.141592f / 180.f);		//	円周率
	D3DXVec3TransformCoord(m_CameraPos, m_CameraPos, &m_CameraRotation);

	SetGameSceneStart3D(MY_FVF);
	pD3Device->SetRenderState(D3DRS_LIGHTING, FALSE);										// ライト

	// 視点座標
	D3DXMATRIX    matView;																	// 視点座標
	D3DXVECTOR3   vUpVec = { 0.0f, 1.0f, 0.0f };											// カメラの上方向のベクトル。ここは固定
	D3DXMatrixLookAtLH(&matView, m_CameraPos, m_LookatPos, &vUpVec);
	pD3Device->SetTransform(D3DTS_VIEW, &matView);

	// 射影座標
	D3DXMATRIX matProj;																		// 射影座標
	float viewAngle = D3DXToRadian(*m_Angle);												// 視野角
	float aspect = WINDOW_WIDTH / WINDOW_HIGHT;												// アスペクト比
	D3DXMatrixPerspectiveFovLH(&matProj, viewAngle, aspect, 1.f, 1000.f);
	pD3Device->SetTransform(D3DTS_PROJECTION, &matProj);

	D3DXMATRIX      matWorld;																// ワールド座標
	D3DXMATRIX		matPos;																	// 移動用行列
	D3DXMatrixIdentity(&matWorld);															// 単位行列
	D3DXMatrixTranslation(&matPos, m_ObjPos.x, m_ObjPos.y, m_ObjPos.z);
	D3DXMatrixMultiply(&matWorld, &matWorld, &matPos);
	pD3Device->SetTransform(D3DTS_WORLD, &matWorld);

	m_Model->m_pModel->DrawFbx();

	D3DXMATRIX      matWorld2;																// ワールド座標
	D3DXMATRIX		matPos2;																// 移動用行列
	D3DXMatrixIdentity(&matWorld2);															// 単位行列
	D3DXMatrixTranslation(&matPos2, m_ObjPos2.x, m_ObjPos2.y, m_ObjPos2.z);
	D3DXMatrixMultiply(&matWorld2, &matWorld2, &matPos2);
	pD3Device->SetTransform(D3DTS_WORLD, &matWorld2);

	m_Model2->m_pModel->DrawFbx();

	pD3Device->SetFVF(D3DFVF_CUSTOMVERTEX);

	SetGameScene(m_pTexture, m_OpeTable);

	if (m_IsHit)
	{
		DrawTxt("あ", m_Txt, 255, 255, 0, 0);
		DrawTxt("　 た", m_Txt, 255, 255, 165, 0);
		DrawTxt("　　  り", m_Txt, 255, 255, 255, 0);
		DrawTxt("　　   　ま", m_Txt, 255, 0, 128, 0);
		DrawTxt("　　    　　し", m_Txt, 255, 0, 255, 255);
		DrawTxt("　　　     　　た", m_Txt, 255, 0, 0, 255);
		DrawTxt("　　　 　     　 ！", m_Txt, 255, 128, 0, 128);
	}
	SetGameSceneEnd();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	解放関数
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
void GameFunc::FreeDx()
{
	SAFE_RELEASE(pDirect3D);
	SAFE_RELEASE(pD3Device);
	SAFE_RELEASE(pFont);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	あたり判定
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
void GameFunc::CreateCollisionPos(D3DXVECTOR3 objPos, D3DXVECTOR2* collisionPos)
{
	collisionPos[0].x = objPos.x + m_Model->m_pModel->maxX;
	collisionPos[0].y = objPos.z;
	collisionPos[1].x = objPos.x + (m_Model->m_pModel->maxX) / 3;
	collisionPos[1].y = objPos.z + m_Model->m_pModel->maxZ;
	collisionPos[2].x = objPos.x + (m_Model->m_pModel->maxX) / 3;
	collisionPos[2].y = objPos.z + m_Model->m_pModel->minZ;
	collisionPos[3].x = objPos.x + (m_Model->m_pModel->minX) / 3;
	collisionPos[3].y = objPos.z + m_Model->m_pModel->maxZ;
	collisionPos[4].x = objPos.x + (m_Model->m_pModel->minX) / 3;
	collisionPos[4].y = objPos.z + m_Model->m_pModel->minZ;
	collisionPos[5].x = objPos.x + m_Model->m_pModel->minX;
	collisionPos[5].y = objPos.z;
}

bool GameFunc::CheckCollision(D3DXVECTOR3 objPos, D3DXVECTOR3 objPos2)
{
	CreateCollisionPos(objPos, m_CollisionPos);
	CreateCollisionPos(objPos2, m_CollisionPos2);
	for (int i = 0; i < 4; i++)
	{

		D3DXVECTOR2 A = m_CollisionPos[i];
		D3DXVECTOR2 B = m_CollisionPos[i + 1];
		D3DXVECTOR2 C = m_CollisionPos[i + 2];

		for (int j = 0; j < 6; j++)
		{
			D3DXVECTOR2 P = m_CollisionPos2[j];

			D3DXVECTOR2 AB = SubCheckCollision(B, A);
			D3DXVECTOR2 BP = SubCheckCollision(P, B);

			D3DXVECTOR2 BC = SubCheckCollision(C, B);
			D3DXVECTOR2 CP = SubCheckCollision(P, C);

			D3DXVECTOR2 CA = SubCheckCollision(A, C);
			D3DXVECTOR2 AP = SubCheckCollision(P, A);

			double z1 = AB.x * BP.y - AB.y * BP.x;
			double z2 = BC.x * CP.y - BC.y * CP.x;
			double z3 = CA.x * AP.y - CA.y * AP.x;

			if ((z1 > 0 && z2 > 0 && z3 > 0) || (z1 < 0 && z2 < 0 && z3 < 0))
			{
				return true;
			}
		}
	}
	return false;
}

D3DXVECTOR2 GameFunc::SubCheckCollision(D3DXVECTOR2 a, D3DXVECTOR2 b)
{
	D3DXVECTOR2 ret;

	ret.x = a.x - b.x;
	ret.y = a.y - b.y;

	return ret;
}

