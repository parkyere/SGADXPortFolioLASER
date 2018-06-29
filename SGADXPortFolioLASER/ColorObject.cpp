#include "stdafx.h"

ColorObject::ColorObject() : SingleColored{ BeamColor::Red , ComponentShape }
{
	ComponentDirection = Direction::NoDirection;
	ComponentShape.emplace_back(-0.5f*Grid::gridSize, -0.5f*Grid::gridSize, COLOR_R);
	ComponentShape.emplace_back(0.5f*Grid::gridSize, -0.5f*Grid::gridSize, COLOR_R);
	ComponentShape.emplace_back(0.5f*Grid::gridSize, 0.5f*Grid::gridSize, COLOR_R);
	ComponentShape.emplace_back(-0.5f*Grid::gridSize, 0.5f*Grid::gridSize, COLOR_R);
}

ColorObject::ColorObject(float x, float y, BeamColor myColor) : ColorObject{}
{
	SetPos(x, y);
	SetColor(myColor);
}

void ColorObject::Render()
{
	vector<Vertex> tempVertex;
	int shapeIndex = ComponentShape.size();

	for (int i = 0; i<shapeIndex; i++)
	{
		tempVertex.push_back(ComponentShape[i]);
		tempVertex[i].position = { tempVertex[i].position[0] + xPos, tempVertex[i].position[1] + yPos, 0.f };
	}

	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, &tempVertex[0], sizeof(Vertex));
}
