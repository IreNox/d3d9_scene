// VertexBuffer.cpp: Simple VertexBuffer-Klasse
// by Tim Boden
//

#define _CRT_SECURE_NO_WARNINGS			// Komische 'fopen' warnung ausblenden

#include <stdio.h>
#include "stdafx.h"
#include "Application.h"
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(LPDIRECT3DDEVICE9 device)
	: IDirectXElement(device), g_tTexture(NULL)
{
	m_VertexFVF = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	m_VertexSize = sizeof(VertexRHW);

	D3DXMATRIX* matrixWorld = new D3DXMATRIX();
	D3DXMatrixIdentity(matrixWorld);
	g_matrixWorld = matrixWorld;
}

VertexBuffer::~VertexBuffer(void)
{
	if(g_VertexBuffer != NULL) g_VertexBuffer->Release();
}

void VertexBuffer::LoadFile(char *filename)
{
	FILE *file = fopen(filename, "r+b");

	fread(&m_VerticesCount, sizeof(UINT), 1, file);
	fread(&m_VertexSize, sizeof(UINT), 1, file);
	fread(&m_VertexFVF, sizeof(DWORD), 1, file);

	m_Vertices = new char[m_VerticesCount * m_VertexSize];
	fread(m_Vertices, m_VertexSize, m_VerticesCount, file);

	fclose(file);

	m_CreateVertexBuffer();
}

void VertexBuffer::SaveFile(char* filename)
{
	FILE *file = fopen(filename, "w");

	fwrite(&m_VerticesCount, sizeof(UINT), 1, file);
	fwrite(&m_VertexSize, sizeof(UINT), 1, file);
	fwrite(&m_VertexFVF, sizeof(DWORD), 1, file);

	fwrite(m_Vertices, m_VertexSize, m_VerticesCount, file);

	fclose(file);
}

void VertexBuffer::SetVertexType(DWORD fvf, UINT size)
{
	m_VertexFVF = fvf;
	m_VertexSize = size;
}

void VertexBuffer::SetVertices(void* inVertices[], UINT count)
{
	m_VerticesCount = count;
	m_Vertices = inVertices;

	m_CreateVertexBuffer();
}

void VertexBuffer::SetMatrix(D3DMATRIX* matrix)
{
	memcpy(g_matrixWorld, matrix, sizeof(D3DXMATRIX));
}

void VertexBuffer::SetTexture(LPDIRECT3DTEXTURE9 texture)
{
	g_tTexture = texture;
}

void VertexBuffer::m_CreateVertexBuffer()
{
	HRESULT r = 0;
	UINT size = m_VerticesCount * m_VertexSize;
	
	r = g_Device->CreateVertexBuffer(size, 0, m_VertexFVF , D3DPOOL_DEFAULT, &g_VertexBuffer, NULL);

	if (FAILED(r))
	{
		App::MsgBox(L"VertexBuffer konnte nicht erstellt werden.", MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	void* pVertices;
	r = g_VertexBuffer->Lock(0, size, (void**)&pVertices, 0);

	if (FAILED(r))
	{
		App::MsgBox(L"Speicher konnte nicht reserviert werden.", MB_OK | MB_ICONEXCLAMATION);
	}

	memcpy(pVertices, m_Vertices, size);
    g_VertexBuffer->Unlock();
}

void VertexBuffer::Render()
{
	g_Device->SetTransform(D3DTS_WORLD, g_matrixWorld);

	if (SUCCEEDED(g_Device->BeginScene()))
	{
		if (g_tTexture != NULL)
		{
			g_Device->SetTexture(0, g_tTexture);
		}

		g_Device->SetFVF(m_VertexFVF);
		g_Device->SetStreamSource(0, g_VertexBuffer, 0, m_VertexSize);
		g_Device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_VerticesCount / 3);

		g_Device->EndScene();
	}
}

/*ULONG IDirectXElement::Release()
{
	return --VertexBuffer::g_lInstances;
}*/