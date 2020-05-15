// Light.cpp: Licht(Nur Spotlicht)
// by Tim Boden
//

#include "Light.h"

Light::Light(LPDIRECT3DDEVICE9 device)
	: IDirectXElement(device)
{
	g_Light = new D3DLIGHT9();
	g_lIndex = 0;
	while (SUCCEEDED(g_Device->GetLight(g_lIndex, g_Light)))
	{
		g_lIndex++;
	}	

	g_Light = new D3DLIGHT9();

	g_Light->Type     = D3DLIGHT_SPOT;
    g_Light->Range    = 10000.0f;
	g_Light->Ambient  = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	g_Light->Diffuse  = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Light->Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Light->Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Light->Attenuation0 = 0;
	g_Light->Attenuation1 = 0;
	g_Light->Attenuation2 = 0;

	UpdateLight();
}

Light::~Light(void)
{
	delete(g_Light);
}

void Light::SetColor(D3DXCOLOR color)
{
	g_Color = color;
	g_Light->Diffuse = color;
	g_Light->Specular = color;

	UpdateLight();
}

void Light::SetPosition(D3DXVECTOR3 pos)
{
	g_Position = pos;
	g_Light->Position = pos;

	UpdateLight();
}

void Light::UpdateLight()
{
	g_Device->SetLight(g_lIndex, g_Light);
	g_Device->LightEnable(g_lIndex, TRUE);
}