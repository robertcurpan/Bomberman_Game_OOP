#include "Map.h"
#include "TextureManager.h"
#include "SpriteComponent.h"
#include "Level.h"
#include <fstream>


Map::Map()
{
	background = TextureManager::LoadTexture("assets/background.png");
	solid_block = TextureManager::LoadTexture("assets/solid_block.png");

	std::ifstream readMap1("assets/level1_map.txt");
	std::ifstream readMap2("assets/level2_map.txt");
	std::ifstream readMap3("assets/level3_map.txt");
	
//////////////////////////////////////////////////////////////
	try
	{
		if (!readMap1.is_open())
			throw 90;
		else
		{
			std::cout << "S-a deschis primul fisier.\n";
			for (int i = 0; i < 20; i++)
				for (int j = 0; j < 25; j++)
					readMap1 >> level1_map[i][j];
		}
	}
	catch (int x) { std::cout << "Exception: The file did not open.\n"; }
	readMap1.close();
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
	try
	{
		if (!readMap2.is_open())
			throw 91;
		else
		{
			std::cout << "S-a deschis al doilea fisier.\n";
			for (int i = 0; i < 20; i++)
				for (int j = 0; j < 25; j++)
					readMap2 >> level2_map[i][j];
		}
	}
	catch (int x) { std::cout << "Exception: The file did not open.\n"; }
	readMap2.close();
/////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
	try
	{
		if (!readMap3.is_open())
			throw 92;
		else
		{
			std::cout << "S-a deschis al treilea fisier.\n";
			for (int i = 0; i < 20; i++)
				for (int j = 0; j < 25; j++)
					readMap3 >> level3_map[i][j];
		}
	}
	catch (int x) { std::cout << "Exception: The file did not open.\n"; }
	readMap3.close();
///////////////////////////////////////////////////////////////////


	switch (Level::level)
	{
	case 1:
		LoadMap(level1_map);
		break;
	case 2:
		LoadMap(level2_map);
		break;
	case 3:
		LoadMap(level3_map);
		break;
	default:
		break;
	}
	
	src.x = src.y = 0;
	dest.x = dest.y = 0;
	src.w = dest.w = 32;
	src.h = dest.h = 32;

}

Map::~Map()
{
	SDL_DestroyTexture(background);
	SDL_DestroyTexture(solid_block);
}

void Map::LoadMap(int arr[20][25])
{
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 25; j++)
			map[i][j] = arr[i][j];
}

void Map::DrawMap()
{
	int type = 0;
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 25; j++)
		{
			type = map[i][j];

			dest.x = j * 32;
			dest.y = i * 32;

			if (type == 0)
			{
				TextureManager::Draw(background, src, dest);//imagine de fundal, doar o afisam.
			}
		}
}

void Map::PreparingSprites()
{
	int type = 0;
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 25; j++)
		{
			type = map[i][j];

			dest.x = j * 32;
			dest.y = i * 32;

			switch (type)
			{
			case 0:
				break;
			case 1: //blocurile breakable
				Game::collidingBlocks[Game::dim++] = new SpriteComponent("assets/breakable_block.png", 1, true, (float)dest.x, (float)dest.y, 32, 32);
				break;
			case 2: //blocurile non-breakable
				Game::collidingBlocks[Game::dim++] = new SpriteComponent("assets/solid_block.png", 1, false, (float)dest.x, (float)dest.y, 32, 32);
				break;
			default:
				break;
			}
		}
}