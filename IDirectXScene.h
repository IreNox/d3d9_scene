#pragma once

#include "List.h"
#include "Mesh.h"
#include "Label.h"
#include "Light.h"
#include "Camera.h"
#include "Button.h"
#include "VertexBuffer.h"
#include "IDirectXElement.h"
#include "VertexBufferWithIndexes.h"

class IDirectXScene
{
public:
	IDirectXScene(LPDIRECT3DDEVICE9 device, List<IDirectXElement>* elements)
	{
		g_Device = device;
		m_listElements = elements;
	}

	virtual ~IDirectXScene(void)
	{
	}

	virtual bool LoadScene()
	{
		return true;
	}

	virtual void Render()
	{
	}

	virtual void Update()
	{
	}

protected:
	LPDIRECT3DDEVICE9 g_Device;
	List<IDirectXElement>* m_listElements;
};

