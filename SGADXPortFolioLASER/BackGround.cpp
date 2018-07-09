#include "stdafx.h"

DWORD BackGround::TexturedVertex::fvf = D3DFVF_XYZ | D3DFVF_TEX1 ;
shared_ptr<BackGround> BackGround::instance{ nullptr };

BackGround::BackGround()
{
	BackGroundPoint[0] = TexturedVertex(0, 0, 0, 0);
	BackGroundPoint[1] = TexturedVertex(winWidth, 0, 1.f, 0);
	BackGroundPoint[2] = TexturedVertex(0, winHeight, 0, 1.f);
	BackGroundPoint[3] = TexturedVertex(0, winHeight, 0, 1.f);
	BackGroundPoint[4] = TexturedVertex(winWidth, 0, 1.f, 0);
	BackGroundPoint[5] = TexturedVertex(winWidth, winHeight, 1.f, 1.f);

	D3DXIMAGE_INFO info;
	DEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);
	D3DXCreateTextureFromFileEx(DEVICE,
		L"Laser3.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,//D3DPOOL_SYSTEMMEM,//D3DPOOL_SCRATCH,//D3DPOOL_FORCE_DWORD,//D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_FILTER_NONE,
		NULL,
		&info,
		NULL,
		&(MAINGAME->texture)
	);
}

shared_ptr<BackGround> BackGround::Get()
{
	if (instance == nullptr) 
	{
		instance = shared_ptr<BackGround>(new BackGround);
	}
	return instance;
}

void BackGround::Render()
{
	DEVICE->SetTexture(0, MAINGAME->texture);
	DEVICE->SetFVF(BackGround::TexturedVertex::fvf);
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, BackGroundPoint, sizeof(TexturedVertex));
}
