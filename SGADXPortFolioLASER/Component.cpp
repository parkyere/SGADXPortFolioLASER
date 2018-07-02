#include "stdafx.h"

void Component::RightRotateDirection()
{
	switch (ComponentDirection)
	{
	case Direction::Up:
		ComponentDirection = Direction::Right;
		break;
	case Direction::Right:
		ComponentDirection = Direction::Down;
		break;
	case Direction::Down:
		ComponentDirection = Direction::Left;
		break;
	case Direction::Left:
		ComponentDirection = Direction::Up;
		break;
	case Direction::NoDirection:
		break;
	}
	if (ComponentDirection != Direction::NoDirection) 
	{
		for (Vertex& v : ComponentShape)
		{
			v.position = { (v.position[1] * (-1.f)),v.position[0],0.f };
		}
	}
}


void Component::SetDirFromDown(Direction myDir)
{
	if (myDir == Direction::NoDirection)
		throw new exception("Direction must be specified!");
	//SetDir
	switch (myDir)
	{
	case Direction::Down:
		break;
	case Direction::Up:
	{
		for (Vertex& v : ComponentShape)
		{
			v.position[0] *= (-1.f);
			v.position[1] *= (-1.f);
			//v.position[3] = 1.f;
		}
	}
	break;
	case Direction::Right:
	{
		for (Vertex& v : ComponentShape)
		{
			v.position = { v.position[1],v.position[0] * (-1.f),0.f };
		}
	}
	break;
	case Direction::Left:
	{
		for (Vertex& v : ComponentShape)
		{
			v.position = { v.position[1] * -1.f,v.position[0],0.f };
		}
	}
	break;
	}
}

void Component::SetDir(Direction myDir)
{
	if (myDir == Direction::NoDirection)
	{
		if (ComponentDirection == Direction::NoDirection) 
		{
			return;
		}
		else 
		{
			throw new exception("Direction must be specified in this function!");
		}
	}
	else if (myDir == ComponentDirection)
		return;
	else 
	{
		while (ComponentDirection != myDir) 
		{
			RightRotateDirection();
		}
	}
}

void Component::SetPos(float x, float y) 
{
	xPos = x;
	yPos = y;
}

void Component::Magnify(float scale)
{
	for (Vertex& v : ComponentShape) 
	{
		v.position[0] *= scale;
		v.position[1] *= scale;
	}
}

void SingleColored::SetColor(DWORD colorToSet)
{
	for (Vertex& v : ShapeToColor)
	{
		v.color = colorToSet;
	}
}

void SingleColored::SetColor(BeamColor colorToSet)
{
	SingleColor = colorToSet;
	switch (colorToSet)
	{
	case BeamColor::Red:
		SetColor(COLOR_R);
		break;
	case BeamColor::Green:
		SetColor(COLOR_G);
		break;
	case BeamColor::Blue:
		SetColor(COLOR_B);
		break;
	case BeamColor::Magenta:
		SetColor(0xffff00ff);
		break;
	case BeamColor::Cyan:
		SetColor(0xff00ffff);
		break;
	case BeamColor::Yellow:
		SetColor(0xffffff00);
		break;
	case BeamColor::White:
		SetColor(COLOR_W);
		break;
	}
}

BeamPulse::BeamPulse()
	:SingleColored{ BeamColor::Red , ComponentShape }
{
	beamLength = 0.5f*Grid::gridSize;
	beamSpeed  = 0.5f*(float)(MAINGAME->callGameField().numStatePerSec)*Grid::gridSize;
	ComponentDirection = Direction::Down;
	firedTime = steady_clock::now();
	ComponentShape.emplace_back( beamThickness / 2.f, 0.f, 0.f, COLOR_R);
	ComponentShape.emplace_back(-beamThickness / 2.f, 0.f, 0.f, COLOR_R);
	ComponentShape.emplace_back(-beamThickness / 2.f, -beamLength, 0.f, COLOR_R);
	ComponentShape.emplace_back( beamThickness / 2.f, -beamLength, 0.f, COLOR_R);
}
BeamPulse::BeamPulse(float x, float y, Direction myDir, BeamColor myColor) : BeamPulse{}
{
	SetDir(myDir);
	SetPos(x, y);
	initX = x;
	initY = y;
	SetColor(myColor);
}

void BeamPulse::Update()
{
	switch (getDirection())
	{
	case Direction::Up: 
		SetPos(getXpos(),initY-beamSpeed*0.001f*(float)duration_cast<milliseconds>(steady_clock::now()-firedTime).count());
		break;
	case Direction::Down: 
		SetPos(getXpos(), initY + beamSpeed * 0.001f*(float)duration_cast<milliseconds>(steady_clock::now() - firedTime).count());
		break;
	case Direction::Right: 
		SetPos(initX + beamSpeed * 0.001f*(float)duration_cast<milliseconds>(steady_clock::now() - firedTime).count(), getYpos());
		break;
	case Direction::Left: 
		SetPos(initX - beamSpeed * 0.001f*(float)duration_cast<milliseconds>(steady_clock::now() - firedTime).count(), getYpos());
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
