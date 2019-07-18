#include "Ball.h"
#include "Paddle.h"

Ball::Ball(Vec2 & pos_in, Vec2 & vel_in, Paddle& pad)
	:
	pos(pos_in),
	vel(vel_in),
	pad(pad)
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

int Ball::DoWallCollision(RectF & wall)
{
	int didItCollide = 0;
	RectF rect = GetRect();

	if (rect.left <= wall.left)
	{
		pos.x -= rect.left - wall.left;
		ReboundX();
		didItCollide = 1;
	}
	if (rect.right > wall.right)
	{
		pos.x -= rect.right - wall.right;
		ReboundX();
		didItCollide = 1;
	}
	if (rect.top <= wall.top)
	{
		pos.y -= rect.top - wall.top;
		vel.y = -vel.y;// ReboundY();
		didItCollide = 1;
	}
	if (rect.bottom > wall.bottom)
	{
		pos.y -= rect.bottom - wall.bottom;
		ReboundY();

		didItCollide = 2;
	}

	return didItCollide;
}

void Ball::ReboundX()
{
	vel.x = -vel.x;
}

void Ball::ReboundY()
{
	vel.y = -vel.y;
}

void Ball::ReboundY(Vec2& padPos)
{
	const float uno = pos.x;
	const float dos = padPos.x;
	const float res = (padPos.x / pos.x)/10;

	vel.y = -vel.y;
}

RectF Ball::GetRect() const
{
	return RectF::FromCenter(pos, radius, radius);
}

Vec2 Ball::GetPos() const
{
	return pos;
}

Vec2 Ball::GetVel() const
{
	return vel;
}
