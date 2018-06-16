#pragma once
struct BoundVertex
{
	D3DXVECTOR3 position;
	DWORD color;

	static DWORD fvf;

	BoundVertex() {}
	BoundVertex(float x, float y, DWORD color)
	{
		position = { x, y, 0.0f };
		this->color = color;
	}
};