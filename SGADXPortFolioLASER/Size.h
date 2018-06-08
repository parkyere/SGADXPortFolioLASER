#pragma once

struct Size
{
	constexpr Size();
	constexpr Size(const Size& size) = default;
	constexpr Size(float width, float height);

	constexpr Size operator+(const Size& size) const;
	constexpr Size operator-(const Size& size) const;
	constexpr bool Equals(const Size& size) const;
	constexpr bool Empty() const;

	float width;
	float height;
};

