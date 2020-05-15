#pragma once

#include <d3dx9.h>
#include "IDirectXElement.h"

class Light
	: public IDirectXElement
{
public:
	Light(LPDIRECT3DDEVICE9 device);
	~Light(void);

	void SetColor(D3DXCOLOR color);
	void SetPosition(D3DXVECTOR3 pos);

private:
	DWORD g_lIndex;

	D3DLIGHT9* g_Light;

	D3DCOLOR g_Color;
	D3DVECTOR g_Position;

	void UpdateLight();
};
