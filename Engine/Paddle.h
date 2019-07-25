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
	static constexpr Color wingColor = Colors::Red;
	static constexpr Color color = Colors::White;
	static constexpr float speed = 300.0f;
	// comportamiento del rebote
	static constexpr float maximumExitRatio = 2.6f;
	static constexpr float fixedZoneWidthRatio = .2f;
	float halfWidth;
	float halfHeight;
	float exitXFactor;
	float fixedZoneHalfWidth;
	float fixedZoneExitX;
	Vec2 pos;
	bool isCoolDown = false;
	int lives = 3;
	
};