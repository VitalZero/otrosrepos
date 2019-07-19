#pragma once
#include "SpriteCodex.h"
#include "Vec2.h"
#include "RectF.h"

class Paddle;

class Ball
{
public:
	Ball(const Vec2& pos_in, const Vec2& dir_in);
	void Draw(Graphics& gfx) const;
	void Update(float dt);
	// 0 = null, 1 = pared 2 = abajo
	int DoWallCollision(RectF& wall);
	void ReboundX();
	void ReboundY(Vec2& padPos);
	void ReboundY();
	RectF GetRect() const;
	Vec2 GetVel() const;
	Vec2 GetPos() const;
	void SetDirection(const Vec2& dir);
protected:
	Vec2 pos;
	Vec2 vel;
	float speed = 400.0f;
	bool died = false;
	static constexpr float radius = 7.0f;
};