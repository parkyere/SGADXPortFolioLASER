#include "stdafx.h"

Mirror::Mirror()
{
	ComponentDirection = Direction::Down;
	ComponentShape.emplace_back(-0.5f*Grid::gridSize, 0.5f*Grid::gridSize, 0x00000000);
	ComponentShape.emplace_back(0.5f*Grid::gridSize, -0.5f*Grid::gridSize, 0x00000000);
}

Mirror::Mirror(float x, float y, Direction myDir) : Mirror{}
{
	SetDir(myDir);
	SetPos(x, y);
}

void Mirror::Render()
{
	vector<Vertex> tempVertex;
	int shapeIndex = ComponentShape.size();

	for (int i = 0; i<shapeIndex; i++)
	{
		tempVertex.push_back(ComponentShape[i]);
		tempVertex[i].position = { tempVertex[i].position[0] + xPos, tempVertex[i].position[1] + yPos, 0.f };
	}

	DEVICE->DrawPrimitiveUP(D3DPT_LINELIST, 1, &tempVertex[0], sizeof(Vertex));
}

void Mirror::beamComing(shared_ptr<BeamPulse> inBeam)
{
}
