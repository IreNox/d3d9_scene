// Mouse.cpp: Maus-Klasse, Position und Tastenstatus
// by Tim Boden
//

#include "Mouse.h"
#include "Application.h"

Mouse::Mouse(LPDIRECT3DDEVICE9 device)
	: IDirectXElement(device), m_eventMove(), m_eventClick(), m_eventDoubleClick()
{
	g_Device = device;

	ZeroMemory(&m_Pos, sizeof(MOUSEPOS));

	m_Buttons = new BUTTONSTATE[3];
	ZeroMemory(m_Buttons, sizeof(BUTTONSTATE) * 3);
}

Mouse::~Mouse(void)
{
}

UINT Mouse:: GetX()
{
	return m_Pos.X;
}

UINT Mouse::GetY()
{
	return m_Pos.Y;
}

BOOL Mouse::GetButtonState(MOUSEBUTTON button)
{
	if (button >= 0 && button < 3)
	{
		return m_Buttons[button];
	}

	return FALSE;
}

void Mouse::SetPosition(UINT, UINT)
{
	//g_Device->SetCursorPosition(x, y, 0);
}

void Mouse::HandleMessage(UINT message, WPARAM, LPARAM lParam)
{
	switch (message)
	{	
		case WM_LBUTTONUP:
			m_Buttons[0] = FALSE;
			m_eventClick.RaiseEvent(this, &m_Buttons[0]);
			break;
		case WM_LBUTTONDOWN:
			m_Buttons[0] = TRUE;
			break;
		case WM_MBUTTONUP:
			m_Buttons[1] = FALSE;
			m_eventClick.RaiseEvent(this, &m_Buttons[1]);
			break;
		case WM_MBUTTONDOWN:
			m_Buttons[1] = TRUE;
			break;
		case WM_RBUTTONUP:
			m_Buttons[2] = FALSE;
			m_eventClick.RaiseEvent(this, &m_Buttons[1]);
			break;
		case WM_RBUTTONDOWN:
			m_Buttons[3] = TRUE;
			break;
		case WM_LBUTTONDBLCLK:
		case WM_MBUTTONDBLCLK:
		case WM_RBUTTONDBLCLK:
			m_eventDoubleClick.RaiseEvent(this, NULL);
			break;
		case WM_MOUSEMOVE:
			UINT x = LOWORD(lParam);
			UINT y = HIWORD(lParam);

			m_Pos.X = x;
			m_Pos.Y = y;

			m_eventMove.RaiseEvent(this, &m_Pos);
			break;
	}
}

void Mouse::Render()
{
}