#include "Wall.h"

Wall::Wall(RectF& rect_in, float width_in)
	:
	rect(rect_in), 
	width(width_in)
{
}

Wall::Wall(float x_in, float y_in, float w_in, float h_in, float width_in)
	:
	Wall(RectF(x_in, y_in, w_in, h_in), width_in)
{
}

RectF Wall::GetRect() const
{
	return RectF(rect.left + width, rect.top + width, rect.right - width, rect.bottom);
}

void Wall::Draw(Graphics& gfx)
{
	//top
	gfx.DrawRect((int)rect.left, (int)rect.top, (int)rect.right, (int)(rect.top + width), Colors::White );
	//left
	gfx.DrawRect((int)rect.left, (int)rect.top, (int)(rect.left + width), (int)rect.bottom, Colors::White);
	//bottom
	//gfx.DrawRect((int)rect.left, (int)(rect.bottom-width), (int)rect.right, (int)rect.bottom, Colors::White);
	//right
	gfx.DrawRect((int)(rect.right-width), (int)rect.top, (int)rect.right, (int)rect.bottom, Colors::White);

}
