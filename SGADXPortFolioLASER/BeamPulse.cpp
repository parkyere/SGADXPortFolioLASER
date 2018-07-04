#include "stdafx.h"

BeamPulse::BeamPulse()
	:SingleColored{ BeamColor::Red , ComponentShape }
{
	beamLength = 0.5f*Grid::gridSize;
	beamSpeed = 0.5f*(float)(MAINGAME->callGameField().numStatePerSec)*Grid::gridSize;
	ComponentDirection = Direction::Down;
	ComponentShape.emplace_back(beamThickness / 2.f, 0.f, 0.f, COLOR_R);
	ComponentShape.emplace_back(-beamThickness / 2.f, 0.f, 0.f, COLOR_R);
	ComponentShape.emplace_back(-beamThickness / 2.f, -beamLength, 0.f, COLOR_R);
	ComponentShape.emplace_back(beamThickness / 2.f, -beamLength, 0.f, COLOR_R);
}
BeamPulse::BeamPulse(float x, float y, Direction myDir, BeamColor myColor, time_point<steady_clock>& infiredTime) : BeamPulse{}
{
	SetDir(myDir);
	SetPos(x, y);
	initX = x;
	initY = y;
	SetColor(myColor);
	firedTime = infiredTime;
}

//BeamPulse::BeamPulse(const float x, const float y, const Direction myDir, const BeamColor myColor, const time_point<steady_clock>& inFiredTime) 
//	: BeamPulse{(float)(x),(float)(y),(Direction)(myDir),(BeamColor)myColor, (time_point<steady_clock>&) inFiredTime}
//{
//}

void BeamPulse::Update(time_point<steady_clock>& thisTime)
{
	switch (getDirection())
	{
	case Direction::Up:
		SetPos(initX, initY - beamSpeed * 0.001f*(float)duration_cast<milliseconds>(thisTime - firedTime).count());
		break;
	case Direction::Down:
		SetPos(initX, initY + beamSpeed * 0.001f*(float)duration_cast<milliseconds>(thisTime - firedTime).count());
		break;
	case Direction::Right:
		SetPos(initX + beamSpeed * 0.001f*(float)duration_cast<milliseconds>(thisTime - firedTime).count(), initY);
		break;
	case Direction::Left:
		SetPos(initX - beamSpeed * 0.001f*(float)duration_cast<milliseconds>(thisTime - firedTime).count(), initY);
		break;
	}
}

void BeamPulse::Render()
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
