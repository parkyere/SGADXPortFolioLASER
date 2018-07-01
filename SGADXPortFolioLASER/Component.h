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
	vector<Vertex> ComponentShape;
	float xPos;
	float yPos;
public:
	Component() : ComponentDirection{ Direction::NoDirection } {}
	void SetDir(Direction myDir);
	virtual void RightRotateDirection();
	virtual void SetDirFromDown(Direction myDir);
	Direction getDirection();

	virtual void Render() = 0;
	virtual void SetPos(float x, float y);
	void Magnify(float scale);
};

class SingleColored 
{
protected:
	BeamColor SingleColor;
	vector<Vertex>& ShapeToColor;
	void SetColor(DWORD colorToSet);
public:
	SingleColored(BeamColor myColor, vector<Vertex>& myShape) : SingleColor{myColor}, ShapeToColor{ myShape } {}
	void SetColor(BeamColor colorToSet);
	inline BeamColor GetColor() { return SingleColor; }
};

