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
		gfx.DrawRect(rect.GetExpanded(-padding), c);
	}
}

bool Brick::DoBallCollision(Ball & ball)
{
	if (!destroyed)
	{
		if (rect.IsOverlappingWidth(ball.GetRect()))
		{
			Vec2 bPos = ball.GetPos();
			destroyed = true;
			if (bPos.x < rect.left || bPos.x > rect.right)
			{
				ball.ReboundX();
			}
			else
			{
				ball.ReboundY();
			}
			return true;
		}
	}
	return false;
}

