#include "stdafx.h"

void ColorChanger::SetColorIn(DWORD myColorIn)
{
	for (Vertex& v : InComponentShape)
	{
		v.color = myColorIn;
	}
}

void ColorChanger::SetColorOut(DWORD myColorOut)
{
	for (Vertex& v : OutComponentShape)
	{
		v.color = myColorOut;
	}
}

void ColorChanger::SetColorIn(BeamColor myColorIn)
{
	ColorIn = myColorIn;
	switch (ColorIn)
	{
	case BeamColor::Red:
		SetColorIn(COLOR_R);
		break;
	case BeamColor::Green:
		SetColorIn(COLOR_G);
		break;
	case BeamColor::Blue:
		SetColorIn(COLOR_B);
		break;
	case BeamColor::Magenta:
		SetColorIn(0xffff00ff);
		break;
	case BeamColor::Cyan:
		SetColorIn(0xff00ffff);
		break;
	case BeamColor::Yellow:
		SetColorIn(0xffffff00);
		break;
	case BeamColor::White:
		SetColorIn(COLOR_W);
		break;
	}
}
void ColorChanger::SetColorOut(BeamColor myColorOut)
{
	ColorOut = myColorOut;
	switch (ColorOut)
	{
	case BeamColor::Red:
		SetColorOut(COLOR_R);
		break;
	case BeamColor::Green:
		SetColorOut(COLOR_G);
		break;
	case BeamColor::Blue:
		SetColorOut(COLOR_B);
		break;
	case BeamColor::Magenta:
		SetColorOut(0xffff00ff);
		break;
	case BeamColor::Cyan:
		SetColorOut(0xff00ffff);
		break;
	case BeamColor::Yellow:
		SetColorOut(0xffffff00);
		break;
	case BeamColor::White:
		SetColorOut(COLOR_W);
		break;
	}

}

void ColorChanger::RightRotateDirection()
{
	switch (ComponentDirection)
	{
	case Direction::Up:
		ComponentDirection = Direction::Right;
		break;
	case Direction::Right:
		ComponentDirection = Direction::Down;
		break;
	case Direction::Down:
		ComponentDirection = Direction::Left;
		break;
	case Direction::Left:
		ComponentDirection = Direction::Up;
		break;
	case Direction::NoDirection:
		break;
	}
	if (ComponentDirection != Direction::NoDirection)
	{
		for (Vertex& v : InComponentShape)
		{
			v.position = { (v.position[1] * (-1.f)),v.position[0],0.f };
		}
		for (Vertex& v : OutComponentShape)
		{
			v.position = { (v.position[1] * (-1.f)),v.position[0],0.f };
		}
	}

}

void ColorChanger::Magnify(float scale)
{
	for (Vertex& v : InComponentShape)
	{
		v.position[0] *= scale;
		v.position[1] *= scale;
	}
	for (Vertex& v : OutComponentShape)
	{
		v.position[0] *= scale;
		v.position[1] *= scale;
	}
}

ColorChanger::ColorChanger() : ColorIn{ BeamColor::Red }, ColorOut{ BeamColor::Blue }
{
	ComponentDirection = Direction::Down;
	OutComponentShape.emplace_back(0.f, 2.f, COLOR_B);
	OutComponentShape.emplace_back(10.f, -3.f, COLOR_B);
	OutComponentShape.emplace_back(10.f, 5.f, COLOR_B);
	OutComponentShape.emplace_back(-10.f, 5.f, COLOR_B);
	OutComponentShape.emplace_back(-10.f, -3.f, COLOR_B);

	OutComponentShape.emplace_back(20.f, 5.f, COLOR_B);
	OutComponentShape.emplace_back(0.f, 20.f, COLOR_B);
	OutComponentShape.emplace_back(-20.f, 5.f, COLOR_B);

	InComponentShape.emplace_back(-10.f, -20.f, COLOR_R);
	InComponentShape.emplace_back(10.f, -20.f, COLOR_R);
	InComponentShape.emplace_back(10.f, -7.f, COLOR_R);
	InComponentShape.emplace_back(0.f, -2.f, COLOR_R);
	InComponentShape.emplace_back(-10.f, -7.f, COLOR_R);

}

void ColorChanger::Render()
{
	vector<Vertex> inTempVertex;
	vector<Vertex> outTempVertex;
	int OutShapeIndex = OutComponentShape.size();
	int InShapeIndex = InComponentShape.size();
	for (int i = 0; i< OutShapeIndex; i++)
	{
		outTempVertex.push_back(OutComponentShape[i]);
		outTempVertex[i].position = { outTempVertex[i].position[0] + xPos, outTempVertex[i].position[1] + yPos, 0.f };
	}

	for (int i = 0; i< InShapeIndex; i++)
	{
		inTempVertex.push_back(InComponentShape[i]);
		inTempVertex[i].position = { inTempVertex[i].position[0] + xPos, inTempVertex[i].position[1] + yPos, 0.f };
	}

	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 3, &outTempVertex[0], sizeof(Vertex));
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 1, &outTempVertex[5], sizeof(Vertex));
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 3, &inTempVertex[0], sizeof(Vertex));
}

void ColorChanger::beamComing(shared_ptr<BeamPulse> inBeam)
{
	auto thisTime = steady_clock::now();
	if (ComponentDirection == inBeam->getDirection()) 
	{
		if (GetColorIn() == inBeam->GetColor())
		{
			MAINGAME->callGameField().CallGenerator(getXpos(), getYpos(), ComponentDirection, GetColorOut(), thisTime);
		}
	}
}
