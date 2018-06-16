#pragma once
struct Vertex
{
	D3DXVECTOR3 position;
	D3DXVECTOR2 uv;

	Vertex() {}
	Vertex(float x, float y, float u, float v)
	{
		position = { x, y, 0.0f };
		uv = { u, v };
	}

	static const DWORD fvf{ D3DFVF_XYZRHW | D3DFVF_DIFFUSE };
};