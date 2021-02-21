#include "Vector2D.h"

Vector2D::Vector2D()
{
	x = 0.0f;
	y = 0.0f;
}

Vector2D::Vector2D(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2D operator+(const Vector2D &v1, const Vector2D &v2)
{
	Vector2D rez;
	rez.x = v1.x + v2.x;
	rez.y = v1.y + v2.y;
	return rez;
}

Vector2D operator-(const Vector2D &v1, const Vector2D &v2)
{
	Vector2D rez;
	rez.x = v1.x - v2.x;
	rez.y = v1.y - v2.y;
	return rez;
}

Vector2D operator*(const Vector2D &v1, float alfa)
{
	Vector2D rez;
	rez.x = v1.x * alfa;
	rez.y = v1.y * alfa;
	return rez;
}

Vector2D operator/(const Vector2D &v1, float alfa)
{
	Vector2D rez;
	rez.x = v1.x / alfa;
	rez.y = v1.y / alfa;
	return rez;
}

Vector2D& Vector2D::operator+=(const Vector2D &v)
{
	this->x += v.x;
	this->y += v.y;
	return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D &v)
{
	this->x -= v.x;
	this->y -= v.y;
	return *this;
}

Vector2D& Vector2D::operator*=(const Vector2D &v)
{
	this->x *= v.x;
	this->y *= v.y;
	return *this;
}

Vector2D& Vector2D::operator/=(const Vector2D &v)
{
	this->x /= v.x;
	this->y /= v.y;
	return *this;
}

Vector2D& Vector2D::operator=(const Vector2D &v)
{
	this->x = v.x;
	this->y = v.y;
	return *this;
}

Vector2D& Vector2D::Zero()
{
	this->x = 0.0f;
	this->y = 0.0f;

	return *this;
}

std::ostream& operator<<(std::ostream& stream, const Vector2D& v)
{
	stream << "(" << v.x << "," << v.y << ")";
	return stream;
}