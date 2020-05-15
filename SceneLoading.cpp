// SceneLoading.cpp: Scene die Während des lade vorgangs angezeigt wird
// by Tim Boden
//

#include "SceneLoading.h"
#include "Application.h"

SceneLoading::SceneLoading(LPDIRECT3DDEVICE9 device, List<IDirectXElement>* elements)
	: IDirectXScene(device, elements)
{
}

SceneLoading::~SceneLoading(void)
{
	delete(m_ivbBar);
	delete(m_labelText);
}

bool SceneLoading::LoadScene()
{
	m_labelText = new Label(g_Device);
	m_ivbBar = new VertexBufferWithIndexes(g_Device);

	WORD indexes[] = {
		0, 1, 2, 1, 2, 3,
	};

	m_ivbBar->SetIndexes(indexes, sizeof(indexes) / sizeof(WORD));

	SetParams(1.0f, L"Lade...");

	return true;
}

void SceneLoading::SetParams(float p, TCHAR* text)
{
	float w1p = (float)App::dx->g_Params.BackBufferWidth / 100;
	float h1p = (float)App::dx->g_Params.BackBufferHeight / 100;

	VertexRHW vertices[] = {
        { w1p * 5.0f,         h1p * 85.0f, 0.0f, 1.0f, 0xFF005500, },
        { w1p * 5.0f,         h1p * 90.0f, 0.0f, 1.0f, 0xFF005500, },
        { w1p * (p - 10.0f),  h1p * 85.0f, 0.0f, 1.0f, 0xFF00FF00, },
        { w1p * (p - 10.0f),  h1p * 90.0f, 0.0f, 1.0f, 0xFF00FF00, },
	};

	m_ivbBar->SetVertexType(VertexRHW::FVF_Flags, sizeof(VertexRHW));
	m_ivbBar->SetVertices((void**)&vertices, sizeof(vertices) / sizeof(VertexRHW));

	RECT rect;
	ZeroMemory(&rect, sizeof(rect));

	rect.left   = (long)(w1p * 5.0f);
	rect.right  = (long)(w1p * 95.0f);
	rect.top    = (long)(h1p * 70.0f);
	rect.bottom = (long)(h1p * 85.0f);

	m_labelText->SetColor(0xFFFFFFFF);
	m_labelText->SetText(text);
	m_labelText->SetRect(&rect);

	App::dx->Render();
}

void SceneLoading::Render()
{
	m_labelText->Render();
	m_ivbBar->Render();
}