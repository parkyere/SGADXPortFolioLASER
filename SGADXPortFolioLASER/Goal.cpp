#include "stdafx.h"

Goal::Goal() : SingleColored{ BeamColor::Red, ComponentShape }
{
	ComponentDirection = Direction::Down;
	ComponentShape.emplace_back(0.f, 0.f, 0.f, COLOR_R);
	ComponentShape.emplace_back(15.f, 10.f, 0.f, COLOR_R);
	ComponentShape.emplace_back(0.f, 20.f, 0.f, COLOR_R);
	ComponentShape.emplace_back(-15.f, 10.f, 0.f, COLOR_R);
	ComponentShape.emplace_back(-15.f, -20.f, 0.f, COLOR_R);
	ComponentShape.emplace_back(0.f, -10.f, 0.f, COLOR_R);
	ComponentShape.emplace_back(15.f, -20.f, 0.f, COLOR_R);
	ComponentShape.emplace_back(15.f, 10.f, 0.f, COLOR_R);
}

Goal::Goal(float x, float y, Direction myDir, BeamColor myColor) : Goal{}
{
	SetDir(myDir);
	SetPos(x, y);
	SetColor(myColor);
}

void Goal::Render()
{
	vector<Vertex> tempVertex;
	int shapeIndex = ComponentShape.size();

	for (int i = 0; i<shapeIndex; i++)
	{
		tempVertex.push_back(ComponentShape[i]);
		tempVertex[i].position = { tempVertex[i].position[0] + xPos, tempVertex[i].position[1] + yPos, 0.f };
	}

	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 6, &tempVertex[0], sizeof(Vertex));
}

void Goal::beamComing(shared_ptr<BeamPulse> inBeam)
{
}
