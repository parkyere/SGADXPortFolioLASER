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

class Component 
{
protected:
	Direction ComponentDirection;
	vector<Vertex> ComponentShape;
	float xPos;
	float yPos;
	string componentName;
public:
	Component() : ComponentDirection{ Direction::NoDirection } {}
	string getName() { return componentName; }
	void SetDir(Direction myDir);
	virtual void RightRotateDirection();
	virtual void SetDirFromDown(Direction myDir);
	inline Direction getDirection()	{ return ComponentDirection;}
	virtual void Render() = 0;
	void SetPos(float x, float y);
	inline float getXpos() const { return xPos; }
	inline float getYpos() const { return yPos; }
	virtual void Magnify(float scale);
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