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

	constexpr MyPoint operator+(const MyPoint& point) const;
	constexpr MyPoint operator-(const MyPoint& point) const;
	constexpr MyPoint operator*(const float amount)   const;
	float magnitude() const;
	constexpr bool Equals(const MyPoint& point) const;
	static float Distance(const MyPoint& a, const MyPoint& b);

	float x;
	float y;
};

