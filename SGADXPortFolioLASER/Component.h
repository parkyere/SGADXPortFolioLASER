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
	virtual void Render(Direction myDir) = 0;

};



class Obstacle : public Component
{

};

class LaserSource : public Component 
{
	BeamColor SourceColor;
	bool isPulsed;
	Vertex ArrowShape[7];
	float xPos;
	float yPos;
public:
	LaserSource();
	void Render(Direction myDir) override;
	void SetColor(DWORD colorToSet);
	void SetColor(BeamColor colorToSet);
	void SetDirPos(float xPos, float yPos, Direction myDirection) noexcept;
};

class ColorChanger : public Component 
{

};
