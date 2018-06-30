#pragma once
class ColorAdder : public Gate
{
public:
	ColorAdder();
	ColorAdder(float x, float y, Direction myDir);
	void Render() override;
};