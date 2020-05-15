#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include "List.h"

#include "Mouse.h"

#include "SceneTest.h"
#include "SceneLoading.h"
#include "SceneSolarSystem.h"

class DirectX
{
public:
	float g_fEyeDistance;

	LPDIRECT3D9 g_Direct3D;
	LPDIRECT3DDEVICE9 g_Device;
	D3DPRESENT_PARAMETERS g_Params;

	Mouse* m_Mouse;
	IDirectXScene* m_Scene;
	SceneLoading* m_sceneLoading;

	DirectX();
	~DirectX();

	BOOL InitDirectX();
	void DisposeDirectX(BOOL quit);

	void Render();

	void HandleMessage(UINT message, WPARAM wParam, LPARAM lParam);
private:
	List<IDirectXElement>* m_listElements;
};

