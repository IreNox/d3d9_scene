// Camera.cpp: Kamera-Klasse
// by Tim Boden
//

#include "Camera.h"
#include "Application.h"

Camera::Camera(LPDIRECT3DDEVICE9 device)
	: IDirectXElement(device)
{
	g_fX = 0.0f;
	g_fY = D3DX_PI / 2;
	g_fMouseX = 0.0f;
	g_fMouseY = 0.0f;

	g_fWidth = (float)App::dx->g_Params.BackBufferWidth;
	g_fHeight = (float)App::dx->g_Params.BackBufferHeight;

	D3DXMATRIXA16 matProj;

    D3DXMatrixPerspectiveFovLH(
		&matProj,
		D3DX_PI / 4,
		(g_fWidth / g_fHeight),
		0.01f,
		10000.0f
	);
    g_Device->SetTransform(D3DTS_PROJECTION, &matProj);

	g_vAt =  D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_vUp =  D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	App::dx->g_fEyeDistance = 5.0f;

	g_vEye = D3DXVECTOR3(
		sinf(g_fX) * App::dx->g_fEyeDistance,
		cosf(g_fY) * App::dx->g_fEyeDistance,
		(cosf(g_fX) * sinf(g_fY)) * App::dx->g_fEyeDistance
	);
	
	D3DXMATRIX matView;
	D3DXMatrixLookAtLH(&matView, &g_vEye, &g_vAt, &g_vUp);
	g_Device->SetTransform(D3DTS_VIEW, &matView);

	D3DXMATRIX worMatrix;
	D3DXMatrixIdentity(&worMatrix);
	g_Device->SetTransform(D3DTS_WORLD, &worMatrix);
}

Camera::~Camera(void)
{
}

void Camera::Update()
{
	float x = (float)App::dx->m_Mouse->GetX();
	float y = (float)App::dx->m_Mouse->GetY();

	if (App::dx->m_Mouse->GetButtonState(MB_LEFTBUTTON))
	{
		g_fX += (g_fMouseX - x) / g_fWidth * 5;
		g_fY += (g_fMouseY - y) / g_fHeight * 5;

		if (g_fX < -D3DX_PI) g_fX += D3DX_PI * 2;
		if (g_fY < -D3DX_PI) g_fY += D3DX_PI * 2;
		if (g_fX > D3DX_PI) g_fX -= D3DX_PI * 2;
		if (g_fY > D3DX_PI) g_fY -= D3DX_PI * 2;

		g_fMouseX = x;
		g_fMouseY = y;
	}
	else
	{
		g_fMouseX = x;
		g_fMouseY = y;
	}

	float fEyeDistance = App::dx->g_fEyeDistance;

	g_vEye = D3DXVECTOR3(
		sinf(g_fX) * fEyeDistance,
		cosf(g_fY) * fEyeDistance,
		(cosf(g_fX) * sinf(g_fY)) * fEyeDistance
	);

	D3DXMATRIX matView;
	D3DXMATRIX matViewLook;
	//D3DXMATRIX matViewRotate;
	//D3DXVECTOR3 vecView(x, y, 0);
	
	D3DXMatrixLookAtLH(&matViewLook, &g_vEye, &g_vAt, &g_vUp);
	//D3DXMatrixRotationAxis(&matViewRotate, &vecView, -1);
	//D3DXMatrixRotationX(&matViewRotate, x);

	//D3DXMatrixMultiply(&matView, &matViewLook, &matViewRotate);	

	g_Device->SetTransform(D3DTS_VIEW, &matViewLook);
}
