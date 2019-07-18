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
		vel.y = -vel.y;// ReboundY();
		didItCollide = true;
	}
	if (rect.bottom > wall.bottom)
	{
		pos.y -= rect.bottom - wall.bottom;
		ReboundY();
		/*if (pad.GetLives() > 0)
			pad.LoseLive();
		else
			died = true;*/

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

void Ball::ReboundY(Vec2& padPos)
{
	const float uno = pos.x;
	const float dos = padPos.x;
	const float res = (padPos.x / pos.x)/10;

	//vel.x = vel.x + (vel.x * -res);
	/*Vec2 tmpPos = padPos - pos;
	tmpPos.x = atan2(tmpPos.y, tmpPos.x);
	tmpPos.x = cos(tmpPos.x);
	vel.x = 300.0f * tmpPos.x;*/
	//vel.x = vel.x * cos(tmpPos.x);
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
