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

}

Direction Component::getDirection()
{
	return ComponentDirection;
}

LaserSource::LaserSource() 
	:SourceColor{BeamColor::Red},
	isPulsed{ true }
{
	ComponentDirection = Direction::Up;
	ArrowShape[0] = Vertex{-20.f,0.f,COLOR_R};
	ArrowShape[1]= Vertex{ 0.f,20.f,COLOR_R };
	ArrowShape[2]= Vertex{ 20.f,0.f,COLOR_R };
	ArrowShape[3]= Vertex{ 10.f,0.f,COLOR_R };
	ArrowShape[4]= Vertex{ 10.f,-20.f,COLOR_R };
	ArrowShape[5]= Vertex{ -10.f,-20.f,COLOR_R };
	ArrowShape[6]= Vertex{ -10.f,0.f,COLOR_R };
}

void LaserSource::Render(Direction myDir)
{
	DEVICE->SetFVF(ArrowShape[0].fvf);
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 1, ArrowShape, sizeof(Vertex));
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, ArrowShape+3, sizeof(Vertex));
}

void LaserSource::SetColor(BeamColor colorToSet) 
{
	SourceColor = colorToSet;
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
		SetColor(0xffff00ff);
		break;
	case BeamColor::Yellow:
		SetColor(0xffff00ff);
		break;
	case BeamColor::White:
		SetColor(COLOR_W);
		break;
	}
}

void LaserSource::SetColor(DWORD colorToSet)
{
	for (Vertex& v: ArrowShape) 
	{
		v.color = colorToSet;
	}
}

void LaserSource::SetDirPos(float xPos, float yPos, Direction myDir) noexcept
{
	this->xPos = xPos;
	this->yPos = yPos;

	if (myDir == Direction::NoDirection)
		throw new exception("Direction must be specified!");
	//SetDir
	switch (myDir) 
	{
	case Direction::Up:
		break;
	case Direction::Down:
	{
		for (Vertex& v : ArrowShape) 
		{
			v.position *= -1.f;
			v.position[3] = 1.f;
		}
	}
		break;
	case Direction::Right:
	{
		for (Vertex& v : ArrowShape)
		{
			v.position = {v.position[1],v.position[0]*-1.f,0,1.f};
		}
	}
	break;
	case Direction::Left:
	{
		for (Vertex& v : ArrowShape)
		{
			v.position = { v.position[1]* - 1.f,v.position[0],0,1.f };
		}
	}
	break;
	}
	//SetPos
	for (Vertex& v : ArrowShape) 
	{
		v.position = { v.position[0] + xPos, v.position[1] + yPos,0.f,1.f };
	}
}
