#include "Brick.h"
#include <cassert>

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

bool Brick::CheckBallCollision(const Ball& ball) const
{
	return !destroyed && rect.IsOverlappingWith( ball.GetRect() );
}

void Brick::ExecuteBallCollision(Ball & ball)
{
	assert(CheckBallCollision(ball));
	Vec2 bPos = ball.GetPos();
	if (std::signbit(ball.GetVel().x) && std::signbit( (ball.GetPos() - GetCenter()).x ))
	{
		ball.ReboundY();
	}
	else if (bPos.x < rect.left || bPos.x > rect.right)
	{
		ball.ReboundX();
	}
	else
	{
		ball.ReboundY();
	}
	destroyed = true;
}

Vec2 Brick::GetCenter() const
{
	return rect.GetCenter();
}

