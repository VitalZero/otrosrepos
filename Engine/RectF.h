#pragma once
#include "Vec2.h"

class RectF
{
public:
	RectF() = default;
	RectF(float left_in, float top_in, float right_in, float bottom_in);
	RectF(const Vec2& topLeft, const Vec2& bottomRight);
	RectF(const Vec2& topLeft, float width_in, float height_in);
public:
	float left, top, right, bottom;
	bool IsOverlapping(const RectF& other);
	static RectF FromCenter(Vec2& center, float hWidth, float hHeight);
private:

};