#pragma once

class Gate : public Component
{
};


class Obstacle : public Gate
{
public:
	Obstacle();
	Obstacle(float x, float y);
	void Render() override;
};