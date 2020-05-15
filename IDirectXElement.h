#pragma once

#include <d3d9.h>

class IDirectXElement
//	: public IUnknown
{
public:
	IDirectXElement(LPDIRECT3DDEVICE9 device)
	{
		g_Device = device;
	}

	virtual ~IDirectXElement(void)
	{
	}

	virtual void Render()
	{
	}
	
	virtual void Update()
	{
	}

	/*ULONG __stdcall AddRef(void)
	{
		return ++g_lInstances;
	}

	virtual ULONG __stdcall Release(void);*/
protected:
	LPDIRECT3DDEVICE9 g_Device;

private:
	//static ULONG g_lInstances;

	IDirectXElement(void)
	{
	}
};

