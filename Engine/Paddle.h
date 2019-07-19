#pragma once
#include "RectF.h"
#include "Colors.h"
#include "Graphics.h"
#include "Ball.h"
#include "Keyboard.h"

class Paddle
{
public:
	Paddle(const Vec2& pos_in, float hWidth, float hHeight);
	void Draw(Graphics& gfx) const;
	bool DoBallCollision(Ball& ball);
	void DoWallCollision(const RectF& wall);
	void Update(Keyboard& kbd, float dt);
	RectF GetRect() const;
	void LoseLive();
	int GetLives() const;
	void ResetCoolDown();
protected:
	static constexpr float wingWidth = 18.0f;
	Color wingColor = Colors::Red;
	Color color = Colors::White;
	float halfWidth, halfHeight;
	const float exitXFactor = 0.045f;
	Vec2 pos;
	bool isCoolDown = false;
	int lives = 3;
	float speed = 300.0f;
};