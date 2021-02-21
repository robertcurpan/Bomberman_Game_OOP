#pragma once
#include "SpriteComponent.h"


class PickupSpeed :public SpriteComponent
{

public:
	PickupSpeed() = default;
	PickupSpeed(const char* path, float theScale, bool breakable, float xpos = 0.0f, float ypos = 0.0f, int h = 32, int w = 32) :SpriteComponent(path, theScale, breakable, xpos, ypos, h, w)
	{
		pickupType = 's';
	}
	~PickupSpeed() {}

	void init()
	{
		SpriteComponent::init();
		srcRect.x = 3 * 16;
		srcRect.y = 14 * 16;
	}

	void update() {}

	void draw()
	{
		if (isDead == false)
			SpriteComponent::draw();
	}
};
