// Label.cpp: Stellt Text dar
// by Tim Boden
//

#include "Label.h"
#include "Application.h"

Label::Label(LPDIRECT3DDEVICE9 device)
	: IDirectXElement(device)
{
	SetFont(L"Arial");
	SetColor(D3DCOLOR_ARGB(255, 0, 0, 255));

	RECT rect;
	rect.top    = 10;
	rect.left   = 10;
	rect.right  = 500;
	rect.bottom = 200;
	SetRect(&rect);
}

Label::~Label(void)
{
	if (g_Font != NULL) g_Font->Release();
}

void Label::Render()
{
	g_Font->DrawText(NULL, g_cText, -1, &g_FontRect, 0, g_FontColor);
}

void Label::SetText(TCHAR* text)
{
	g_cText = text;
}

void Label::SetFont(TCHAR* font)
{
	HRESULT r = 0;

	r = D3DXCreateFont(g_Device, 20, 0, FW_BOLD, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, font, &g_Font );

	if (FAILED(r))
	{
		App::MsgBox(L"Schrift konnte nicht erstellt werden.", MB_OK | MB_ICONEXCLAMATION);
	}
}

void Label::SetRect(LPRECT rect)
{
	memcpy(&g_FontRect, rect, sizeof(RECT));
}

void Label::SetColor(D3DCOLOR color)
{
	g_FontColor = color;
}

/*ULONG IDirectXElement::Release()
{
	return --Lable::g_lInstances;
}*/