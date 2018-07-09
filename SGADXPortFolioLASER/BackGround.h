#pragma once

class BackGround 
{
	static shared_ptr<BackGround> instance;

	struct TexturedVertex 
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 uv;
		static DWORD fvf;

		TexturedVertex() {}
		TexturedVertex(float x, float y, float u, float v)
		{
			position = { x, y, 0.9f };
			uv = { u, v };
		}
	};
	BackGround();
public:
	TexturedVertex BackGroundPoint[6];
	static shared_ptr<BackGround> Get();
	void Render();
};