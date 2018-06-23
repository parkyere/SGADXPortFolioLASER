#include "stdafx.h"

float MyPoint::magnitude() const
{
	return sqrtf(x*x + y*y);
}

float MyPoint::Distance(const MyPoint & a, const MyPoint & b)
{
	return (a-b).magnitude();
}