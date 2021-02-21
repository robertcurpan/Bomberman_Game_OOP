#pragma once
#include "SpriteComponent.h"


class PickupRange:public SpriteComponent
{

public:
	PickupRange() = default;
	PickupRange(const char* path, float theScale, bool breakable, float xpos = 0.0f, float ypos = 0.0f, int h = 32, int w = 32) :SpriteComponent(path, theScale, breakable, xpos, ypos, h, w)
	{
		pickupType = 'r';
	}
	~PickupRange() {}

	void init()
	{
		SpriteComponent::init();
		srcRect.x = 1 * 16;
		srcRect.y = 14 * 16;
	}

	void update() {}

	void draw()
	{
		if (isDead == false)
			SpriteComponent::draw();
	}
};