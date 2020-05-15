// VertexBufferWithIndexes.cpp: Indizierter VertexBuffer
// by Tim Boden
//

#define _CRT_SECURE_NO_WARNINGS			// Komische 'fopen' warnung ausblenden

#include <stdio.h>
#include "Application.h"
#include "VertexBufferWithIndexes.h"

VertexBufferWithIndexes::VertexBufferWithIndexes(LPDIRECT3DDEVICE9 device)
	: VertexBuffer(device)
{
	m_VertexFVF = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	m_VertexSize = sizeof(VertexRHW);
}

VertexBufferWithIndexes::~VertexBufferWithIndexes(void)
{
	if (g_IndexBuffer != NULL) g_IndexBuffer->Release();
}

void VertexBufferWithIndexes::LoadFile(char *filename)
{
	FILE *file = fopen(filename, "r+b");

	fread(&m_VerticesCount, sizeof(UINT), 1, file);
	fread(&m_VertexSize, sizeof(UINT), 1, file);
	fread(&m_VertexFVF, sizeof(DWORD), 1, file);
	fread(&m_IndexesCount, sizeof(UINT), 1, file);

	m_Vertices = new char[m_VerticesCount * m_VertexSize];
	fread(m_Vertices, m_VertexSize, m_VerticesCount, file);

	m_Indexes = new WORD[m_IndexesCount];
	fread(m_Indexes, sizeof(WORD), m_IndexesCount, file);

	fclose(file);

	m_CreateIndexBuffer();
	m_CreateVertexBuffer();
}

void VertexBufferWithIndexes::SaveFile(char* filename)
{
	FILE *file = fopen(filename, "w");

	fwrite(&m_VerticesCount, sizeof(UINT), 1, file);
	fwrite(&m_VertexSize, sizeof(UINT), 1, file);
	fwrite(&m_VertexFVF, sizeof(DWORD), 1, file);

	fwrite(m_Vertices, m_VertexSize, m_VerticesCount, file);

	fwrite(m_Indexes, sizeof(WORD), m_IndexesCount, file);

	fclose(file);
}

void VertexBufferWithIndexes::SetIndexes(WORD inIndexes[], UINT count)
{
	m_IndexesCount = count;
	m_Indexes = inIndexes;

	m_CreateIndexBuffer();
}

void VertexBufferWithIndexes::m_CreateIndexBuffer()
{
	HRESULT r = 0;
	UINT size = m_IndexesCount * sizeof(WORD);
	
	r = g_Device->CreateIndexBuffer(size, 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &g_IndexBuffer, NULL);

	if (FAILED(r))
	{
		App::MsgBox(L"IndexBuffer konnte nicht erstellt werden.", MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	void* pIndexes;
	r = g_IndexBuffer->Lock(0, size, (void**)&pIndexes, 0);

	if (FAILED(r))
	{
		App::MsgBox(L"Speicher konnte nicht reserviert werden.", MB_OK | MB_ICONEXCLAMATION);
	}

	memcpy(pIndexes, m_Indexes, size);
    g_IndexBuffer->Unlock();
}

void VertexBufferWithIndexes::Render()
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
		g_Device->SetIndices(g_IndexBuffer);
		g_Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_VerticesCount, 0, m_IndexesCount / 3);	

		g_Device->EndScene();
	}
}