#pragma once

#include <d3d9.h>
#include "Event.h"
#include "IDirectXElement.h"

enum MOUSEBUTTON {
	MB_LEFTBUTTON = 0,
	MB_MIDDLEBUTTON = 1,
	MB_RIGHTBUTTON = 2
};

struct MOUSEPOS {
	UINT X;
	UINT Y;
};

typedef int BUTTONSTATE;

class Mouse
	: public IDirectXElement
{
public:
	Event m_eventMove;
	Event m_eventClick;
	Event m_eventDoubleClick;

	Mouse(LPDIRECT3DDEVICE9);
	~Mouse(void);

	UINT GetX();
	UINT GetY();
	BOOL GetButtonState(MOUSEBUTTON);

	void HandleMessage(UINT message, WPARAM wParam, LPARAM lParam);

	void Render();
private:
	MOUSEPOS m_Pos;
	BUTTONSTATE* m_Buttons;

	LPDIRECT3DDEVICE9 g_Device;

	void SetPosition(UINT x, UINT y);
};

