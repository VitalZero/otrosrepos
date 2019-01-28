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
{
	RectF( topLeft.x, topLeft.y, bottomRight.x, bottomRight.y );
}

RectF::RectF( const Vec2 & topLeft, float width_in, float height_in )
{
	RectF( topLeft, Vec2(topLeft.x + width_in, topLeft.y + height_in) );
}

bool RectF::IsOverlapping(const RectF & other)
{
	return (right >= other.left && left <= other.right &&
		top <= other.bottom && bottom >= other.top);
}

RectF RectF::FromCenter(Vec2 & center, float hWidth, float hHeight)
{
	return RectF( center.x - hWidth, center.y - hHeight, center.x + hWidth, center.y + hHeight );
}
