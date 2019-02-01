#pragma once
#include "SpriteCodex.h"
#include "Vec2.h"
#include "RectF.h"

class Ball
{
public:
	Ball(Vec2& pos_in, Vec2& vel_in);
	void Draw(Graphics& gfx) const;
	void Update(float dt);
	bool DoWallCollision(RectF& wall);
	void ReboundX();
	void ReboundY();
	RectF GetRect() const;
	Vec2 GetVel();
protected:
	Vec2 pos;
	Vec2 vel;
	static constexpr float radius = 7.0f;

};