#pragma once

class ColorChanger : public Gate
{
protected:
	BeamColor ColorIn;
	BeamColor ColorOut;
	vector<Vertex> InComponentShape;
	vector<Vertex> OutComponentShape;
	void SetColorIn(DWORD myColorIn);
	void SetColorOut(DWORD myColorOut);
public:
	void SetColorIn(BeamColor myColorIn);
	void SetColorOut(BeamColor myColorOut);
	void RightRotateDirection() override;
	void Magnify(float scale) override;
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
