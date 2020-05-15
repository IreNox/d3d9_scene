// DirectX.cpp: Alle benötigten DirectX-Funktionen
// by Tim Boden
//

#include "stdafx.h"
#include "Application.h"
#include "DirectX.h"

DirectX::DirectX()
	: g_Device(NULL), g_Direct3D(NULL)
{
}

DirectX::~DirectX()
{
	this->DisposeDirectX(TRUE);
}

BOOL DirectX::InitDirectX()
{
	bool ok = true;
	HRESULT r = 0;

	// DirectX-Object erstellen, wenn noch nicht erstellt.
	if (g_Direct3D == NULL)
	{
		g_Direct3D = Direct3DCreate9(D3D_SDK_VERSION);
	
		if (g_Direct3D == NULL)
		{
			App::MsgBox(L"Direct3D Object konnte nicht erstellt werden!", MB_OK | MB_ICONEXCLAMATION);
			return FALSE;
		}
	}

	// DirectX-Device erstellen, wenn noch nicht erstellt.
	if (g_Device == NULL)
	{
		D3DDISPLAYMODE displayMode;
		g_Direct3D->GetAdapterDisplayMode(0, &displayMode);

		ZeroMemory(&g_Params, sizeof(D3DPRESENT_PARAMETERS));
		g_Params.Windowed = TRUE;
		g_Params.SwapEffect = D3DSWAPEFFECT_DISCARD;
		g_Params.BackBufferFormat = D3DFMT_UNKNOWN;
		g_Params.EnableAutoDepthStencil = TRUE;
		g_Params.AutoDepthStencilFormat = D3DFMT_D16;

		RECT *winRect = new RECT();
		if (GetClientRect(App::hWnd, winRect))
		{
			g_Params.BackBufferWidth = winRect->right - winRect->left;
			g_Params.BackBufferHeight = winRect->bottom - winRect->top;
		}
		delete(winRect);

		r = g_Direct3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, App::hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_Params, &g_Device);
		
		if (FAILED(r))
		{
			App::FailBox(L"Direct3D Device konnte nicht erstellt werden!", r);
			return FALSE;
		}
	}
	else
	{
		r = g_Device->Reset(&g_Params);

		if (FAILED(r))
		{
			App::FailBox(L"Direct3D Device konnte nicht zurückgesetzt werden!", r);

			return FALSE;
		}
	}

	g_Device->SetRenderState(D3DRS_LIGHTING,  FALSE);
	g_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	m_listElements = new List<IDirectXElement>();

	// Maus erstellen und hinzufügen
	m_Mouse = new Mouse(g_Device);
	m_listElements->Add(m_Mouse);

	// Lade Szene laden
	m_sceneLoading = new SceneLoading(g_Device, m_listElements);
	m_Scene = m_sceneLoading;
	m_sceneLoading->LoadScene();

	// Szene erstellen und laden
	//m_Scene = new SceneTest(g_Device, m_listElements);
	IDirectXScene* scene = new SceneSolarSystem(g_Device, m_listElements);
	ok = scene->LoadScene();
	m_Scene = scene;

	// Lade Szene löschen
	delete(m_sceneLoading);
	m_sceneLoading = NULL;

	return ok;
}

void DirectX::Render()
{
	if (g_Device == NULL) return;

	// Szene updaten
	m_Scene->Update();

	// BackBuffer leeren
	g_Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER , D3DCOLOR_XRGB(0, 0, 128), 1.0f, 0);

	// Szene rendern
	m_Scene->Render();

	// Bild darstellen
	g_Device->Present(NULL, NULL, NULL, NULL);
}

void DirectX::HandleMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (g_Device == NULL) return;

	// Maus-Nachrichten an Maus-Module weiterleiten
	if (message >= 0x0200 && message < 0x0210)
	{
		m_Mouse->HandleMessage(message, wParam, lParam);
	}

	DWORD state = 0;

	switch (message)
	{
		// Mittlere-Maustaste: Licht an/aus
		case WM_MBUTTONUP:
			g_Device->GetRenderState(D3DRS_LIGHTING, &state);

			if (state == TRUE)
			{
				g_Device->SetRenderState(D3DRS_LIGHTING, FALSE);
			}
			else
			{
				g_Device->SetRenderState(D3DRS_LIGHTING, TRUE);
			}
			break;
		// Rechte-Maustaste:: Wireframe an/aus
		case WM_RBUTTONUP:
			g_Device->GetRenderState(D3DRS_FILLMODE, &state);

			if (state == D3DFILL_WIREFRAME)
			{
				g_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
			}
			else
			{
				g_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
			}
			break;
		case WM_SIZE:
			if (wParam != SIZE_MINIMIZED && !m_Mouse->GetButtonState(MB_LEFTBUTTON))
			{
				DisposeDirectX(FALSE);

				g_Params.BackBufferWidth = LOWORD(lParam);
				g_Params.BackBufferHeight = HIWORD(lParam);

				if (!InitDirectX())
				{
					g_Device->Release();
					g_Device = NULL;

					DestroyWindow(App::hWnd);
				}
			}
			break;
		case WM_MOUSEWHEEL:
			short zDelta = GET_WHEEL_DELTA_WPARAM(wParam) / 12;

			g_fEyeDistance -= zDelta;

			if (g_fEyeDistance < 50.0f) g_fEyeDistance = 50.0f;
			if (g_fEyeDistance > 900.0f) g_fEyeDistance = 900.0f;
			break;
	}
}

// Entladen der DirectX-Komponenten
void DirectX::DisposeDirectX(BOOL quit)
{
    if (g_Device != NULL && quit)
	{
		g_Device->Release();
		g_Device = NULL;
	}

	if (g_Direct3D != NULL && quit)
	{
		g_Direct3D->Release();
		g_Direct3D = NULL;
	}

	if (m_listElements != NULL)
	{
		for (int i = 0; i < m_listElements->Count(); i++)
		{
			delete(m_listElements->GetValue(i));
		}

		delete(m_listElements);
		m_listElements = NULL;
	}
}