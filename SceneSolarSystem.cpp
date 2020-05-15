// SceneSolarSystem.cpp: Szene mit Sonne, Erde und Mond
// by Tim Boden
//

#define _CRT_SECURE_NO_WARNINGS			// Komische Sicherheitswarnung ausblenden

#include "Application.h"
#include "SceneSolarSystem.h"

SceneSolarSystem::SceneSolarSystem(LPDIRECT3DDEVICE9 device, List<IDirectXElement>* elements)
	: IDirectXScene(device, elements)
{
	// Werte initialisieren
	g_lTime = 0;

	g_fRotationEarth = 0.0f;
	g_fRotationToSun = 0.0f;
	g_fRotationToEarth = 0.0f;
}

void SceneSolarSystem::Render()
{
	// Liste durchlaufen und rendern
	for (int i = 0; i < m_listElements->Count(); i++)
	{
		m_listElements->GetValue(i)->Render();
	}
}

void SceneSolarSystem::Update()
{
	// Zeit differenz zum letzten Aufruf berechnen
	time_t time = clock();
	time = time - g_lTime;

	float pix2 = D3DX_PI * 2;
	float diff = pix2 / CLOCKS_PER_SEC * time;
	diff /= 10;

	g_fRotationEarth += diff / 0.1f;	// Erdrotation
	g_fRotationToSun += diff / 3.65f;	// Rotation der Erde um die Sonne
	g_fRotationToEarth += diff / 0.29f; // Rotation des Mondes um die Erde

	// Werte zurücksetzen, wenn zu hoch
	if (g_fRotationEarth > pix2) g_fRotationEarth -= pix2;
	if (g_fRotationToSun > pix2) g_fRotationToSun -= pix2;
	if (g_fRotationToEarth > pix2) g_fRotationToEarth -= pix2;

	// Kamera updateten
	m_Camera->Update();

	// Matrizen updaten
	UpdateMatrices();

	// Zeit speichern
	g_lTime = clock();
}

void SceneSolarSystem::UpdateMatrices()
{
	// WorldMatrix für Sonne: Auf 5% der ursprünglichen Größe scalieren
	D3DXMATRIX matWorld;
	D3DXMatrixScaling(&matWorld, 0.05f, 0.05f, 0.05f);
	g_Device->SetTransform(D3DTS_WORLD, &matWorld);
	m_meshSun->SetMatrix(&matWorld);

	// WorldMatrix für Erde: Um eigene Achse rotieren und um die Sonne bewegen
	D3DXMATRIX matWorldRotation;
	D3DXMATRIX matWorldTranslation;
	D3DXMatrixRotationY(&matWorldRotation, g_fRotationEarth);
	D3DXMatrixTranslation(
		&matWorldTranslation,
		sinf(g_fRotationToSun) * 150,
		0.0f,
		cosf(g_fRotationToSun) * 150
	);
	D3DXMatrixMultiply(&matWorld, &matWorldRotation, &matWorldTranslation);	
	m_meshEarth->SetMatrix(&matWorld);

	// WorldMatrix für Mond: Um Erde bewegen
	D3DXMATRIX matWorldTranslation2;
	D3DXMatrixTranslation(
		&matWorldTranslation2,
		sinf(g_fRotationToEarth) * 25,
		cosf(g_fRotationToEarth) * 25,
		0.0f
	);
	D3DXMatrixMultiply(&matWorld, &matWorldTranslation, &matWorldTranslation2);	
	m_meshMoon->SetMatrix(&matWorld);
}

bool SceneSolarSystem::LoadScene()
{
	bool ok = true;
	App::dx->m_sceneLoading->SetParams(10, L"Sonnensystem wird geladen...");

	// Kamera laden
	m_Camera = new Camera(g_Device);
	m_Camera->g_fX = -0.9f;
	m_Camera->g_fY = 1.19f;
	App::dx->g_fEyeDistance = 350.0f;
	m_listElements->Add(m_Camera);

	// Info Label erstellen und hinzufügen
	m_labelInfo = new Label(g_Device);
	m_labelInfo->SetText(L"Linke-Maustaste: Kamera bewegen\nMittlere-Maustaste: Licht an/aus\nRechte-Maustaste: Wireframe an/aus");
	m_listElements->Add(m_labelInfo);
	
	// Licht erstellen
	App::dx->m_sceneLoading->SetParams(20, L"Licht laden...");
	ok = LoadLight();

	// SkyBoy laden
	App::dx->m_sceneLoading->SetParams(30, L"Skybox laden...");
	ok = LoadSkyBox() && ok;

	// Planeten laden
	ok = LoadPlanets() && ok;

	return ok;
}

bool SceneSolarSystem::LoadLight()
{
	float f = 100.0f;
	Light* light;
	
	light = new Light(g_Device);
	light->SetPosition(D3DXVECTOR3(-f, 0.0f, 0.0f));
	m_listElements->Add(light);

	light = new Light(g_Device);
	light->SetPosition(D3DXVECTOR3(f, 0.0f, 0.0f));
	m_listElements->Add(light);

	light = new Light(g_Device);
	light->SetPosition(D3DXVECTOR3(0.0f, -f, 0.0f));
	m_listElements->Add(light);

	light = new Light(g_Device);
	light->SetPosition(D3DXVECTOR3(0.0f, f, 0.0f));
	m_listElements->Add(light);

	light = new Light(g_Device);
	light->SetPosition(D3DXVECTOR3(0.0f, 0.0f, -f));
	m_listElements->Add(light);

	light = new Light(g_Device);
	light->SetPosition(D3DXVECTOR3(0.0f, 0.0f, f));
	m_listElements->Add(light);

	return true;
}

bool SceneSolarSystem::LoadSkyBox()
{
	m_ivbSkybox = new VertexBufferWithIndexes(g_Device);

	VertexTextured vertices[] = {
		// Vorne
        { -1000.0f, -1000.0f, -1000.0f, 0.0f, 0.0f, },	//  0 -  0
        {  1000.0f, -1000.0f, -1000.0f, 1.0f, 0.0f, },	//  1 -  1
        {  1000.0f,  1000.0f, -1000.0f, 1.0f, 1.0f, },	//  2 -  2
        { -1000.0f,  1000.0f, -1000.0f, 0.0f, 1.0f, },	//  3 -  3
		// Hinten
        { -1000.0f, -1000.0f,  1000.0f, 0.0f, 0.0f, },	//  4 -  4
        {  1000.0f, -1000.0f,  1000.0f, 1.0f, 0.0f, },	//  5 -  5
        {  1000.0f,  1000.0f,  1000.0f, 1.0f, 1.0f, },	//  6 -  6
        { -1000.0f,  1000.0f,  1000.0f, 0.0f, 1.0f, },	//  7 -  7
		// Links
        { -1000.0f, -1000.0f,  1000.0f, 0.0f, 1.0f, },	//  4 -  8
        { -1000.0f, -1000.0f, -1000.0f, 0.0f, 0.0f, },	//  0 -  9
        { -1000.0f,  1000.0f, -1000.0f, 1.0f, 0.0f, },	//  3 - 10
        { -1000.0f,  1000.0f,  1000.0f, 1.0f, 1.0f, },	//  7 - 11
		// Rechts
        {  1000.0f, -1000.0f,  1000.0f, 0.0f, 1.0f, },	//  5 - 12
        {  1000.0f, -1000.0f, -1000.0f, 0.0f, 0.0f, },	//  1 - 13
        {  1000.0f,  1000.0f, -1000.0f, 1.0f, 0.0f, },	//  2 - 14
        {  1000.0f,  1000.0f,  1000.0f, 1.0f, 1.0f, },	//  6 - 15
		// Oben
        { -1000.0f, -1000.0f, -1000.0f, 0.0f, 0.0f, },	//  0 - 16
        {  1000.0f, -1000.0f, -1000.0f, 1.0f, 0.0f, },	//  1 - 17
        { -1000.0f, -1000.0f,  1000.0f, 0.0f, 1.0f, },	//  4 - 18
        {  1000.0f, -1000.0f,  1000.0f, 1.0f, 1.0f, },	//  5 - 19
		// Unten
        { -1000.0f,  1000.0f, -1000.0f, 0.0f, 0.0f, },	//  3 - 20
        {  1000.0f,  1000.0f, -1000.0f, 1.0f, 0.0f, },	//  2 - 21
        { -1000.0f,  1000.0f,  1000.0f, 0.0f, 1.0f, },	//  7 - 22
        {  1000.0f,  1000.0f,  1000.0f, 1.0f, 1.0f, },	//  6 - 23
	};

	WORD indexes[] = {
		0,   1,  2, 0,   2,  3,	// Vorne
		4,   5,  6, 4,   6,  7,	// Hinten
		8,   9, 10, 8,  10, 11,	// Links
		12, 13, 14, 12, 14, 15,	// Rechts
		16, 17, 18, 17, 18, 19,	// Oben
		20, 21, 22, 21, 22, 23,	// Unten
	};

	LPDIRECT3DTEXTURE9 texture;
	HRESULT r = D3DXCreateTextureFromFile(g_Device, L"data\\space.jpg", &texture);

	if (FAILED(r))
	{
		App::FailBox(L"Textur konnte nicht geladen werden.", r);
		return false;
	}

	UINT size = sizeof(VertexTextured);

	m_ivbSkybox->SetTexture(texture);
	m_ivbSkybox->SetVertexType(VertexTextured::FVF_Flags, size);
	m_ivbSkybox->SetIndexes(indexes, sizeof(indexes) / sizeof(WORD));
	m_ivbSkybox->SetVertices((void**)&vertices, sizeof(vertices) / size);

	m_listElements->Add(m_ivbSkybox);

	return true;
}

bool SceneSolarSystem::LoadPlanets()
{
	HRESULT* r = new HRESULT[6];
	LPD3DXMESH mesh = NULL;
	LPD3DXBUFFER buffer = NULL;
	LPDIRECT3DTEXTURE9 texture = NULL;
	DWORD num = NULL;

	// Sonne
	App::dx->m_sceneLoading->SetParams(50, L"Sonne laden...");
	r[0] = D3DXLoadMeshFromX(L"data\\sun.x", D3DXMESH_MANAGED, g_Device, NULL, &buffer, NULL, &num, &mesh);
	r[1] = D3DXCreateTextureFromFile(g_Device, L"data\\sun.jpg", &texture);
	m_meshSun = new Mesh(g_Device, mesh, buffer, num);
	m_meshSun->SetTexture(0, texture);

	// Mond
	App::dx->m_sceneLoading->SetParams(70, L"Mond laden...");
	r[2] = D3DXLoadMeshFromX(L"data\\moon.x", D3DXMESH_MANAGED, g_Device, NULL, &buffer, NULL, &num, &mesh);
	r[3] = D3DXCreateTextureFromFile(g_Device, L"data\\moon.jpg", &texture);
	m_meshMoon = new Mesh(g_Device, mesh, buffer, num);
	m_meshMoon->SetTexture(0, texture);

	// Erde
	App::dx->m_sceneLoading->SetParams(90, L"Erde laden...");
	r[4] = D3DXLoadMeshFromX(L"data\\earth.x", D3DXMESH_MANAGED, g_Device, NULL, &buffer, NULL, &num, &mesh);
	r[5] = D3DXCreateTextureFromFile(g_Device, L"data\\earth.jpg", &texture);
	m_meshEarth = new Mesh(g_Device, mesh, buffer, num);
	m_meshEarth->SetTexture(0, texture);

	m_listElements->Add(m_meshSun);
	m_listElements->Add(m_meshMoon);
	m_listElements->Add(m_meshEarth);

	for (int i = 0; i < 6; i++)
	{
		if (FAILED(r[i])) return false;
	}

	return true;
}

SceneSolarSystem::~SceneSolarSystem(void)
{
	// Elemente löschen
	for (int i = 0; i < m_listElements->Count(); i++)
	{
		delete(m_listElements->GetValue(i));
	}

	// Liste löschen
	delete(m_listElements);
	m_listElements = NULL;
}