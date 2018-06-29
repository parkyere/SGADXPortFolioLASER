#pragma once
class BeamSplitter : public Gate, public SingleColored
{
public:
	BeamSplitter();
	BeamSplitter(float x, float y, Direction myDir, BeamColor myColor);
	void Render();
};