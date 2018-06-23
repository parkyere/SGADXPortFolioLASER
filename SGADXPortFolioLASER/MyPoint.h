#pragma once

struct MyPoint
{
	constexpr MyPoint() : x{ 0.f }, y{ 0.f }
	{
	}
	constexpr MyPoint(const MyPoint& point) : x{ point.x }, y{ point.y }
	{
	}
	constexpr MyPoint(const MyPoint&& point) : x{ point.x }, y{ point.y }
	{
	}
	constexpr MyPoint(const Size& size) : x{ size.width }, y{ size.height }
	{
	}

	constexpr MyPoint(float x, float y) : x{ x }, y{ y }
	{
	}

	constexpr MyPoint operator+(const MyPoint& point) const 
	{
		return MyPoint{ x + point.x,y + point.y };
	}
	constexpr MyPoint operator-(const MyPoint& point) const 
	{
		return MyPoint{ x - point.x, y - point.y };
	}
	constexpr MyPoint operator*(const float amount)   const 
	{
		return MyPoint{ x * amount, y * amount };
	}
	float magnitude() const;
	constexpr bool Equals(const MyPoint& point) const 
	{
		return (x == point.x) && (y == point.y);
	}
	static float Distance(const MyPoint& a, const MyPoint& b);

	float x;
	float y;
};

