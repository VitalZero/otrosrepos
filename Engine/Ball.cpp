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

bool Ball::DoWallCollision(RectF & wall)
{
	bool didItCollide = false;
	RectF rect = GetRect();

	if (rect.left <= wall.left)
	{
		pos.x -= rect.left - wall.left;
		ReboundX();
		didItCollide = true;
	}
	if (rect.right > wall.right)
	{
		pos.x -= rect.right - wall.right;
		ReboundX();
		didItCollide = true;
	}
	if (rect.top <= wall.top)
	{
		pos.y -= rect.top - wall.top;
		ReboundY();
		didItCollide = true;
	}
	if (rect.bottom > wall.bottom)
	{
		pos.y -= rect.bottom - wall.bottom;
		//ReboundY();
		died = true;
		didItCollide = false;
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

bool Ball::Died() const
{
	return died;
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
