#pragma once

#include "Graphics.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Vec2.h"
#include "Surface.h"

class Dude
{
public:
	Dude()
		:
		pos(300.0f, 400.0f)
	{
	}
	void ClampToScreen();
	void Draw( Graphics& gfx ) const;
	void Update( const Keyboard& kbd, const Mouse& mouse, float dt );
	Vec2 GetPos() const;
	float GetWidth() const;
	float GetHeight() const;
private:
	Vec2 pos;
	Surface sprite = "bmp/awsom.bmp";
	static constexpr float speed = 1.0f * 60.0f;
	static constexpr float width = 20.0f;
	static constexpr float height = 20.0f;
};