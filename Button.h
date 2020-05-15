#pragma once
#pragma warning( disable : 4584 )

#include "IDirectXElement.h"
#include "Label.h"
#include "VertexBufferWithIndexes.h"


struct RectangleF
{
	RectangleF() { }
	RectangleF(float fTop, float fBottom, float fLeft, float fRight)
	{
		Top = fTop;
		Bottom = fBottom;
		Left = fLeft;
		Right = fRight;
	}

	float Top;
	float Bottom;

	float Left;
	float Right;
};
typedef RectangleF* LPRECTANGLEF;

class Button
	: public IDirectXElement, private Label
{
public:
	Button(LPDIRECT3DDEVICE9 device, LPRECT rect);
	~Button(void);

	void SetLabelText(TCHAR* text);
	void SetBackgroundColor(D3DCOLOR color);

	void Render();

private:
	DWORD g_cColor;
	LPRECT g_pRect;

	VertexBufferWithIndexes m_ivbBackground;

	void SetVertexBuffer();

	void CALLBACK ClickHandler(LPVOID, LPVOID);
};

