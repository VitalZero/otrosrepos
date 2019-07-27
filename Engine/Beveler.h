#pragma once

#include "Graphics.h"
class Beveler
{
public:
	Beveler(Color baseColor);
	void DrawOuterBevel(const RectF& rect, int size, Graphics& gfx);
	void DrawInnerBevel(const RectF& rect, int size, Graphics& gfx);
	void DrawBeveledBrick(const RectF& rect, int bevelSize, Graphics& gfx);
	void DrawBevelFrame(const RectF& rect, int bevelSize, Graphics& gfx);
	Color GetBaseColor() const; 
	void SetBaseColor(Color base_in);
private:
	static constexpr float leftFactor = 1.10f;
	static constexpr float topFactor = 0.93f;
	static constexpr float rightFactor = 0.65f;
	static constexpr float bottomFactor = 0.80f;
	Color baseColor;
	Color topColor;
	Color bottomColor;
	Color leftColor;
	Color rightColor;
};