#pragma once
#include "RectF.h"
#include "Graphics.h"
#include "Colors.h"
#include "Ball.h"

class Brick
{
private:
	static constexpr float padding = 1.0f;
	RectF rect;
	Color c;
	bool destroyed;
public:
	Brick() = default;
	Brick(const RectF& rect_in, const Color& c_in);
	void Draw(Graphics& gfx) const;
	bool CheckBallCollision(const Ball& ball) const;
	void ExecuteBallCollision(Ball& ball);
	Vec2 GetCenter() const;
};