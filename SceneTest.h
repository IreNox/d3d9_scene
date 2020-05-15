#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "IDirectXScene.h"

class SceneTest
	: public IDirectXScene
{
public:
	SceneTest(LPDIRECT3DDEVICE9 device, List<IDirectXElement>* elements);
	~SceneTest(void);

	bool LoadScene();

	void Render();
	void Update();

private:
	Camera* m_Camera;

	Mesh* m_meshBox;
	Label* m_labelInfo;
	VertexBufferWithIndexes* m_VertexBuffer;
	VertexBufferWithIndexes* m_IndexedVertexBuffer;

	void LoadMesh();
	void LoadVertexBuffer();
	void LoadIndexedVertexBuffer();
};

