#pragma once

#include <d3d9.h>
#include "IDirectXElement.h"

struct VertexRHW
{
	float x, y, z, rhw;
	DWORD color;

	enum FVF {
		FVF_Flags = D3DFVF_XYZRHW | D3DFVF_DIFFUSE
	};
};

struct VertexColored
{
	float x, y, z;
	DWORD color;

	enum FVF {
		FVF_Flags = D3DFVF_XYZ | D3DFVF_DIFFUSE
	};
};

struct VertexTextured
{
	float x, y, z, rhw;
	float tu, tv;

	enum FVF {
		FVF_Flags = D3DFVF_XYZ | D3DFVF_TEX1
	};
};


class VertexBuffer
	: public IDirectXElement
{
public:
	VertexBuffer(LPDIRECT3DDEVICE9 device);
	~VertexBuffer();

	void LoadFile(char *filename);
	void SaveFile(char* filename);
	
	void SetVertexType(DWORD fvf, UINT size);
	void SetVertices(void** vertexes, UINT count);
	
	void SetMatrix(D3DMATRIX* matrix);
	void SetTexture(LPDIRECT3DTEXTURE9 texture);
	
	void Render();

	ULONG __stdcall Release(void);
protected:
	DWORD m_VertexFVF;
	UINT m_VertexSize;
	UINT m_VerticesCount;

	void* m_Vertices;

	D3DMATRIX* g_matrixWorld;
	LPDIRECT3DTEXTURE9 g_tTexture;
	LPDIRECT3DVERTEXBUFFER9 g_VertexBuffer;

	void m_CreateVertexBuffer();
};

