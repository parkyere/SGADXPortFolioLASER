#pragma once

class ColorObject : public Component, public SingleColored
{
public:
	ColorObject();
	ColorObject(float x, float y, BeamColor myColor);
	void Render() override;
};