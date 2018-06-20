#pragma once
struct Vertex
{
	D3DXVECTOR3 position;
	DWORD color;

	static const DWORD fvf{ D3DFVF_XYZRHW | D3DFVF_DIFFUSE };
};