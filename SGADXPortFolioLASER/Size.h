#pragma once

struct Size
{
	constexpr Size() : width{ 0.f }, height{ 0.f } {}
	constexpr Size(const Size& size) = default;
	constexpr Size(float width, float height) : width{ width }, height{ height } {}

	constexpr Size operator+(const Size& size) const 
	{
		return Size{ width + size.width, height + size.height };
	}
	constexpr Size operator-(const Size& size) const 
	{
		return Size{ width - size.width, height - size.height };
	}
	constexpr bool Equals(const Size& size) const 
	{
		return (width == size.width) && (height == size.height);
	}
	constexpr bool Empty() const 
	{
		return (width == 0.0f) && (height == 0.0f);
	}

	float width;
	float height;
};

