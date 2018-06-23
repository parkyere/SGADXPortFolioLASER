#pragma once
struct Vertex
{
	D3DXVECTOR3 position;
	DWORD color;

	static const DWORD fvf{ D3DFVF_XYZRHW | D3DFVF_DIFFUSE };
	Vertex() {}
	Vertex(float x, float y, DWORD color) : position{ x,y,0.f }, color{ color }
	{}
	Vertex(float x, float y, float z, DWORD color) : position{ x,y,z }, color{ color }
	{}
};