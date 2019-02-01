#include "Brick.h"

Brick::Brick(const RectF& rect_in, const Color& c_in)
	:
	destroyed(false),
	c(c_in),
	rect(rect_in)
{
}

void Brick::Draw(Graphics & gfx) const
{
	if (!destroyed)
	{
		gfx.DrawRect(rect, c);
	}
}

bool Brick::DoBallCollision(Ball & ball)
{
	if (!destroyed)
	{
		if (rect.IsOverlappingWidth(ball.GetRect()))
		{
			destroyed = true;
			ball.ReboundY();
			return true;
		}
	}
	return false;
}

