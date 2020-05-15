// Mesh.cpp: Verwaltet ein Mesh mit Materials und Texturen
// by Tim Boden
//

#include "Mesh.h"
#include "Application.h"

Mesh::Mesh(LPDIRECT3DDEVICE9 device, LPD3DXMESH mesh, LPD3DXBUFFER buffer, DWORD subsetCount)
	: IDirectXElement(device)
{
	g_mMesh = mesh;
	g_bBuffer = buffer;
	g_lSubsetCount = subsetCount;

	D3DXMATRIX* worldMatrix = new D3DXMATRIX();
	D3DXMatrixIdentity(worldMatrix);
	g_matrixWorld = worldMatrix;

	g_Textures = new LPDIRECT3DTEXTURE9[g_lSubsetCount];

	if (buffer != NULL)
	{
		g_Materials = (D3DXMATERIAL*)buffer->GetBufferPointer();

		for (DWORD i = 0; i < g_lSubsetCount; i++)
		{
			HRESULT r = -1;
			
			if (g_Materials[i].pTextureFilename)
			{
				r = D3DXCreateTextureFromFile(g_Device, L"", &g_Textures[i]); //g_Materials[i].pTextureFilename(konvertierung fehlt)
			}

			if (FAILED(r))
			{
				g_Textures[i] = NULL;
			}
		}
	}
	else
	{
		App::MsgBox(L"Mesh konnte nicht geladen werden.", MB_OK | MB_ICONSTOP);
	}
}

Mesh::~Mesh(void)
{
	g_mMesh->Release();
	g_bBuffer->Release();

	delete(g_Textures);
	delete(g_matrixWorld);
}

void Mesh::Render()
{
	g_Device->SetTransform(D3DTS_WORLD, g_matrixWorld);

	if (SUCCEEDED(g_Device->BeginScene()))
	{
		for (DWORD i = 0; i < g_lSubsetCount; i++)
		{
			g_Device->SetMaterial(&g_Materials[i].MatD3D);
			g_Device->SetTexture(0, g_Textures[i]);
			g_mMesh->DrawSubset(i);
		}

		g_Device->EndScene();
	}
}

void Mesh::SetMatrix(D3DMATRIX* matrix)
{
	memcpy(g_matrixWorld, matrix, sizeof(D3DXMATRIX));
}

void Mesh::SetTexture(DWORD subset, LPDIRECT3DTEXTURE9 texture)
{
	if (subset <= g_lSubsetCount)
	{
		g_Textures[subset] = texture;
	}
}