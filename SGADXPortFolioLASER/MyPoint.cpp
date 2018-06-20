#include "stdafx.h"

constexpr MyPoint MyPoint::operator+(const MyPoint& point) const
{
	return MyPoint{ x + point.x,y + point.y };
}

constexpr MyPoint MyPoint::operator-(const MyPoint& point) const
{
	return MyPoint{ x - point.x, y - point.y };
}

constexpr MyPoint MyPoint::operator*(const float amount) const
{
	return MyPoint{ x * amount, y * amount };
}

float MyPoint::magnitude() const
{
	return sqrtf(x*x + y*y);
}

constexpr bool MyPoint::Equals(const MyPoint & point) const
{
	return (x == point.x) && (y == point.y);
}

float MyPoint::Distance(const MyPoint & a, const MyPoint & b)
{
	return (a-b).magnitude();
}