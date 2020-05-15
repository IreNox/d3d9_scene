// Button.cpp: Schaltfläsche(Nur anzeige)
// by Tim Boden
//

#include "Button.h"
#include "Application.h"

Button::Button(LPDIRECT3DDEVICE9 device, LPRECT rect)
	: IDirectXElement(device), Label(device), m_ivbBackground(device), g_cColor(0)
{
	g_pRect = rect;
	
	SetRect(rect);

	// e = ClickHandler;

	//App::dx->m_Mouse->m_eventClick.AddHandler(ClickHandler);

	SetVertexBuffer();
}


Button::~Button(void)
{
}

void Button::SetLabelText(TCHAR* text)
{
	SetText(text);
}

void Button::SetBackgroundColor(D3DCOLOR color)
{
	g_cColor = color;
	SetVertexBuffer();
}

void Button::Render()
{
	m_ivbBackground.Render();
	
	Label::Render();
}

void Button::SetVertexBuffer()
{
	RectangleF r = RectangleF(
		(float)g_pRect->top,
		(float)g_pRect->bottom,
		(float)g_pRect->left,
		(float)g_pRect->right
	);

	VertexRHW vertices[] = {
        { r.Left,  r.Top,    0.0f, 1.0f, g_cColor, },
        { r.Right, r.Top,    0.0f, 1.0f, g_cColor, },
        { r.Right, r.Bottom, 0.0f, 1.0f, g_cColor, },
        { r.Left,  r.Bottom, 0.0f, 1.0f, g_cColor, },
	};

	WORD indexes[] = {
		0, 1, 2,
		0, 2, 3,
	};

	m_ivbBackground.SetIndexes(indexes, sizeof(indexes) / sizeof(WORD));
	m_ivbBackground.SetVertices((void**)&vertices, sizeof(vertices) / sizeof(VertexRHW));
}

void CALLBACK Button::ClickHandler(LPVOID, LPVOID)
{
}