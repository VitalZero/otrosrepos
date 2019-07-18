#include "Brick.h"
#include <cassert>

Brick::Brick(const RectF& rect_in, const Color& c_in, unsigned char type_in)
	:
	destroyed(false),
	c(c_in),
	rect(rect_in),
	type(type_in),
	hits(type_in)
{
}

void Brick::Draw(Graphics & gfx) const
{
	Color a(170, 170, 170);

	if (!destroyed)
	{
		RectF lines = rect.GetExpanded(-padding);
		gfx.DrawRect(rect.GetExpanded(-padding), (type == 1) ? a:c);

		gfx.DrawRect((int)lines.left, (int)lines.top, (int)lines.right, (int)(lines.top + 1.0f), Color(250, 250, 250) );

		gfx.DrawRect((int)(lines.right - 1.0f), (int)lines.top, (int)lines.right, (int)lines.bottom, Color(250, 250, 250) );

		gfx.DrawRect((int)lines.left, (int)(lines.bottom - 1.0f), (int)lines.right, (int)lines.bottom, Color(100, 100, 100) );

		gfx.DrawRect((int)lines.left, (int)lines.top, (int)(lines.left + 1.0f), (int)lines.bottom, Color(100,100,100) );
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

	if (std::signbit(ball.GetVel().x) && std::signbit( (bPos - GetCenter()).x ))
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
	
	if (hits > 0)
	{
		--hits;
		destroyed = false;
	}
	else if (hits == 0)
	{
		destroyed = true;
	}
}

Vec2 Brick::GetCenter() const
{
	return rect.GetCenter();
}

