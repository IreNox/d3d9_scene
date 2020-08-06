#pragma once

#include "IDirectXScene.h"

class SceneLoading
	: public IDirectXScene
{
public:
	SceneLoading(LPDIRECT3DDEVICE9 device, List<IDirectXElement>* elements);
	~SceneLoading(void);

	bool LoadScene();

	void Render();

	void SetParams(float percent, TCHAR* text);
private:
	Label* m_labelText;
	VertexBufferWithIndexes* m_ivbBar;
};

