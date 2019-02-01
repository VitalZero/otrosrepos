#pragma once
#include "RectF.h"
#include "Graphics.h"
#include "Colors.h"
#include "Ball.h"

class Brick
{
public:
	Brick() = default;
	Brick(const RectF& rect_in, const Color& c_in);
	void Draw(Graphics& gfx) const;
	bool DoBallCollision(Ball& ball);
private:
	RectF rect;
	Color c;
	bool destroyed;
};