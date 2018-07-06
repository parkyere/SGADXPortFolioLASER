#include "stdafx.h"

BeamBeingAbsorbed::BeamBeingAbsorbed() : SingleColored{ BeamColor::Red , ComponentShape }
{
	beamLength = 0.5f*Grid::gridSize;
	beamSpeed = 0.5f*(float)(MAINGAME->callGameField().numStatePerSec)*Grid::gridSize;
	thickness = BeamPulse::beamThickness;
	ComponentDirection = Direction::Down;
	ComponentShape.emplace_back(thickness / 2.f, 0.f, 0.f, COLOR_R);
	ComponentShape.emplace_back(-thickness / 2.f, 0.f, 0.f, COLOR_R);
	ComponentShape.emplace_back(-thickness / 2.f, -beamLength, 0.f, COLOR_R);
	ComponentShape.emplace_back(thickness / 2.f, -beamLength, 0.f, COLOR_R);
}

BeamBeingAbsorbed::BeamBeingAbsorbed(float x, float y, Direction myDir, BeamColor myColor, time_point<steady_clock>& inFiredTime) : BeamBeingAbsorbed{}
{
	SetDir(myDir);
	SetPos(x, y);
	SetColor(myColor);
	firedTime = inFiredTime;
}

BeamBeingAbsorbed::BeamBeingAbsorbed(shared_ptr<BeamPulse> inBeam, time_point<steady_clock>& inTime) 
	: BeamBeingAbsorbed {inBeam->getXpos(),inBeam->getYpos(), inBeam->getDirection(), inBeam->GetColor(),inTime}
{
}

bool BeamBeingAbsorbed::UpdateNCheckForDelete(time_point<steady_clock>& thisTime)
{
	switch (getDirection())
	{
	case Direction::Up:
		ComponentShape[2].position[1] = { beamLength - beamSpeed * 0.001f*(float)duration_cast<milliseconds>(thisTime - firedTime).count() };
		ComponentShape[3].position[1] = { beamLength - beamSpeed * 0.001f*(float)duration_cast<milliseconds>(thisTime - firedTime).count() };
		break;
	case Direction::Down:
		ComponentShape[2].position[1] = { -beamLength + beamSpeed * 0.001f*(float)duration_cast<milliseconds>(thisTime - firedTime).count() };
		ComponentShape[3].position[1] = { -beamLength + beamSpeed * 0.001f*(float)duration_cast<milliseconds>(thisTime - firedTime).count() };
		break;
	case Direction::Right:
		ComponentShape[2].position[0] = { -beamLength + beamSpeed * 0.001f*(float)duration_cast<milliseconds>(thisTime - firedTime).count() };
		ComponentShape[3].position[0] = { -beamLength + beamSpeed * 0.001f*(float)duration_cast<milliseconds>(thisTime - firedTime).count() };
		break;
	case Direction::Left:
		ComponentShape[2].position[0] = { beamLength - beamSpeed * 0.001f*(float)duration_cast<milliseconds>(thisTime - firedTime).count() };
		ComponentShape[3].position[0] = { beamLength - beamSpeed * 0.001f*(float)duration_cast<milliseconds>(thisTime - firedTime).count() };
		break;
	}
	if (beamLength  <beamSpeed*0.001f*(float)duration_cast<milliseconds>(thisTime - firedTime).count())
	{
		return true;
	}
	else 
	{
		return false;
	}
}
void BeamBeingAbsorbed::Render()
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