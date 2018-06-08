#pragma once

struct MyPoint
{
	constexpr MyPoint();
	constexpr MyPoint(const MyPoint& point);
	constexpr MyPoint(const MyPoint&& point);
	constexpr MyPoint(const Size& size);
	constexpr MyPoint(float x, float y);
	~MyPoint();

	MyPoint operator+(const MyPoint& point) const;
	MyPoint operator-(const MyPoint& point) const;
	MyPoint operator*(const float amount)   const;
	float magnitude();
	constexpr bool Equals(const MyPoint& point) const;
	static float Distance(const MyPoint& a, const MyPoint& b);

	float x;
	float y;
};

