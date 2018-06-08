#include "stdafx.h"

constexpr MyPoint::MyPoint() : x{ 0.f }, y{0.f}
{
}

constexpr MyPoint::MyPoint(const MyPoint & point) : x{ point.x }, y{ point.y }
{
}

constexpr MyPoint::MyPoint(const MyPoint && point) : x{ point.x }, y{point.y}
{
}

constexpr MyPoint::MyPoint(const Size & size) : x{ size.width }, y{size.height}
{
}

constexpr MyPoint::MyPoint(float x, float y): x{x} ,y{y}
{
}

MyPoint::~MyPoint()
{
}

MyPoint MyPoint::operator+(const MyPoint& point) const
{
	return MyPoint{( x + point.x), (y + point.y) };
}

MyPoint MyPoint::operator-(const MyPoint& point) const
{
	return MyPoint{ x - point.x, y - point.y };
}

MyPoint MyPoint::operator*(const float amount) const
{
	return MyPoint{ x * amount, y * amount };
}

float MyPoint::magnitude()
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