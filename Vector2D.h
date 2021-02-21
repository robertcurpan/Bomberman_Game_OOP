#pragma once
#include <iostream>

class Vector2D
{
public:
	float x, y;

	Vector2D();
	Vector2D(float x, float y);

	friend Vector2D operator+(const Vector2D &v1, const Vector2D &v2); //le-am facut fct prietene pt a nu modifica un vector dupa o operatie.
	friend Vector2D operator-(const Vector2D &v1, const Vector2D &v2);
	friend Vector2D operator*(const Vector2D &v1, float alfa);
	friend Vector2D operator/(const Vector2D &v1, float alfa);

	Vector2D& operator+=(const Vector2D &v);
	Vector2D& operator-=(const Vector2D &v);
	Vector2D& operator*=(const Vector2D &v);
	Vector2D& operator/=(const Vector2D &v);
	Vector2D& operator=(const Vector2D &v);

	Vector2D& Zero();

	friend std::ostream& operator<<(std::ostream& stream, const Vector2D& v);
};
