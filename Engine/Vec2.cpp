#include "Vec2.h"
#include <cmath>

Vec2::Vec2(float in_x, float in_y)
	:
	x(in_x),
	y(in_y)
{
}

Vec2 Vec2::operator+(const Vec2 & rhs) const
{

	return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 & Vec2::operator+=(const Vec2 & rhs)
{
	*this = *this + rhs;
	return *this;
}

Vec2 Vec2::operator*(const float rhs) const
{
	return Vec2(x * rhs, y * rhs);
}

Vec2 & Vec2::operator*=(const float rhs)
{
	*this = *this * rhs;
	return *this;
}

Vec2 Vec2::operator-(const Vec2 & rhs) const
{

	return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 & Vec2::operator-=(const Vec2 & rhs)
{
	*this = *this - rhs;
	return *this;
}

float Vec2::GetLength() const
{
	return sqrt(GetLengthSq());
}

float Vec2::GetLengthSq() const
{
	return x * x + y * y;
}

Vec2 & Vec2::Normalize()
{
	return *this = GetNormalized();
}

Vec2 Vec2::GetNormalized() const
{
	const float length = GetLength();
	if(length != 0.0f)
		return *this * (1.0f / length);

	return *this;
}
