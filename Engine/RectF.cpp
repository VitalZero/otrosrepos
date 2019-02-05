#include "RectF.h"

RectF::RectF( float left_in, float top_in, float right_in, float bottom_in )
	:
	left(left_in),
	top(top_in),
	right(right_in),
	bottom(bottom_in)
{
}

RectF::RectF( const Vec2 & topLeft, const Vec2 & bottomRight )
	:
	RectF(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y)
{
}

RectF::RectF( const Vec2 & topLeft, float width_in, float height_in )
	:
	RectF(topLeft, Vec2(topLeft.x + width_in, topLeft.y + height_in))
{
}

bool RectF::IsOverlappingWith(const RectF & other) const
{
	return (right >= other.left && left <= other.right &&
		top <= other.bottom && bottom >= other.top);
}

RectF RectF::FromCenter(const Vec2 & center, float halfWidth, float halfHeight)
{
	return RectF( center.x - halfWidth, center.y - halfHeight, center.x + halfWidth, center.y + halfHeight );
}

RectF RectF::GetExpanded(float offset) const
{
	return RectF(left - offset, top - offset, right + offset, bottom + offset);
}

Vec2 RectF::GetCenter() const
{
	return Vec2((left + right) / 2, (top + bottom) / 2);
}
