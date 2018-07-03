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
public:
	Component() : ComponentDirection{ Direction::NoDirection } {}
	void SetDir(Direction myDir);
	virtual void RightRotateDirection();
	virtual void SetDirFromDown(Direction myDir);
	inline Direction getDirection()	{ return ComponentDirection;	}
	virtual void Render() = 0;
	virtual void SetPos(float x, float y);
	inline float getXpos() { return xPos; }
	inline float getYpos() { return yPos; }
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

class BeamPulse :public Component, public SingleColored
{
	float beamLength;
	float beamThickness{4.f};
	float beamSpeed;
	float initX;
	float initY;
public:
	time_point<steady_clock> firedTime;
	BeamPulse();
	BeamPulse(float x, float y, Direction myDir, BeamColor myColor, time_point<steady_clock>& inFiredTime);
	void Update(time_point<steady_clock>& thisTime);
	void Render() override;
};