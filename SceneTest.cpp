// Scene.cpp: Beschreibt eine Test-Szene
// by Tim Boden
//

#define _CRT_SECURE_NO_WARNINGS			// Komische Sicherheitswarnung ausblenden

#include "SceneTest.h"
#include "Application.h"

SceneTest::SceneTest(LPDIRECT3DDEVICE9 device, List<IDirectXElement>* elements)
	: IDirectXScene(device, elements)
{
}

SceneTest::~SceneTest(void)
{
}

bool SceneTest::LoadScene()
{
	m_meshBox = NULL;

	LoadMesh();
	LoadVertexBuffer();
	LoadIndexedVertexBuffer();

	// Kamera erstellen und hinzufügen
	m_Camera = new Camera(g_Device);
	m_listElements->Add(m_Camera);

	// Info Label erstellen und hinzufügen
	m_labelInfo = new Label(g_Device);

	//Button erstellen und hinzufügen
	RECT rect;
	rect.top    = 175;
	rect.left   = 10;
	rect.bottom = 200;
	rect.right  = 140;

	Button* button = new Button(g_Device, &rect);
	button->SetLabelText(L"Test");
	button->SetBackgroundColor(0xAAFFFFFF);

	m_listElements->Add(m_IndexedVertexBuffer);
	m_listElements->Add(m_VertexBuffer);
	m_listElements->Add(m_labelInfo);
	m_listElements->Add(button);
	//if (m_meshBox != NULL) m_listElements->Add(m_meshBox);

	return true;
}

// Mesh laden
void SceneTest::LoadMesh()
{
	LPD3DXMESH mesh;
	LPD3DXBUFFER buffer;

	HRESULT r = 0; // = D3DXCreateBox(g_Device, 5.0f, 5.0f, 5.0f, &mesh, &buffer);

	D3DXCreateSphere(g_Device, 1.0f,  25, 25, &mesh, &buffer);

	if (FAILED(r))
	{
		App::MsgBox(L"Mesh konnte nicht erstellt werden.", MB_OK | MB_ICONEXCLAMATION);
	}
	else
	{
		m_meshBox = new Mesh(g_Device, mesh, buffer, 1);
	}

	/*LPDIRECT3DTEXTURE9 texture;
	D3DXCreateTextureFromFile(g_Device, L"Media\\skybox.jpg", &texture);
	m_meshBox->SetTexture(0, texture);*/
}

void SceneTest::LoadVertexBuffer()
{
	m_VertexBuffer = new VertexBufferWithIndexes(g_Device);

	VertexTextured vertices[] = {
        { -1.0f, -1.0f, 0.0f,  1.0f,  1.0f, },
        {  1.0f, -1.0f, 0.0f, -1.0f,  1.0f, },
        {  1.0f,  1.0f, 0.0f, -1.0f, -1.0f, },
        { -1.0f,  1.0f, 0.0f,  1.0f, -1.0f, },
	};

	WORD indexes[] = {
		0, 1, 2, 0, 2, 3,
	};

	LPDIRECT3DTEXTURE9 texture;
	D3DXCreateTextureFromFile(g_Device, L"data\\space.jpg", &texture);

	m_VertexBuffer->SetTexture(texture);
	m_VertexBuffer->SetIndexes(indexes, sizeof(indexes) / sizeof(WORD));
	m_VertexBuffer->SetVertexType(VertexTextured::FVF_Flags, sizeof(VertexTextured));
	m_VertexBuffer->SetVertices((void**)&vertices, sizeof(vertices) / sizeof(VertexTextured));
}

void SceneTest::LoadIndexedVertexBuffer()
{
	m_IndexedVertexBuffer = new VertexBufferWithIndexes(g_Device);

	/*VertexColored vertices[] = {
        { -100.0f, -100.0f, -100.0f, 0xffff0000, },
        {  100.0f, -100.0f, -100.0f, 0xff0000ff, },
        {  100.0f,  100.0f, -100.0f, 0xff00ff00, },
        { -100.0f,  100.0f, -100.0f, 0xff00ffff, },
        { -100.0f, -100.0f,  100.0f, 0xffffff00, },
        {  100.0f, -100.0f,  100.0f, 0xff0000ff, },
        {  100.0f,  100.0f,  100.0f, 0xffff00ff, },
        { -100.0f,  100.0f,  100.0f, 0xffffffff, },
	};*/

	VertexTextured vertices[] = {
        { -10.0f, -10.0f, -10.0f, 0.0f, 0.0f, },
        {  10.0f, -10.0f, -10.0f, 1.0f, 0.0f, },
        {  10.0f,  10.0f, -10.0f, 0.0f, 1.0f, },
        { -10.0f,  10.0f, -10.0f, 1.0f, 0.0f, },
        { -10.0f, -10.0f,  10.0f, 0.0f, 1.0f, },
        {  10.0f, -10.0f,  10.0f, 1.0f, 0.0f, },
        {  10.0f,  10.0f,  10.0f, 0.0f, 1.0f, },
        { -10.0f,  10.0f,  10.0f, 1.0f, 0.0f, },
	};

	WORD indexes[] = {
		0, 1, 2, 0, 2, 3,
		4, 6, 7, 4, 5, 6,
		1, 2, 5, 2, 5, 6,
		0, 3, 4, 3, 4, 7,
		0, 1, 5, 0, 4, 5,
		2, 3, 6, 3, 6, 7,
	};

	LPDIRECT3DTEXTURE9 texture;
	D3DXCreateTextureFromFile(g_Device, L"data\\space.jpg", &texture);

	UINT size = sizeof(VertexTextured);

	//m_IndexedVertexBuffer->SetTexture(texture);
	m_IndexedVertexBuffer->SetVertexType(VertexTextured::FVF_Flags, size);
	m_IndexedVertexBuffer->SetIndexes(indexes, sizeof(indexes) / sizeof(WORD));
	m_IndexedVertexBuffer->SetVertices((void**)&vertices, sizeof(vertices) / size);
}

void SceneTest::Update()
{
	TCHAR* textBuffer = new TCHAR[256];
	ZeroMemory(textBuffer, sizeof(TCHAR) * 256);
	_snwprintf(
		textBuffer,
		256,
		L"Z: %f\nX: %u\nY: %u\nCX: %f\nCY: %f",
		App::dx->g_fEyeDistance,
		App::dx->m_Mouse->GetX(),
		App::dx->m_Mouse->GetY(),
		m_Camera->g_fX,
		m_Camera->g_fY
	);

	m_labelInfo->SetText(textBuffer);

	for (int i = 0; i < m_listElements->Count(); i++)
	{
		m_listElements->GetValue(i)->Update();
	}
}

void SceneTest::Render()
{
	for (int i = 0; i < m_listElements->Count(); i++)
	{
		m_listElements->GetValue(i)->Render();
	}
}