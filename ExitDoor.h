#pragma once
#include "SpriteComponent.h"
#include "Enemies.h"
#include "TextureManager.h"


class ExitDoor:public SpriteComponent
{
	SDL_Texture *door_open;
	SDL_Texture *door_closed;

public:
	ExitDoor() = default;
	ExitDoor(const char* path, float theScale, bool breakable, float xpos = 0.0f, float ypos = 0.0f, int h = 32, int w = 32) : SpriteComponent(path, theScale, breakable, xpos, ypos, h, w)
	{
		doorOpen = false;
		door_open = TextureManager::LoadTexture("assets/exit_door_opened.png");
		door_closed = TextureManager::LoadTexture("assets/exit_door_closed.png");
	}
	~ExitDoor() { SDL_DestroyTexture(door_open); SDL_DestroyTexture(door_closed); }

	void setOpen()
	{
		bool all_dead = true;
		for (int i = 0; i < Game::nrEnemies; i++)
		{
			if (Game::enemies[i]->isDead == false)
				all_dead = false;
		}

		if (all_dead == true)
			doorOpen = true;
		else
			doorOpen = false;
	}

	void init()
	{
		SpriteComponent::init();
	}

	void update()
	{
		setOpen();
	}

	void draw()
	{
		if (doorOpen == true)
			TextureManager::Draw(door_open, srcRect, destRect);
		else
			TextureManager::Draw(door_closed, srcRect, destRect);
	}
};