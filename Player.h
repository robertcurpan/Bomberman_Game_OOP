#pragma once
#include "SpriteComponent.h"
#include "Bomb.h"


class Player :public SpriteComponent
{
	SDL_Rect futurePosition;
	char lastKeyPressed;
	bool stopPlayerAnimationFromKeyboard;
public:

	Player() = default;
	Player(const char* path, float theScale, bool breakable, float xpos = 0.0f, float ypos = 0.0f, int h = 32, int w = 32);
	~Player() {}

	void KeyboardControllerPlayer(); //functia in care asiguram miscarea obiectului cu ajutorul unor taste
	void collidePlayerWithBlocks();
	void collidePlayerWithExplosion();
	void collidePlayerWithEnemies();
	void collidePlayerWithOpenDoor();
	void collidePlayerWithPickups();

	void playerDeathAnimation();

	void init() override { SpriteComponent::init(); }

	void update() override;
	
	void draw() override;
};

