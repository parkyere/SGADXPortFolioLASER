#pragma once

class Gate : public Component
{
public:
	void beamComing(Direction inDirection);
};


class Obstacle : public Gate
{
public:
	Obstacle();
	Obstacle(float x, float y);
	void Render() override;
};