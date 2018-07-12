#pragma once

class IntroScene 
{
	static shared_ptr<IntroScene> instance;

	struct TexturedVertex
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 uv;
		static DWORD fvf;

		TexturedVertex() {}
		TexturedVertex(float x, float y, float u, float v)
		{
			position = { x, y, 0.95f };
			uv = { u, v };
		}
	};
	IntroScene();
	LPDIRECT3DTEXTURE9 texture;
public:
	TexturedVertex IntroScenePoint[6];
	static shared_ptr<IntroScene> Get();
	void Render();
	void Update();
};