#pragma once

class BackGround 
{
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
};