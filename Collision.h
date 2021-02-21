#pragma once
#include "SDL.h"
#include "Vector2D.h"

class Collision
{
public:
	//functie de detectie a coliziunii de tip AABB (axis aligned bounding box)
	static bool AABB(const SDL_Rect &rectA, const SDL_Rect &rectB);
};