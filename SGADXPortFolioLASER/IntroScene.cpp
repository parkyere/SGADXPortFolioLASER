#include "stdafx.h"

DWORD IntroScene::TexturedVertex::fvf = D3DFVF_XYZ | D3DFVF_TEX1;
shared_ptr<IntroScene> IntroScene::instance{ nullptr };

IntroScene::IntroScene()
{
	IntroScenePoint[0] = TexturedVertex(0, 0, 0, 0);
	IntroScenePoint[1] = TexturedVertex(winWidth, 0, 1.f, 0);
	IntroScenePoint[2] = TexturedVertex(0, winHeight, 0, 1.f);
	IntroScenePoint[3] = TexturedVertex(0, winHeight, 0, 1.f);
	IntroScenePoint[4] = TexturedVertex(winWidth, 0, 1.f, 0);
	IntroScenePoint[5] = TexturedVertex(winWidth, winHeight, 1.f, 1.f);

	D3DXIMAGE_INFO info;
	DEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);
	D3DXCreateTextureFromFileEx(DEVICE,
		L"Intro.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_FILTER_NONE,
		D3DX_FILTER_NONE,
		NULL,
		&info,
		NULL,
		&texture
	);
}

shared_ptr<IntroScene> IntroScene::Get()
{
	if (instance == nullptr)
	{
		instance = shared_ptr<IntroScene>(new IntroScene);
	}
	return instance;
}

void IntroScene::Render()
{
	D3DVIEWPORT9 viewport;
	DEVICE->GetViewport(&viewport);
	D3DXMATRIX projection;
	D3DXMatrixOrthoOffCenterLH(&projection, 0.0f,
		viewport.Width, viewport.Height, 0.0f, -1, 1);
	DEVICE->SetTransform(D3DTS_PROJECTION, &projection);
	DEVICE->SetTexture(0, texture);
	DEVICE->SetFVF(IntroScene::TexturedVertex::fvf);
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, IntroScenePoint, sizeof(TexturedVertex));
}

void IntroScene::Update()
{
	if (KEYBOARD->KeyDown(VK_RETURN)|| KEYBOARD->KeyDown(VK_SPACE))
	{
		MAINGAME->setState(GameState::GamePlayEditMode);
		MAINGAME->PrepareGame();
	}
	else if (KEYBOARD->KeyDown(VK_F10)) 
	{
		MAINGAME->setState(GameState::MapEditorEditMode);
		MAINGAME->PrepareEditor();
	}
}
