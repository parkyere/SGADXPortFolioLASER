#pragma once
struct Vertex
{
	D3DXVECTOR3 position;
	DWORD color;
	DWORD fvf{  D3DFVF_XYZ | D3DFVF_DIFFUSE };
	Vertex() {}
	Vertex(float x, float y, DWORD color) : position{ x,y,0.f }, color{ color }
	{}
	Vertex(float x, float y, float z, DWORD color) : position{ x,y,z}, color{ color }
	{}
};