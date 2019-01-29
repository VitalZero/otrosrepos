#include "Ball.h"

Ball::Ball(Vec2 & pos_in, Vec2 & vel_in)
	:
	pos(pos_in),
	vel(vel_in)
{
}

void Ball::Draw(Graphics & gfx) const
{
	SpriteCodex::DrawBall(pos, gfx);
}

void Ball::Update(float dt)
{
	pos += vel * dt;
}

bool Ball::WallCollide(RectF & wall)
{
	RectF rect = GetRect();

	if (rect.left <= wall.left)
	{
		pos.x -= rect.left - wall.left;
		ReboundX();
		return true;
	}
	else if (rect.right > wall.right)
	{
		pos.x -= rect.right - wall.right;
		ReboundX();
		return true;

	}
	else if (rect.top <= wall.top)
	{
		pos.y -= rect.top - wall.top;
		ReboundY();
		return true;

	}
	else if (rect.bottom > wall.bottom)
	{
		pos.y -= rect.bottom - wall.bottom;
		ReboundY();
		return true;

	}

	return false;
}

void Ball::ReboundX()
{
	vel.x = -vel.x;
}

void Ball::ReboundY()
{
	vel.y = -vel.y;
}

RectF Ball::GetRect() const
{
	return RectF::FromCenter(pos, size, size);
}
