#pragma once
#include "SpriteComponent.h"
#include "Bomb.h"


class Enemy :public SpriteComponent
{
	SDL_Rect futurePosition;
	int enemyID;
	bool verticalMovement; //true -> se misca pe verticala, false -> se misca pe orizontala
public:

	Enemy() = default;
	Enemy(const char* path, float theScale, bool breakable, int enemyID, bool verticalMovement, float xpos = 0.0f, float ypos = 0.0f, int h = 32, int w = 32);
	~Enemy() {}

	int getEnemyID() { return enemyID; }
	SDL_Rect getFuturePosition() { return futurePosition; }

	void setMovement();

	void collideWithBlocksAndBombs(); //functie membra a clasei -> avem for cu toti inamicii in Game.cpp
	void collideWithBlocksAndBombsV2();

	void init() override
	{
		SpriteComponent::init();
		setMovement();
	}

	void update() override
	{
		SpriteComponent::update();
	}

	void draw() override
	{
		if(isDead == false)
			SpriteComponent::draw();
	}
};

void collideEnemiesWithExplosion();

void collideEnemiesWithOtherEnemies(); //functie globala, avem for-ul cu toti inamicii inclus in functie

void enemiesDeathAnimation();

void updateEnemies();