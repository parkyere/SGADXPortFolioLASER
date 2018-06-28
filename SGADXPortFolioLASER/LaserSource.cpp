#include "stdafx.h"

LaserSource::LaserSource()
	:SingleColored{ BeamColor::Red , ComponentShape},
	isPulsed{ true }
{
	ComponentDirection = Direction::Down;
	ComponentShape.emplace_back(20.f, 0.f, 0.f, COLOR_R);
	ComponentShape.emplace_back(0.f, 20.f, 0.f, COLOR_R);
	ComponentShape.emplace_back(-20.f, 0.f, 0.f, COLOR_R);
	ComponentShape.emplace_back(10.f, -20.f, 0.f, COLOR_R);
	ComponentShape.emplace_back(10.f, 0.f, 0.f, COLOR_R);
	ComponentShape.emplace_back(-10.f, -20.f, 0.f, COLOR_R);
	ComponentShape.emplace_back(-10.f, 0.f, 0.f, COLOR_R);
}

LaserSource::LaserSource(float x, float y, Direction myDir, BeamColor myColor) : LaserSource{}
{
	SetDir(myDir);
	SetPos(x, y);
	SetColor(myColor);
}

void LaserSource::Render()
{
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 1, &ComponentShape[0], sizeof(Vertex));
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &ComponentShape[3], sizeof(Vertex));
}