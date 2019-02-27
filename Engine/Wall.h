#pragma once
#include "Graphics.h"
#include "RectF.h"
#include "Colors.h"

class Wall
{
public:
	Wall(RectF& rect_in, float width_in);
	Wall(float x_in, float y_in, float w_in, float h_in, float width_in);
	RectF GetRect() const;
	void Draw(Graphics& gfx);
private:
	RectF rect;
	float width;
};