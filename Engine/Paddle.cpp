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
	RectF livesRect = GetRect();
	livesRect.left = 10.0f;
	livesRect.top = Graphics::ScreenHeight - 16.0f;
	livesRect.right = livesRect.left + 40.0f;
	livesRect.bottom = livesRect.top + 8.0f;

	gfx.DrawRect(rect, wingColor);
	rect.left += wingWidth;
	rect.right -= wingWidth;
	gfx.DrawRect(rect, color);

	for (int i = 0; i < lives-1; i++)
	{
		gfx.DrawRect(livesRect, wingColor);
		livesRect.left += wingWidth/7.0f;
		livesRect.right -= wingWidth/7.0f;
		gfx.DrawRect(livesRect, color);

		livesRect.left = livesRect.right + 10.0f;
		livesRect.right = livesRect.left + 40.0f;
	}
}

bool Paddle::DoBallCollision(Ball & ball)
{
	if (!isCoolDown)
	{
		const RectF rect = GetRect();
		if (rect.IsOverlappingWith(ball.GetRect()) /*&& (ball.GetVel().y > 0) */)
		{
			const Vec2 bPos = ball.GetPos();

			if (std::signbit(ball.GetVel().x) && std::signbit((ball.GetPos() - pos).x)
				|| (bPos.x >= rect.left && bPos.x <= rect.right))
			{
				const float xDifference = bPos.x - pos.x;
				const Vec2 dir(xDifference * exitXFactor, -1.0f);
				ball.SetDirection(dir);
				//ball.ReboundY();
			}
			else
			{
				ball.ReboundX();
			}
			isCoolDown = true;
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

void Paddle::LoseLive()
{
	--lives;
}

int Paddle::GetLives() const
{
	return lives-1;
}

void Paddle::ResetCoolDown()
{
	isCoolDown = false;
}
