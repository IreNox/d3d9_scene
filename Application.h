#pragma once

#include "DirectX.h"

class App
{
public:
	// Variablen Deklaration
	static HWND hWnd;					// Fensterhandle
	static HINSTANCE hInst;				// Aktuelle Instanz

	static DirectX *dx;					// Instanz der DirectX-Klasse

	// Haupt Funktion
	static int WinMain(HINSTANCE hInstace);

	static void MsgBox(TCHAR *msg, UINT type);
	static void FailBox(TCHAR* text, HRESULT r);

private:
	static TCHAR *szTitle;				// Titelleistentext
	static TCHAR *szWindowClass;		// Klassenname des Hauptfensters

	static BOOL InitWindow();
	static BOOL InitDirectX();

	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
};