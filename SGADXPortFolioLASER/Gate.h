#pragma once

class Gate : public Component
{
};

class ColorAdder : public Gate
{
};

class Mirror : public Gate
{
public:
	Mirror();
	Mirror(float x, float y, Direction myDir);
	void Render();
};

class BeamSplitter : public Gate, public SingleColored
{
public:
	BeamSplitter();
	BeamSplitter(float x, float y, Direction myDir, BeamColor myColor);
	void Render();
};