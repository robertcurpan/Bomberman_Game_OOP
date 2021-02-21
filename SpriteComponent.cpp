#include "SpriteComponent.h"
#include "TextureManager.h"


SpriteComponent::SpriteComponent(const char* path, float theScale, bool breakable, float xpos, float ypos, int h, int w) :ColliderComponent(xpos, ypos, theScale, h, w)
{
	setTexture(path);
	this->breakable = breakable;
	this->timerForDeathAnimation = 0;

	this->isDead = false;
	this->startDeathAnimation = false;
	this->deathTimer = 0;
}


void SpriteComponent::setTexture(const char* path)
{
	texture = TextureManager::LoadTexture(path); //renderer e var statica in cadrul clasei Game
}

void SpriteComponent::setAnimation()
{
	switch (animation.animID)
	{
	case Animations::walkUp: //mers in sus
		animation.nrFrames = 3;
		srcRect.x = 3 * 16 + 16 * static_cast<int>((SDL_GetTicks() / animation.animSpeed) % animation.nrFrames);
		srcRect.y = 16;
		break;
	case Animations::walkLeft: //mers la stanga
		animation.nrFrames = 3;
		srcRect.x = 0 + 16 * static_cast<int>((SDL_GetTicks() / animation.animSpeed) % animation.nrFrames);
		srcRect.y = 0;
		break;
	case Animations::walkDown: //mers in jos
		animation.nrFrames = 3;
		srcRect.x = 3 * 16 + 16 * static_cast<int>((SDL_GetTicks() / animation.animSpeed) % animation.nrFrames);
		srcRect.y = 0;
		break;
	case Animations::walkRight: //mers la dreapta
		animation.nrFrames = 3;
		srcRect.x = 0 + 16 * static_cast<int>((SDL_GetTicks() / animation.animSpeed) % animation.nrFrames);
		srcRect.y = 16;
		break;
	case Animations::idleUp: //playerul se opreste (se vede spatele)
		srcRect.x = 4 * 16;
		srcRect.y = 16;
		break;
	case Animations::idleLeft: //profil stanga
		srcRect.x = 16;
		srcRect.y = 0;
		break;
	case Animations::idleDown: //playerul se opreste (se vede fata)
		srcRect.x = 4 * 16;
		srcRect.y = 0;
		break;
	case Animations::idleRight: //profil dreapta
		srcRect.x = 16;
		srcRect.y = 16;
		break;
	case Animations::enemyID1:
		animation.animSpeed = 200;
		animation.nrFrames = 6;
		srcRect.x = 0 + 16 * static_cast<int>((SDL_GetTicks() / animation.animSpeed) % animation.nrFrames);
		srcRect.y = 15 * 16;
		break;
	case Animations::enemyID2:
		animation.animSpeed = 200;
		animation.nrFrames = 6;
		srcRect.x = 0 + 16 * static_cast<int>((SDL_GetTicks() / animation.animSpeed) % animation.nrFrames);
		srcRect.y = 17 * 16;
		break;
	case Animations::enemyID3:
		animation.animSpeed = 200;
		animation.nrFrames = 6;
		srcRect.x = 0 + 16 * static_cast<int>((SDL_GetTicks() / animation.animSpeed) % animation.nrFrames);
		srcRect.y = 19 * 16;
		break;
	case Animations::deathEnemyID1:
		timerForDeathAnimation++;
		if (timerForDeathAnimation > 0 && timerForDeathAnimation <= 12)
			srcRect.x = 6 * 16;
		if (timerForDeathAnimation > 12 && timerForDeathAnimation <= 24)
			srcRect.x = 7 * 16;
		if (timerForDeathAnimation > 24 && timerForDeathAnimation <= 36)
			srcRect.x = 8 * 16;
		if (timerForDeathAnimation > 36 && timerForDeathAnimation <= 48)
			srcRect.x = 9 * 16;
		if (timerForDeathAnimation > 48 && timerForDeathAnimation < 60)
			srcRect.x = 10 * 16;
		if (timerForDeathAnimation >= 60)
			timerForDeathAnimation = 0;
		srcRect.y = 15 * 16;
		break;
	case Animations::deathEnemyID2:
		timerForDeathAnimation++;
		if (timerForDeathAnimation > 0 && timerForDeathAnimation <= 12)
			srcRect.x = 6 * 16;
		if (timerForDeathAnimation > 12 && timerForDeathAnimation <= 24)
			srcRect.x = 7 * 16;
		if (timerForDeathAnimation > 24 && timerForDeathAnimation <= 36)
			srcRect.x = 8 * 16;
		if (timerForDeathAnimation > 36 && timerForDeathAnimation <= 48)
			srcRect.x = 9 * 16;
		if (timerForDeathAnimation > 48 && timerForDeathAnimation < 60)
			srcRect.x = 10 * 16;
		if (timerForDeathAnimation >= 60)
			timerForDeathAnimation = 0;
		srcRect.y = 17 * 16;
		break;
	case Animations::deathEnemyID3:
		timerForDeathAnimation++;
		if (timerForDeathAnimation > 0 && timerForDeathAnimation <= 12)
		{
			srcRect.x = 6 * 16;
			srcRect.y = 19 * 16;
		}
		if (timerForDeathAnimation > 12 && timerForDeathAnimation <= 24)
		{
			srcRect.x = 7 * 16;
			srcRect.y = 18 * 16;
		}
		if (timerForDeathAnimation > 24 && timerForDeathAnimation <= 36)
		{
			srcRect.x = 8 * 16;
			srcRect.y = 18 * 16;
		}
		if (timerForDeathAnimation > 36 && timerForDeathAnimation <= 48)
		{
			srcRect.x = 9 * 16;
			srcRect.y = 18 * 16;
		}
		if (timerForDeathAnimation > 48 && timerForDeathAnimation < 60)
		{
			srcRect.x = 10 * 16;
			srcRect.y = 18 * 16;
		}
		if (timerForDeathAnimation >= 60)
			timerForDeathAnimation = 0;
		break;
	case Animations::deathPlayer:
		timerForDeathAnimation++;
		if (timerForDeathAnimation > 0 && timerForDeathAnimation <= 9)
			srcRect.x = 0;
		if (timerForDeathAnimation > 9 && timerForDeathAnimation <= 18)
			srcRect.x = 16;
		if (timerForDeathAnimation > 18 && timerForDeathAnimation <= 27)
			srcRect.x = 2*16;
		if (timerForDeathAnimation > 27 && timerForDeathAnimation <= 36)
			srcRect.x = 3*16;
		if (timerForDeathAnimation > 36 && timerForDeathAnimation <= 45)
			srcRect.x = 4*16;
		if (timerForDeathAnimation > 45 && timerForDeathAnimation <= 53)
			srcRect.x = 5*16;
		if (timerForDeathAnimation > 53 && timerForDeathAnimation < 60)
			srcRect.x = 6*16;
		if (timerForDeathAnimation >= 60)
			timerForDeathAnimation = 0;

		srcRect.y = 2 * 16;
		break;
	default:
		break;
	}
}

void SpriteComponent::init()
{
	animation.animID = Animations::nothing;
	animation.animSpeed = 100;

	srcRect.x = srcRect.y = 0;
	srcRect.w = width; //ATENTIE posibil incorect!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	srcRect.h = height;
	destRect.w = width*scale;
	destRect.h = height*scale;
	

	destRect.x = (int)position.x;  //pozitia initiala (in fereastra) a playerului
	destRect.y = (int)position.y;  //destRect are coordonate int-uri

	ColliderComponent::init();
}

void SpriteComponent::update()
{
	ColliderComponent::update();

	setAnimation();

	destRect.x = static_cast<int>(position.x);
	destRect.y = static_cast<int>(position.y);
	
}

void SpriteComponent::draw()
{
	TextureManager::Draw(texture, srcRect, destRect);
}

