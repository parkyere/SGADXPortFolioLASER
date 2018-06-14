#pragma once

struct Rect
{
	constexpr Rect() = default;
	constexpr Rect(const Rect& rect) = default;
	constexpr Rect(float x, float y, float width, float height);
	constexpr Rect(const MyPoint& location, const Size& size);
	constexpr Rect(const RECT& rect);

	void GetHalfLocation(MyPoint* location) const;
	void GetHalfSize(Size* size) const;

	constexpr float GetLeft() const;
	constexpr float GetTop() const;
	constexpr float GetRight() const;
	constexpr float GetBottom() const;

	constexpr bool IsEmptyArea() const;
	constexpr bool Equals(const Rect& rect) const;

	constexpr static bool Intersect(const Rect& a, const Rect& b);
	static bool Intersect(const Rect & a, const Rect & b, Rect * c);

	enum Direction { None = 0, Left, Right, Top, Bottom };
	static Direction IntersectDir(const Rect& a, const Rect& b);

	MyPoint location;
	Size size;
};