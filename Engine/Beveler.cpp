#include "Beveler.h"

Beveler::Beveler(Color baseColor)
{
	SetBaseColor(baseColor);
}

void Beveler::DrawOuterBevel(const RectF & rect, int size, Graphics & gfx)
{
	const int left = int(rect.left);
	const int right = int(rect.right);
	const int top = int(rect.top);
	const int bottom = int(rect.bottom);
	// lado izquierdo (esquina, orilla, esquina)
	gfx.DrawIsoRightTriBL(left, top, size, leftColor);
	gfx.DrawRect(left, top + size, left + size, bottom - size, leftColor);
	gfx.DrawIsoRightTriUL(left, bottom - size, size, leftColor);
	// arriba
	gfx.DrawIsoRightTriUR(left, top, size, topColor);
	gfx.DrawRect(left + size, top, right - size, top + size, topColor);
	gfx.DrawIsoRightTriUL(right - size, top, size, topColor);
	// derecha
	gfx.DrawIsoRightTriBR(right - size, top, size, rightColor);
	gfx.DrawRect(right - size, top + size, right, bottom - size, rightColor);
	gfx.DrawIsoRightTriUR(right - size, bottom - size, size, rightColor);
	// abajo
	gfx.DrawIsoRightTriBR(left, bottom - size, size, bottomColor);
	gfx.DrawRect(left + size, bottom - size, right - size, bottom, bottomColor);
	gfx.DrawIsoRightTriBL(right - size, bottom - size, size, bottomColor);
}

void Beveler::DrawInnerBevel(const RectF& rect, int size, Graphics & gfx)
{
	const int left = int(rect.left);
	const int right = int(rect.right);
	const int top = int(rect.top);
	const int bottom = int(rect.bottom);
	// lado izquierdo (esquina, orilla, esquina)
	gfx.DrawIsoRightTriBL(left, top, size, rightColor);
	gfx.DrawRect(left, top + size, left + size, bottom-size, rightColor);
	gfx.DrawIsoRightTriUL(left, bottom-size, size, rightColor);
	// arriba
	gfx.DrawIsoRightTriUR(left, top, size, bottomColor);
	gfx.DrawRect(left + size, top, right - size, top + size, bottomColor);
	gfx.DrawIsoRightTriUL(right - size, top, size, bottomColor);
	// derecha
	gfx.DrawIsoRightTriBR(right - size, top, size, leftColor);
	gfx.DrawRect(right - size, top + size, right, bottom - size, leftColor);
	gfx.DrawIsoRightTriUR(right - size, bottom - size, size, leftColor);
	// abajo
	gfx.DrawIsoRightTriBR(left, bottom - size, size, topColor);
	gfx.DrawRect(left + size, bottom - size, right - size, bottom, topColor);
	gfx.DrawIsoRightTriBL(right - size, bottom - size, size, topColor);
}

void Beveler::DrawBeveledBrick(const RectF & rect, int bevelSize, Graphics & gfx)
{
	DrawOuterBevel(rect, bevelSize, gfx);
	gfx.DrawRect(rect.GetExpanded(-float(bevelSize)), baseColor);
}

void Beveler::DrawBevelFrame(const RectF & rect, int bevelSize, Graphics & gfx)
{
	DrawOuterBevel(rect, bevelSize, gfx);
	DrawInnerBevel(rect.GetExpanded(-float(bevelSize)), bevelSize, gfx);
}

Color Beveler::GetBaseColor() const
{
	return baseColor;
}

void Beveler::SetBaseColor(Color base_in)
{
	baseColor = base_in;
	topColor = Color(
		int(float(baseColor.GetR()) * topFactor),
		int(float(baseColor.GetG()) * topFactor),
		int(float(baseColor.GetB()) * topFactor) );
	bottomColor = Color(
		int(float(baseColor.GetR()) * bottomFactor),
		int(float(baseColor.GetG()) * bottomFactor),
		int(float(baseColor.GetB()) * bottomFactor)	);
	leftColor = Color(
		int(float(baseColor.GetR()) * leftFactor),
		int(float(baseColor.GetG()) * leftFactor),
		int(float(baseColor.GetB()) * leftFactor));
	rightColor = Color(
		int(float(baseColor.GetR()) * rightFactor),
		int(float(baseColor.GetG()) * rightFactor),
		int(float(baseColor.GetB()) * rightFactor) );
}
