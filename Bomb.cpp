#include "Bomb.h"
#include "TextureManager.h"
#include "Game.h"
#include "Collision.h"
#include "Level.h"
#include "Player.h"
#include "Map.h"

int Bomb::bombStartTime = 0;
int Bomb::explosionStartTime = 0;

void Bomb::KeyboardControllerBomb()
{
	if (Game::event.type == SDL_KEYDOWN)
	{
		switch (Game::event.key.keysym.sym)
		{
		case SDLK_SPACE:
			spacebarPressed = true;
			break;
		default:
			break;
		}
	}
}

Bomb::~Bomb()
{
	SDL_DestroyTexture(bombTexture);
	SDL_DestroyTexture(explosionTexture);
	SDL_DestroyTexture(background);
}

Bomb::Bomb(const char *path, float xpos, float ypos)
{
	if(Level::level == 1)
		radius = 3; //fara blocul din centru (cel unde se afla bomba)
	if (Level::level == 2)
		radius = 2; //fara blocul din centru (cel unde se afla bomba)
	if (Level::level == 3)
		radius = 2;
	dimExplosion = 0;
	bombActive = false;
	explosionActive = false;
	nrFrames = 3;
	animSpeed = 100;
	removeBlockUp = removeBlockDown = removeBlockLeft = removeBlockRight = false;

	srcRectExplosion.x = 2 * 16;
	srcRectExplosion.y = 11 * 16;
	srcRectExplosion.w = srcRectExplosion.h = 16;

	srcRectBackground.x = srcRectBackground.y = 0;
	srcRectBackground.h = srcRectBackground.w = 32;
	

	srcRect.x = 0;
	srcRect.y = 3 * 16;
	srcRect.w = srcRect.h = 16;
	destRect.w = destRect.h = 32;
	destRect.x = (static_cast<int>(xpos) / 32) * 32;
	destRect.y = (static_cast<int>(ypos) / 32) * 32;

	bombTexture = TextureManager::LoadTexture(path);
	explosionTexture = TextureManager::LoadTexture(path); //acelasi spritesheet
	background = TextureManager::LoadTexture("assets/background.png");
}

void Bomb::drawBomb()
{
	TextureManager::Draw(bombTexture, srcRect, destRect);
}

void Bomb::bombAnimation()
{
	if (spacebarPressed == true)
	{
		srcRect.x = 16 * static_cast<int>((SDL_GetTicks() / animSpeed) % nrFrames);
		srcRect.y = 3 * 16;
		drawBomb();
		bombActive = true;
	}
}

void Bomb::bombPositionUpdate(SDL_Rect rect)
{
	//bomba trebuie plasata intr-un Rect cu x si y divizibile cu 32
	if (rect.x - rect.x / 32 * 32 >= 16)
	{
		destRect.x = (rect.x / 32) * 32 + 32;
	}
	else
	{
		destRect.x = (rect.x / 32) * 32;
	}
	if (rect.y - rect.y / 32 * 32 >= 16)
	{
		destRect.y = (rect.y / 32) * 32 + 32;
	}
	else
	{
		destRect.y = (rect.y / 32) * 32;
	}

	smallerCollider.x = destRect.x + 4;
	smallerCollider.y = destRect.y + 4;
	smallerCollider.h = destRect.h - 8;
	smallerCollider.w = destRect.w - 8;
}

void Bomb::eraseBomb(float dt) //dt = nr de secunde dupa care vrem sa dispara bomba
{
	//programul parcurge codul din main de 60 de ori intr-o secunda (60 FPS)
	Bomb::bombStartTime++;
	if (Bomb::bombStartTime > 60 * dt)
	{
		Bomb::bombStartTime = 0;
		spacebarPressed = false;
		bombActive = false;
		explosionActive = true;
	}
}

void Bomb::explosion(Map *&map)
{
	//stim pozitia bombei (destRect) si raza exploziei (radius), deci putem calcula
	//toate blocurile unde ar trebui sa plasam flacarile. Aceste blocuri le punem in
	//vectorul explosionBlocks[21]
	Bomb::explosionStartTime++;

	int destroyedBlockUpPosition, destroyedBlockDownPosition, destroyedBlockLeftPosition, destroyedBlockRightPosition;
	bool foundCollision;
	dimExplosion = radius * 4 + 1;
	explosionBlocks[0] = destRect; //pozitia bombei

	foundCollision = false;
	for (int i = 1; (i < radius + 1) && (foundCollision == false); i++) //adaugam blocurile de explozie de deasupra bombei
	{
		explosionBlocks[i].x = destRect.x;
		explosionBlocks[i].y = destRect.y - i * 32;
		explosionBlocks[i].w = explosionBlocks[i].h = 32;

		for (int j = 0; (j < Game::dim) && (foundCollision == false); j++)
		{
			
			if (explosionBlocks[i].x == Game::collidingBlocks[j]->destRect.x && explosionBlocks[i].y == Game::collidingBlocks[j]->destRect.y)
			{
				if (Game::collidingBlocks[j]->breakable == true)
				{
					foundCollision = true;
					removeBlockUp = true;
					destroyedBlockUpPosition = j;
					map->map[explosionBlocks[i].y / 32][explosionBlocks[i].x / 32] = 0; //desenam fundal in locul blocului distrus

					for (int k = i+1; k < radius + 1; k++) //nu mai afisam exploziile de dupa bloc
					{
						explosionBlocks[k].x = -32;
						explosionBlocks[k].y = -32;
						explosionBlocks[k].w = explosionBlocks[k].h = 0;
					}
				}
				else
				{
					//blocurile de explozie (de la al i-lea mai departe) din directia respectiva (aici de sus) nu vor mai fi afisate si nu vor putea interactiona cu alte obiecte
					foundCollision = true;
					for (int k = i; k < radius + 1; k++)
					{
						explosionBlocks[k].x = -32;
						explosionBlocks[k].y = -32;
						explosionBlocks[k].w = explosionBlocks[k].h = 0;
					}
				}
			}
		}
	}

	foundCollision = false;
	for (int i = radius+1; (i < 2*radius + 1) && (foundCollision == false); i++) //adaugam blocurile de explozie de sub bomba
	{
		explosionBlocks[i].x = destRect.x; //explosionBlocks[0].x
		explosionBlocks[i].y = destRect.y + (i - radius) * 32;
		explosionBlocks[i].w = explosionBlocks[i].h = 32;

		for (int j = 0; (j < Game::dim) && (foundCollision == false); j++)
		{

			if (explosionBlocks[i].x == Game::collidingBlocks[j]->destRect.x && explosionBlocks[i].y == Game::collidingBlocks[j]->destRect.y)
			{
				if (Game::collidingBlocks[j]->breakable == true)
				{
					foundCollision = true;
					removeBlockDown = true;
					destroyedBlockDownPosition = j;
					map->map[explosionBlocks[i].y / 32][explosionBlocks[i].x / 32] = 0; //desenam fundal in locul blocului distrus

					for (int k = i + 1; k < 2*radius + 1; k++) //nu mai afisam exploziile de dupa bloc
					{
						explosionBlocks[k].x = -32;
						explosionBlocks[k].y = -32;
						explosionBlocks[k].w = explosionBlocks[k].h = 0;
					}
				}
				else
				{
					//blocurile de explozie (de la al i-lea mai departe) din directia respectiva (aici de sus) nu vor mai fi afisate si nu vor putea interactiona cu alte obiecte
					foundCollision = true;
					for (int k = i; k < 2*radius + 1; k++)
					{
						explosionBlocks[k].x = -32;
						explosionBlocks[k].y = -32;
						explosionBlocks[k].w = explosionBlocks[k].h = 0;
					}
				}
			}
		}
	}

	foundCollision = false;
	for (int i = 2*radius + 1; (i < 3*radius + 1) && (foundCollision == false); i++) //adaugam blocurile de explozie din dreapta bombei
	{
		explosionBlocks[i].x = destRect.x + (i - 2 * radius) * 32;
		explosionBlocks[i].y = destRect.y;
		explosionBlocks[i].w = explosionBlocks[i].h = 32;

		for (int j = 0; (j < Game::dim) && (foundCollision == false); j++)
		{

			if (explosionBlocks[i].x == Game::collidingBlocks[j]->destRect.x && explosionBlocks[i].y == Game::collidingBlocks[j]->destRect.y)
			{
				if (Game::collidingBlocks[j]->breakable == true)
				{
					foundCollision = true;
					removeBlockRight = true;
					destroyedBlockRightPosition = j;
					map->map[explosionBlocks[i].y / 32][explosionBlocks[i].x / 32] = 0; //desenam fundal in locul blocului distrus

					for (int k = i + 1; k < 3*radius + 1; k++) //nu mai afisam exploziile de dupa bloc
					{
						explosionBlocks[k].x = -32;
						explosionBlocks[k].y = -32;
						explosionBlocks[k].w = explosionBlocks[k].h = 0;
					}
				}
				else
				{
					//blocurile de explozie (de la al i-lea mai departe) din directia respectiva (aici de sus) nu vor mai fi afisate si nu vor putea interactiona cu alte obiecte
					foundCollision = true;
					for (int k = i; k < 3*radius + 1; k++)
					{
						explosionBlocks[k].x = -32;
						explosionBlocks[k].y = -32;
						explosionBlocks[k].w = explosionBlocks[k].h = 0;
					}
				}
			}
		}
	}

	foundCollision = false;
	for (int i = 3*radius + 1; (i < 4*radius + 1) && (foundCollision == false); i++) //adaugam blocurile de explozie din stanga bombei
	{
		explosionBlocks[i].x = destRect.x - (i - 3 * radius) * 32;
		explosionBlocks[i].y = destRect.y;
		explosionBlocks[i].w = explosionBlocks[i].h = 32;

		for (int j = 0; (j < Game::dim) && (foundCollision == false); j++)
		{

			if (explosionBlocks[i].x == Game::collidingBlocks[j]->destRect.x && explosionBlocks[i].y == Game::collidingBlocks[j]->destRect.y)
			{
				if (Game::collidingBlocks[j]->breakable == true)
				{
					foundCollision = true;
					removeBlockLeft = true;
					destroyedBlockLeftPosition = j;
					map->map[explosionBlocks[i].y / 32][explosionBlocks[i].x / 32] = 0; //desenam fundal in locul blocului distrus

					for (int k = i + 1; k < 4*radius + 1; k++) //nu mai afisam exploziile de dupa bloc
					{
						explosionBlocks[k].x = -32;
						explosionBlocks[k].y = -32;
						explosionBlocks[k].w = explosionBlocks[k].h = 0;
					}
				}
				else
				{
					//blocurile de explozie (de la al i-lea mai departe) din directia respectiva (aici de sus) nu vor mai fi afisate si nu vor putea interactiona cu alte obiecte
					foundCollision = true;
					for (int k = i; k < 4*radius + 1; k++)
					{
						explosionBlocks[k].x = -32;
						explosionBlocks[k].y = -32;
						explosionBlocks[k].w = explosionBlocks[k].h = 0;
					}
				}
			}
		}
	}

	
	for (int i = 0; i < dimExplosion; i++)
	{
		TextureManager::Draw(explosionTexture, srcRectExplosion, explosionBlocks[i]);
	}

	if (Bomb::explosionStartTime > 15) //explozia ramane activa jumate de secunda
	{
		Bomb::explosionStartTime = 0;
		explosionActive = false;
		
		if (removeBlockUp == true)
		{
			Game::collidingBlocks[destroyedBlockUpPosition] = Game::collidingBlocks[Game::dim - 1]; //scoatem blocul spart din lista blocurilor cu care putem face coliziune
			Game::dim--;
			removeBlockUp = false;
		}
		if (removeBlockDown == true)
		{
			Game::collidingBlocks[destroyedBlockDownPosition] = Game::collidingBlocks[Game::dim - 1]; //scoatem blocul spart din lista blocurilor cu care putem face coliziune
			Game::dim--;
			removeBlockDown = false;
		}
		if (removeBlockRight == true)
		{
			Game::collidingBlocks[destroyedBlockRightPosition] = Game::collidingBlocks[Game::dim - 1]; //scoatem blocul spart din lista blocurilor cu care putem face coliziune
			Game::dim--;
			removeBlockRight = false;
		}
		if (removeBlockLeft == true)
		{
			Game::collidingBlocks[destroyedBlockLeftPosition] = Game::collidingBlocks[Game::dim - 1]; //scoatem blocul spart din lista blocurilor cu care putem face coliziune
			Game::dim--;
			removeBlockLeft = false;
		}
	}
}
