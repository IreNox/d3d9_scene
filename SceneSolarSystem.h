#pragma once

#include <time.h>

#include "IDirectXScene.h"

class SceneSolarSystem
	: public IDirectXScene
{
public:
	SceneSolarSystem(LPDIRECT3DDEVICE9 device, List<IDirectXElement>* elements);
	~SceneSolarSystem(void);

	bool LoadScene();

	void Render();
	void Update();
private:
	time_t g_lTime;
	float g_fRotationEarth;
	float g_fRotationToSun;
	float g_fRotationToEarth;
	
	Label* m_labelInfo;

	Camera* m_Camera;

	Mesh* m_meshSun;
	Mesh* m_meshMoon;
	Mesh* m_meshEarth;

	VertexBufferWithIndexes* m_ivbSkybox;

	D3DLIGHT9* g_lightSun;

	bool LoadLight();
	bool LoadSkyBox();
	bool LoadPlanets();

	void UpdateMatrices();
};

