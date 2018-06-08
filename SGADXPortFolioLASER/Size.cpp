#include "stdafx.h"

constexpr Size::Size() 
	: width{ 0.f },
	height{0.f}
{
}

constexpr Size::Size(float width, float height): width{width}, height{height}
{
}


constexpr Size Size::operator+(const Size & size) const
{
	return Size{ width + size.width, height + size.height };
}

constexpr Size Size::operator-(const Size & size) const
{
	return Size{width - size.width, height - size.height};
}

constexpr bool Size::Equals(const Size & size) const
{
	return (width == size.width) && (height == size.height);
}

constexpr bool Size::Empty() const
{
	return (width == 0.0f) && (height == 0.0f);
}
