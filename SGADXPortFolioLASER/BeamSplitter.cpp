#include "stdafx.h"

BeamSplitter::BeamSplitter() : SingleColored{ BeamColor::Red , ComponentShape }
{
	ComponentDirection = Direction::Down;

	//Body
	ComponentShape.emplace_back(4.f, 4.f, 0.f, COLOR_R);
	ComponentShape.emplace_back(4.f, 12.f, 0.f, COLOR_R);
	ComponentShape.emplace_back(-4.f, 12.f, 0.f, COLOR_R);
	ComponentShape.emplace_back(-4.f, -4.f, 0.f, COLOR_R);
	ComponentShape.emplace_back(12.f, -4.f, 0.f, COLOR_R);
	ComponentShape.emplace_back(12.f, 4.f, 0.f, COLOR_R);
	ComponentShape.emplace_back(4.f, 4.f, 0.f, COLOR_R);

	//ArrowHead1
	ComponentShape.emplace_back(0.f, 20.f, 0.f, COLOR_R);
	ComponentShape.emplace_back(-10.f, 10.f, 0.f, COLOR_R);
	ComponentShape.emplace_back(10.f, 10.f, 0.f, COLOR_R);

	//ArrowHead2
	ComponentShape.emplace_back(10.f, 10.f, 0.f, COLOR_R);
	ComponentShape.emplace_back(10.f, -10.f, 0.f, COLOR_R);
	ComponentShape.emplace_back(20.f, 0.f, 0.f, COLOR_R);
}

BeamSplitter::BeamSplitter(float x, float y, Direction myDir, BeamColor myColor) : BeamSplitter{}
{
	SetDir(myDir);
	SetPos(x, y);
	SetColor(myColor);
}

void BeamSplitter::Render()
{
	vector<Vertex> tempVertex;
	int shapeIndex = ComponentShape.size();

	for (int i = 0; i<shapeIndex; i++)
	{
		tempVertex.push_back(ComponentShape[i]);
		tempVertex[i].position = { tempVertex[i].position[0] + xPos, tempVertex[i].position[1] + yPos, 0.f };
	}


	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 1, &tempVertex[7], sizeof(Vertex));
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 5, &tempVertex[0], sizeof(Vertex));
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 1, &tempVertex[10], sizeof(Vertex));
}