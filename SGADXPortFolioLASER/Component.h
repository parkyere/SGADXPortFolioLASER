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
	virtual void RightRotateDirection();
	Direction getDirection();
	virtual void Render() = 0;

};



class Obstacle : public Component
{

};

class LaserSource : public Component 
{
private:
	BeamColor SourceColor;
	bool isPulsed;
	Vertex ArrowShape[7];
	float xPos;
	float yPos;
	void SetColor(DWORD colorToSet);
public:
	LaserSource();
	LaserSource(float x, float y, Direction myDir, BeamColor myColor);
	void Render() override;

	void SetColor(BeamColor colorToSet);
	//void SetPosDir(float xPos, float yPos, Direction myDirection);
	void RightRotateDirection() override;
	void SetDirFromDown(Direction myDir);
	void SetDir(Direction myDir);
	void SetPos(float x, float y);
};

class ColorChanger : public Component 
{

};
