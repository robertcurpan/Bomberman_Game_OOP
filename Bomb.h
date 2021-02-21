#pragma once
#include "SDL.h"
#include "Map.h"


class Bomb
{
	SDL_Texture *bombTexture;
	SDL_Texture *explosionTexture;
	SDL_Texture *background;

	int radius;
	int animSpeed;
	int nrFrames;
public:
	static int bombStartTime;                //momentul cand e plasata o bomba
	static int explosionStartTime;
	
	SDL_Rect explosionBlocks[21]; //blocurile unde apar flacarile de la explozia bombei
	int dimExplosion;             //nr de blocuri de flacari produse de bomba (nr de elemente din vectorul explosionBlocks)

	SDL_Rect srcRect, destRect;
	SDL_Rect smallerCollider;
	SDL_Rect srcRectBackground;
	SDL_Rect srcRectExplosion;
	SDL_Rect rectChangeTextureUp, rectChangeTextureDown, rectChangeTextureLeft, rectChangeTextureRight;
	bool removeBlockUp, removeBlockDown, removeBlockLeft, removeBlockRight;
	bool spacebarPressed;
	bool bombActive;
	bool explosionActive;

	Bomb() = default;
	Bomb(const char *path, float xpos, float ypos);
	~Bomb();

	void setRadius(int r) { radius = r; }
	int getRadius() { return radius; }

	void KeyboardControllerBomb();
	void drawBomb();
	void eraseBomb(float dt);
	void bombPositionUpdate(SDL_Rect rect);
	void bombAnimation();
	void explosion(Map *&map);
};
