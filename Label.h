#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "IDirectXElement.h"
#include <stdio.h>

class Label
	: public IDirectXElement
{
public:
	Label(LPDIRECT3DDEVICE9 device);
	~Label(void);

	void Render();

	void SetText(TCHAR* text);
	void SetFont(TCHAR* font);
	void SetRect(LPRECT rect);
	void SetColor(D3DCOLOR color);

protected:
	RECT g_FontRect;
	D3DCOLOR g_FontColor;   
	LPD3DXFONT g_Font;

	TCHAR* g_cText;
};

