#pragma once

#include "VertexBuffer.h"

class VertexBufferWithIndexes :
	public VertexBuffer
{
public:
	UINT m_IndexesCount;
	WORD *m_Indexes;

	LPDIRECT3DINDEXBUFFER9 g_IndexBuffer;

	VertexBufferWithIndexes(LPDIRECT3DDEVICE9 device);
	~VertexBufferWithIndexes(void);

	void LoadFile(char *filename);
	void SaveFile(char *filename);

	void SetIndexes(WORD inIndexes[], UINT count);

	void Render();
private:
	VertexBufferWithIndexes(void);

	void m_CreateIndexBuffer();
};

