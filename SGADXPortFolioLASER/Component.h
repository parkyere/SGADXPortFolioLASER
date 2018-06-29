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
};
/*
class TwoColored 
{
protected:
	BeamColor Color1;
	BeamColor Color2;
	vector<Vertex>& Color1Shape;
	vector<Vertex>& Color2Shape;
	void SetColor1(DWORD color1ToSet);
	void SetColor2(DWORD color2ToSet);
public:
	TwoColored(BeamColor myColor1, BeamColor myColor2, vector<Vertex>& myColor1Shape, vector<Vertex>& myColor2Shape ) 
		: Color1{ myColor1 }, Color2{ myColor2 }, Color1Shape{ myColor1Shape }, Color2Shape{myColor2Shape} {}
	void SetColor1(BeamColor color1ToSet);
	void SetColor2(BeamColor color2ToSet);
};
*/

class Obstacle : public Component
{

};


class ColorChanger : public Component
{
protected:
	BeamColor ColorIn;
	BeamColor ColorOut;
	vector<Vertex>& InComponentShape{ ComponentShape };
	vector<Vertex> OutComponentShape;
	void SetColorIn (DWORD myColorIn);
	void SetColorOut(DWORD myColorOut);
public:
	void SetColorIn (BeamColor myColorIn );
	void SetColorOut(BeamColor myColorOut);
	void RightRotateDirection() override;
	ColorChanger();
	ColorChanger(float x, float y, Direction myDir, BeamColor myColorIn, BeamColor myColorOut) : ColorChanger() 
	{
		SetDir(myDir);
		SetPos(x, y);
		SetColorIn(myColorIn);
		SetColorOut(myColorOut);
	}
	void Render() override;
};

