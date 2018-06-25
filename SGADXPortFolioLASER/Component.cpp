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
}

void LaserSource::Render(float xPos, float yPos, Direction myDir)
{
}
