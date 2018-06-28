#pragma once

class LaserSource : public Component, public SingleColored
{
protected:
	bool isPulsed;
public:
	LaserSource();
	LaserSource(float x, float y, Direction myDir, BeamColor myColor);
	void Render() override;
};