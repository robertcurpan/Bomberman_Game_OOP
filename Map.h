#pragma once
#include "Game.h"

class Map
{
	SDL_Rect src, dest;

	SDL_Texture *background;
	SDL_Texture *solid_block;

	int level1_map[20][25];
	int level2_map[20][25];
	int level3_map[20][25];
public:
	int map[20][25];

	Map();
	~Map();

	void LoadMap(int arr[20][25]);
	void DrawMap();
	void PreparingSprites();
};