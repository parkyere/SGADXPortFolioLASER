#pragma once

enum class BeamColor 
{
	Red,
	Green,
	Blue,
	Yellow,
	Cyan,
	Magenta,
	White
};

enum class Direction 
{
	NoDirection,
	Up,
	Right,
	Down,
	Left
};

class BeamPulse 
{
	BeamColor LaserColor;
	Direction BeamDirection;
};

class Component 
{
protected:
	Direction ComponentDirection;
public:
	Component() : ComponentDirection{ Direction::NoDirection } {}
	void RightRotateDirection();
	Direction getDirection();
	virtual void Render(float xPos, float yPos, Direction myDir) = 0;
};



class Obstacle : public Component
{

};

class LaserSource : public Component 
{
	BeamColor SourceColor;
	bool isPulsed;
public:
	LaserSource();
	void Render(float xPos, float yPos, Direction myDir) override;
};

class ColorChanger : public Component 
{

};
