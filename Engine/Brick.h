#pragma once
#include "RectF.h"
#include "Graphics.h"
#include "Colors.h"

class Brick
{
public:
	Brick(const RectF& rect_in, const Color& c_in);
	void Draw(Graphics& gfx) const;
private:
	RectF rect;
	Color c;
	bool destroyed;
};