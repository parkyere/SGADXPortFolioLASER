#pragma once

class Gate : public Component
{
public:
	virtual void beamComing(shared_ptr<BeamPulse> inBeam) = 0;
};


class Obstacle : public Gate
{
public:
	Obstacle();
	Obstacle(float x, float y);
	void Render() override;
	void beamComing(shared_ptr<BeamPulse> inBeam) override;
};