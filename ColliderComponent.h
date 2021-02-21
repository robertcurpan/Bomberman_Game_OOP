#pragma once
#include "Transform.h"
#include "SDL.h"


class ColliderComponent :public Transform
{
public:
	SDL_Rect collider; //pozitia si dimensiunile obiectului de pe harta
	SDL_Rect smallerCollider; //cream un hitbox mai mic pentru tile-uri ca sa putem trece printre 2 ziduri paralele aflate la distanta de 1 tile (32 pixeli) unul de celalalt

	ColliderComponent() = default;
	ColliderComponent(float xpos, float ypos, float theScale, int h, int w) :Transform(xpos, ypos, theScale, h, w) {}
	

	void init() override
	{
		Transform::init();

		collider.x = static_cast<int>(position.x);
		collider.y = static_cast<int>(position.y);
		collider.w = static_cast<int>(width*scale);
		collider.h = static_cast<int>(height*scale);

		smallerCollider.x = collider.x + 4;
		smallerCollider.y = collider.y + 4;
		smallerCollider.w = collider.w - 8;
		smallerCollider.h = collider.h - 8;
	}

	void update() override
	{
		Transform::update();

		collider.x = static_cast<int>(position.x);
		collider.y = static_cast<int>(position.y);
		collider.w = static_cast<int>(width*scale);
		collider.h = static_cast<int>(height*scale);

		smallerCollider.x = collider.x + 4;
		smallerCollider.y = collider.y + 4;
		smallerCollider.w = collider.w - 8;
		smallerCollider.h = collider.h - 8;
	}
	
};
