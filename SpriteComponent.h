#pragma once
#include "ColliderComponent.h"
#include "Animations.h"


//Sprite-urile sunt obiectele non-statice din harta
//GameObject-urile sunt obiectele statice

class SpriteComponent : public ColliderComponent
{
	SDL_Texture* texture;

public:
	bool isDead;
	bool startDeathAnimation;
	int deathTimer;

	char pickupType;
	bool doorOpen;
	bool collidedWithOpenDoor;

	SDL_Rect srcRect, destRect;
	Animations animation;
	bool breakable;

	SpriteComponent() = default;
	SpriteComponent(const char* path, float theScale, bool breakable, float xpos = 0.0f, float ypos = 0.0f, int h = 32, int w = 32);
	~SpriteComponent() { SDL_DestroyTexture(texture); }

	void setTexture(const char* path);
	void setAnimation();

	void init() override;
	void update() override;
	void draw() override;

	int timerForDeathAnimation;
};
