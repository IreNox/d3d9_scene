// Application.cpp: Erstellen des Fensters und Hauptnachrichtenschleife
// by Tim Boden
//

#define _CRT_SECURE_NO_WARNINGS			// Komische Sicherheitswarnung ausblenden

#include "stdafx.h"
#include "Application.h"

#include <dxerr.h>

// Variablen definition
HWND App::hWnd = 0;					// Fensterhandle
HINSTANCE App::hInst = 0;			// Aktuelle Instanz

TCHAR *App::szTitle = L"DirectX Aufgabe";	// Titelleistentext
TCHAR *App::szWindowClass  = L"D3DXXX";		// Klassenname des Hauptfensters

DirectX *App::dx = NULL;

//   FUNKTION: App::WinMain(HINSTANCE)
//   ZWECK: Hauptfunktion
//
int App::WinMain(HINSTANCE hInstance)
{
	App::hInst = hInstance; // Instanzenhandle in statische Variable speichern

	// Anwendungsinitialisierung
	if (!App::InitWindow())
	{
		return FALSE;
	}

	// DirectX initialisierung
	if (!App::InitDirectX())
	{
		return FALSE;
	}

	// Hauptnachrichtenschleife
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	while (msg.message != WM_QUIT)
	{
        if(PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
		{
		}

		dx->Render();
	}

	delete(App::dx);

	return (int)msg.wParam;
}

//   FUNKTION: App::InitInstance(HINSTANCE, int)
//   ZWECK: Erstellt das Hauptfenster.
//
BOOL App::InitWindow()
{
	ATOM r = 0;

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInst;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIcon			= NULL;
	wcex.hIconSm		= NULL;
	wcex.lpszMenuName	= NULL;

	r = RegisterClassEx(&wcex);

	if (FAILED(r))
	{	
		return FALSE;
	}

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768, NULL, NULL, hInst, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, 1);
	UpdateWindow(hWnd);

	return TRUE;
}

//  FUNKTION: App::InitDirectX()
//  ZWECK:  Initialisieren von DirectX
//
BOOL App::InitDirectX()
{
	App::dx = new DirectX();

	return App::dx->InitDirectX();
}

//  FUNKTION: App::WndProc(HWND, UINT, WPARAM, LPARAM)
//  ZWECK:  Verarbeitet Meldungen vom Hauptfenster.
//
LRESULT CALLBACK App::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// Wenn DirectX geladen, dann Nachricht an DirectX-Klasse weiterleiten.
	if (dx != NULL)
	{
		dx->HandleMessage(message, wParam, lParam);
	}

	switch (message)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

//  FUNKTION: App::MsgBox(TCHAR, UINT)
//  ZWECK: MessageBox anzeigen.
//
void App::MsgBox(TCHAR *msg, UINT type)
{
	MessageBox(
		App::hWnd,
		msg,
		L"DirectX Test",
		type
	);
}

//  FUNKTION: App::FailBox(TCHAR, UINT)
//  ZWECK: Fehler anzeigen.
//
void App::FailBox(TCHAR *msg, HRESULT r)
{
	TCHAR* buffer = new TCHAR[1024];
	ZeroMemory(buffer, sizeof(TCHAR) * 1024);
		
	_snwprintf(
		buffer,
		1024,
		L"%s\n\nFehlername: %s\n\nFehlerbeschreibung: %s",
		msg,
		DXGetErrorString(r),
		DXGetErrorDescription(r)
	);

	MessageBox(
		App::hWnd,
		buffer,
		L"DirectX Test",
		MB_OK | MB_ICONSTOP
	);
}