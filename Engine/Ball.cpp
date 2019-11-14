#include "Ball.h"
#include "Paddle.h"

Ball::Ball(const Vec2 & pos_in, const Vec2 & dir_in)
	:
	pos(pos_in)
{
	SetDirection(dir_in);
}

void Ball::Draw(Graphics & gfx) const
{
	SpriteCodex::DrawBall(pos, gfx);
}

void Ball::Update(float dt)
{
	pos += vel * dt;
}

Ball::Collisions Ball::DoWallCollision(RectF & wall)
{
	Collisions didItCollide = Collisions::Empty;
	RectF rect = GetRect();

	if (rect.left <= wall.left)
	{
		pos.x -= rect.left - wall.left;
		ReboundX();
		didItCollide = Collisions::Wall;
	}
	if (rect.right > wall.right)
	{
		pos.x -= rect.right - wall.right;
		ReboundX();
		didItCollide = Collisions::Wall;
	}
	if (rect.top <= wall.top)
	{
		pos.y -= rect.top - wall.top;
		vel.y = -vel.y;// ReboundY();
		didItCollide = Collisions::Wall;
	}
	if (rect.bottom > wall.bottom)
	{
		pos.y -= rect.bottom - wall.bottom;
		ReboundY();

		didItCollide = Collisions::Floor;
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

void Ball::ReboundY(Vec2 & padPos)
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

void Ball::SetDirection(const Vec2 & dir)
{
	vel = dir.GetNormalized() * speed;
}

Vec2 Ball::GetVel() const
{
	return vel;
}
