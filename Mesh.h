#pragma once

#include <d3dx9.h>
#include "IDirectXElement.h"

class Mesh
	: public IDirectXElement
{
public:
	Mesh(LPDIRECT3DDEVICE9 device, LPD3DXMESH mesh, LPD3DXBUFFER buffer, DWORD subsetCount);
	~Mesh(void);

	void Render();
	
	void SetMatrix(D3DMATRIX* matrix);
	void SetTexture(DWORD subset, LPDIRECT3DTEXTURE9 texture);
private:
	DWORD g_lSubsetCount;

	D3DMATRIX* g_matrixWorld;

	LPD3DXMESH g_mMesh;
	LPD3DXBUFFER g_bBuffer;

	D3DXMATERIAL* g_Materials;
	LPDIRECT3DTEXTURE9* g_Textures;
};

