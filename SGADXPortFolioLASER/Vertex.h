#pragma once
struct Vertex
{
	D3DXVECTOR4 position;
	DWORD color;
	DWORD fvf{ D3DFVF_XYZRHW | D3DFVF_DIFFUSE };
	Vertex() {}
	Vertex(float x, float y, DWORD color) : position{ x,y,0.f,1.f }, color{ color }
	{}
	Vertex(float x, float y, float z, DWORD color) : position{ x,y,z,1.f }, color{ color }
	{}
};