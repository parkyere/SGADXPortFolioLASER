#pragma once

struct MyPoint
{
	constexpr MyPoint() = default;
	constexpr MyPoint(const MyPoint& point);
	constexpr MyPoint(const MyPoint&& point);
	constexpr MyPoint(const Size& size);
	constexpr MyPoint(float x, float y);

	constexpr MyPoint operator+(const MyPoint& point) const;
	constexpr MyPoint operator-(const MyPoint& point) const;
	constexpr MyPoint operator*(const float amount)   const;
	float magnitude() const;
	constexpr bool Equals(const MyPoint& point) const;
	static float Distance(const MyPoint& a, const MyPoint& b);

	float x;
	float y;
};

