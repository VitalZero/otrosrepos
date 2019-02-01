#include "Paddle.h"

Paddle::Paddle(const Vec2 & pos_in, float hWidth, float hHeight)
	:
	pos(pos_in),
	halfWidth(hWidth),
	halfHeight(hHeight)
{
}

void Paddle::Draw(Graphics & gfx) const
{
	RectF rect = GetRect();
	
	gfx.DrawRect(rect, wingColor);
	rect.left += wingWidth;
	rect.right -= wingWidth;
	gfx.DrawRect(rect, color);
}

bool Paddle::DoBallCollision(Ball & ball)
{
	if ( GetRect().IsOverlappingWidth(ball.GetRect() ) )
	{
		if (ball.GetVel().y > 0.0f)
		{
			ball.ReboundY();
			return true;
		}
	}
	return false;
}

void Paddle::DoWallCollision(const RectF & wall)
{
	const RectF rect = GetRect();

	if (rect.left < wall.left)
	{
		pos.x += wall.left - rect.left;
	}
	if (rect.right > wall.right)
	{
		pos.x -= rect.right - wall.right;
	}
}

void Paddle::Update(Keyboard & kbd, float dt)
{
	if (kbd.KeyIsPressed(VK_LEFT))
	{
		pos.x -= speed * dt;
	}
	if (kbd.KeyIsPressed(VK_RIGHT))
	{
		pos.x += speed * dt;
	}
}

RectF Paddle::GetRect() const
{
	return RectF::FromCenter(pos, halfWidth, halfHeight);
}
