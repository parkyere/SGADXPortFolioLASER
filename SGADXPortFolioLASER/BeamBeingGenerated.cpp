#include "stdafx.h"

BeamBeingGenerated::BeamBeingGenerated(): SingleColored{ BeamColor::Red , ComponentShape }
{
	beamLength = 0.5f*Grid::gridSize;
	beamSpeed = 0.5f*(float)(MAINGAME->callGameField().numStatePerSec)*Grid::gridSize;
	thickness = BeamPulse::beamThickness;
	ComponentDirection = Direction::Down;
	ComponentShape.emplace_back(thickness / 2.f, 0.f, 0.f, COLOR_R);
	ComponentShape.emplace_back(-thickness / 2.f, 0.f, 0.f, COLOR_R);
	ComponentShape.emplace_back(-thickness / 2.f, 0.f, 0.f, COLOR_R);
	ComponentShape.emplace_back(thickness / 2.f, 0.f, 0.f, COLOR_R);
}

BeamBeingGenerated::BeamBeingGenerated(float x, float y, Direction myDir, BeamColor myColor, time_point<steady_clock>& inFiredTime) : BeamBeingGenerated{}
{
	SetDir(myDir);
	SetPos(x, y);
	SetColor(myColor);
	firedTime = inFiredTime;
}

BeamBeingGenerated::BeamBeingGenerated(shared_ptr<BeamPulse> inBeam, time_point<steady_clock>& inTime)
	: BeamBeingGenerated{ inBeam->getXpos(),inBeam->getYpos(), inBeam->getDirection(), inBeam->GetColor(),inTime }
{
}

bool BeamBeingGenerated::UpdateNCheckForDelete(time_point<steady_clock>& thisTime)
{
	switch (getDirection())
	{
	case Direction::Up:
		ComponentShape[0].position[1] = { -beamSpeed * 0.001f*(float)duration_cast<milliseconds>(thisTime - firedTime).count() };
		ComponentShape[1].position[1] = { -beamSpeed * 0.001f*(float)duration_cast<milliseconds>(thisTime - firedTime).count() };
		break;
	case Direction::Down:
		ComponentShape[0].position[1] = { beamSpeed * 0.001f*(float)duration_cast<milliseconds>(thisTime - firedTime).count() };
		ComponentShape[1].position[1] = { beamSpeed * 0.001f*(float)duration_cast<milliseconds>(thisTime - firedTime).count() };
		break;
	case Direction::Right:
		ComponentShape[0].position[0] = { beamSpeed * 0.001f*(float)duration_cast<milliseconds>(thisTime - firedTime).count() };
		ComponentShape[1].position[0] = { beamSpeed * 0.001f*(float)duration_cast<milliseconds>(thisTime - firedTime).count() };
		break;
	case Direction::Left:
		ComponentShape[0].position[0] = { -beamSpeed * 0.001f*(float)duration_cast<milliseconds>(thisTime - firedTime).count() };
		ComponentShape[1].position[0] = { -beamSpeed * 0.001f*(float)duration_cast<milliseconds>(thisTime - firedTime).count() };
		break;
	}
	if (beamLength  < beamSpeed*0.001f*(float)duration_cast<milliseconds>(thisTime - firedTime).count())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void BeamBeingGenerated::Render()
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

shared_ptr<BeamPulse> BeamBeingGenerated::ReleaseBeam(time_point<steady_clock>& thisTime)
{
	switch (getDirection())
	{
	case Direction::Up:
		return shared_ptr<BeamPulse>{new BeamPulse(getXpos(), getYpos() - 0.5f*Grid::gridSize, getDirection(), GetColor(), thisTime)};
		break;
	case Direction::Down:
		return shared_ptr<BeamPulse>{new BeamPulse(getXpos(), getYpos() + 0.5f*Grid::gridSize, getDirection(), GetColor(), thisTime)};
		break;
	case Direction::Left:
		return shared_ptr<BeamPulse>{new BeamPulse(getXpos() - 0.5f*Grid::gridSize, getYpos(), getDirection(), GetColor(), thisTime)};
		break;
	case Direction::Right:
		return shared_ptr<BeamPulse>{new BeamPulse(getXpos() + 0.5f*Grid::gridSize, getYpos(), getDirection(), GetColor(), thisTime)};
		break;
	default:
		throw new exception("LaserSource direction not specified!");
	}
}

