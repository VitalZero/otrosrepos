#pragma once
#include "SpriteCodex.h"
#include "Vec2.h"
#include "RectF.h"

class Paddle;

class Ball
{
public:
	Ball(Vec2& pos_in, Vec2& vel_in, Paddle& pad);
	void Draw(Graphics& gfx) const;
	void Update(float dt);
	bool DoWallCollision(RectF& wall);
	void ReboundX();
	void ReboundY(Vec2& padPos);
	void ReboundY();
	bool Died() const;
	RectF GetRect() const;
	Vec2 GetVel() const;
	Vec2 GetPos() const;
protected:
	Vec2 pos;
	Vec2 vel;
	Paddle& pad;
	bool died = false;
	static constexpr float radius = 7.0f;

};