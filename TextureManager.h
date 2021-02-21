#pragma once
#include "Game.h" //contains "SDL.h", "SDL_image.h" and <iostream>

class TextureManager
{
public:
	//we make this method a static function, because we want it to be apllied as a class function. We dont want an object that can use this method.
	static SDL_Texture *LoadTexture(const char *fileName); //Creeaza o textura folosind o imagine si renderul.
	static void Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest);
};


