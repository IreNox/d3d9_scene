#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "IDirectXElement.h"

class Camera
	: public IDirectXElement
{
public:
	float g_fX;
	float g_fY;

	Camera(LPDIRECT3DDEVICE9 device);
	~Camera(void);

	void Update();


private:
	float g_fWidth;
	float g_fHeight;

	float g_fMouseX;
	float g_fMouseY;

	D3DXVECTOR3 g_vAt;
	D3DXVECTOR3 g_vUp;
	D3DXVECTOR3 g_vEye;

	void InitCamera();
};
