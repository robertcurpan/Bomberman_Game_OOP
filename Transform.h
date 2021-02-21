#pragma once
#include "Vector2D.h"
#include "Component.h"
#include "Level.h"


class Transform : public Component
{
	
public:
	Vector2D position; //pozitia obiectului
	Vector2D velocity; //in ce directie ii aplicam viteza(viteza poz/neg pe x/y)
	float speed;     //viteza (cu cati pixeli se misca)
	int height;   //width si height sunt dimensiunile imaginii(texturii) pe care o folosim
	int width;	  //uzual ele vor fi 32x32
	float scale;

	Transform()
	{
		position.Zero();
	}

	Transform(float xpos, float ypos, float theScale, int h, int w)
	{
		position.x = xpos;
		position.y = ypos;
		scale = theScale;
		height = h; 
		width = w;
	}

	void init()
	{
		velocity.Zero(); //velocity nu se afla in constructor pt ca nu vrem sa o specificam
					     //la crearea unui obiect. Aceasta depinde de alte situatii
		if(Level::level == 1)
			speed = 3;  //viteza player (viteza inamicilor o setam in functia setMovement din clasa Enemies)
		if (Level::level == 2)
			speed = 2;  
		if (Level::level == 3)
			speed = 2;
	}

	void update()
	{
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}
};