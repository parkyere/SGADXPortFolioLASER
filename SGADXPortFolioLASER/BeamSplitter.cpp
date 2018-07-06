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

void BeamSplitter::beamComing(shared_ptr<BeamPulse> inBeam)
{
	if (GetColor() == inBeam->GetColor()) 
	{
		auto thisTime = steady_clock::now();
		Direction inBeamDirection = inBeam->getDirection();
		//Beam Splitting
		switch (getDirection())
		{
		case Direction::Up:
		{
			switch (inBeamDirection)
			{
			case Direction::Left:
			case Direction::Up:
			{
				MAINGAME->callGameField().CallGenerator(getXpos(), getYpos(), Direction::Up, GetColor(), thisTime);
				MAINGAME->callGameField().CallGenerator(getXpos(), getYpos(), Direction::Left, GetColor(), thisTime);
				return;
			}
			break;
			default:
				break;
			}
		}
		break;
		case Direction::Right:
		{
			switch (inBeamDirection)
			{
			case Direction::Right:
			case Direction::Up:
			{
				MAINGAME->callGameField().CallGenerator(getXpos(), getYpos(), Direction::Up, GetColor(), thisTime);
				MAINGAME->callGameField().CallGenerator(getXpos(), getYpos(), Direction::Right, GetColor(), thisTime);
				return;
			}
			break;
			default:
				break;
			}
		}
		break;
		case Direction::Down:
		{
			switch (inBeamDirection)
			{
			case Direction::Right:
			case Direction::Down:
			{
				MAINGAME->callGameField().CallGenerator(getXpos(), getYpos(), Direction::Right, GetColor(), thisTime);
				MAINGAME->callGameField().CallGenerator(getXpos(), getYpos(), Direction::Down, GetColor(), thisTime);
				return;
			}
			break;
			default:
				break;
			}
		}
		break;
		case Direction::Left:
		{
			switch (inBeamDirection)
			{
			case Direction::Left:
			case Direction::Down:
			{
				MAINGAME->callGameField().CallGenerator(getXpos(), getYpos(), Direction::Left, GetColor(), thisTime);
				MAINGAME->callGameField().CallGenerator(getXpos(), getYpos(), Direction::Down, GetColor(), thisTime);
				return;
			}
			break;
			default:
				break;
			}
		}
		break;
		default:
			break;
		}
	}
	else 
	{
		return;
	}
}
