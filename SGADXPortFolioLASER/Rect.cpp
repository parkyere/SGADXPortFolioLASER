#include "stdafx.h"

constexpr Rect::Rect(float x, float y, float width, float height) 
	: location{ x,y },
	size{ width,height }
{
}

constexpr Rect::Rect(const MyPoint & location, const Size & size)
	: location{location},
	size{size}
{
}

constexpr Rect::Rect(const RECT & rect)
	: location{(float)rect.left, (float)rect.top},
	size{(float)(rect.right-rect.left), (float)(rect.bottom-rect.top)}
{
}

void Rect::GetHalfLocation(MyPoint * location) const
{
	location->x = this->location.x + (size.width * 0.5f);
	location->y = this->location.y + (size.height * 0.5f);
}

void Rect::GetHalfSize(Size * size) const
{
	size->width = this->size.width * 0.5f;
	size->height = this->size.height * 0.5f;
}

constexpr float Rect::GetLeft() const
{
	return location.x;
}

constexpr float Rect::GetTop() const
{
	return location.y;
}

constexpr float Rect::GetRight() const
{
	return location.x + size.width;
}

constexpr float Rect::GetBottom() const
{
	return location.y + size.height;
}

constexpr bool Rect::IsEmptyArea() const
{
	return (size.width < 1.0f) || (size.height < 1.0f);
}

constexpr bool Rect::Equals(const Rect & rect) const
{
	return location.Equals(rect.location) && size.Equals(rect.size);
}

constexpr bool Rect::Intersect(const Rect & a, const Rect & b)
{
	return (a.GetLeft() < b.GetRight()) &&
		(a.GetTop() < b.GetBottom()) &&
		(a.GetRight() > b.GetLeft()) &&
		(a.GetBottom() > b.GetTop());
}

bool Rect::Intersect(const Rect & a, const Rect & b, Rect * c)
{
	float left = max(a.GetLeft(), b.GetLeft());
	float top = max(a.GetTop(), b.GetTop());
	float right = min(a.GetRight(), b.GetRight());
	float bottom = min(a.GetBottom(), b.GetBottom());

	if (c != NULL)
	{
		c->location.x = left;
		c->location.y = top;
		c->size.width = right - left;
		c->size.height = bottom - top;
	}
	return c->IsEmptyArea() == false;
}

Rect::Direction Rect::IntersectDir(const Rect & a, const Rect & b)
{
	MyPoint halfLocation1, halfLocation2;
	a.GetHalfLocation(&halfLocation1);
	b.GetHalfLocation(&halfLocation2);

	Size halfSize1, halfSize2;
	a.GetHalfSize(&halfSize1);
	b.GetHalfSize(&halfSize2);

	MyPoint halfLocation = halfLocation1 - halfLocation2;
	Size halfSize = halfSize1 + halfSize2;

	Direction direction = None;
	if (fabs(halfLocation.x) < (double)halfSize.width && fabs(halfLocation.y) < (double)halfSize.height)
	{
		Size overlap;
		overlap.width = halfSize.width - (float)fabs(halfLocation.x);
		overlap.height = halfSize.height - (float)fabs(halfLocation.y);

		if (overlap.width >= overlap.height)
			return halfLocation.y > 0 ? Bottom : Top;
		else
			return halfLocation.x > 0 ? Right : Left;
	}

	return Direction::None;
}
