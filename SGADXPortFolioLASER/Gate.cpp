#include "stdafx.h"

Obstacle::Obstacle()
{
	componentName = "Obstacle";
	ComponentDirection = Direction::NoDirection;
	ComponentShape.emplace_back(-0.5f*Grid::gridSize, -0.5f*Grid::gridSize ,0x0);
	ComponentShape.emplace_back(0.5f*Grid::gridSize, -0.5f*Grid::gridSize,0x0);
	ComponentShape.emplace_back(0.5f*Grid::gridSize, 0.5f*Grid::gridSize,0x0);
	ComponentShape.emplace_back(-0.5f*Grid::gridSize, 0.5f*Grid::gridSize,0x0);
}

Obstacle::Obstacle(float x, float y)
{
	SetPos(x, y);
}

void Obstacle::Render()
{
	vector<Vertex> tempVertex;
	int shapeIndex = ComponentShape.size();

	for (int i = 0; i<shapeIndex; i++)
	{
		tempVertex.push_back(ComponentShape[i]);
		tempVertex[i].position = { tempVertex[i].position[0] + xPos, tempVertex[i].position[1] + yPos, -0.8f };
	}

	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, &tempVertex[0], sizeof(Vertex));
}

void Obstacle::beamComing(shared_ptr<BeamPulse> inBeam)
{
}
