#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char *fileName)
{
	SDL_Surface *tempSurface = IMG_Load(fileName); //cream o suprafata din imaginea respectiva
	SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface); //cream o textura din suprafata
	SDL_FreeSurface(tempSurface); //eliberam suprafata

	return tex;
}

void TextureManager::Draw(SDL_Texture * tex, SDL_Rect src, SDL_Rect dest)
{
	SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}
