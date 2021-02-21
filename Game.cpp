#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Collision.h"
#include "Player.h"
#include "Bomb.h"
#include "Enemies.h"
#include "Level.h"
#include "ExitDoor.h"
#include "PickupRange.h"
#include "PickupSpeed.h"


SpriteComponent *player;  //declaram obiectele global
Enemy* Game::enemies[10];
int Game::nrEnemies;
Map *map;
Bomb* Game::bomb;
SpriteComponent* Game::collidingBlocks[500];
int Game::dim;
SpriteComponent* Game::exitDoor;
SpriteComponent* Game::pickups[4];
int Game::nrPickups;

SDL_Renderer* Game::renderer = nullptr; //va fi initializat in init
SDL_Event Game::event;


void Game::setPositions()
{
	if (Level::level == 1)
	{
		enemiesPos[0].x = 5*32;  enemiesPos[0].y = 1*32;
		enemiesPos[1].x = 9*32;  enemiesPos[1].y = 11*32;
		enemiesPos[2].x = 15*32;  enemiesPos[2].y = 2*32;
		enemiesPos[3].x = 17*32;  enemiesPos[3].y = 11*32;
		enemiesPos[4].x = 15*32;  enemiesPos[4].y = 17*32;
		enemiesPos[5].x = 3*32;  enemiesPos[5].y = 17*32;
		enemiesPos[6].x = 23*32;  enemiesPos[6].y = 14*32;
		enemiesPos[7].x = 15*32;  enemiesPos[7].y = 5*32;
		enemiesPos[8].x = 23*32;  enemiesPos[8].y = 2*32;
		enemiesPos[9].x = 20*32;  enemiesPos[9].y = 18*32;

		pickupsPos[0].x = 3*32;  pickupsPos[0].y = 2*32;
		pickupsPos[1].x = 13*32;  pickupsPos[1].y = 3*32;
		pickupsPos[2].x = 13*32;  pickupsPos[2].y = 11*32;
		pickupsPos[3].x = 23*32;  pickupsPos[3].y = 11*32;

		exitDoorPos.x = 22*32;  exitDoorPos.y = 18*32;
	}
	if (Level::level == 2)
	{
		enemiesPos[0].x = 3 * 32;  enemiesPos[0].y = 7 * 32;
		enemiesPos[1].x = 11 * 32;  enemiesPos[1].y = 5 * 32;
		enemiesPos[2].x = 15 * 32;  enemiesPos[2].y = 4 * 32;
		enemiesPos[3].x = 11 * 32;  enemiesPos[3].y = 11 * 32;
		enemiesPos[4].x = 23 * 32;  enemiesPos[4].y = 9 * 32;
		enemiesPos[5].x = 10 * 32;  enemiesPos[5].y = 1 * 32;
		enemiesPos[6].x = 7 * 32;  enemiesPos[6].y = 15 * 32;
		enemiesPos[7].x = 22 * 32;  enemiesPos[7].y = 18 * 32;
		enemiesPos[8].x = 1 * 32;  enemiesPos[8].y = 11 * 32;
		enemiesPos[9].x = 21 * 32;  enemiesPos[9].y = 9 * 32;

		pickupsPos[0].x = 7*32;  pickupsPos[0].y = 1*32;
		pickupsPos[1].x = 5*32;  pickupsPos[1].y = 11*32;
		pickupsPos[2].x = 21*32;  pickupsPos[2].y = 5*32;
		pickupsPos[3].x = 11*32;  pickupsPos[3].y = 13*32;

		exitDoorPos.x = 19*32;  exitDoorPos.y = 7*32;
	}
	if (Level::level == 3)
	{
		enemiesPos[0].x = 3 * 32;  enemiesPos[0].y = 13 * 32;
		enemiesPos[1].x = 6 * 32;  enemiesPos[1].y = 11 * 32;
		enemiesPos[2].x = 14 * 32;  enemiesPos[2].y = 14 * 32;
		enemiesPos[3].x = 5 * 32;  enemiesPos[3].y = 5 * 32;
		enemiesPos[4].x = 21 * 32;  enemiesPos[4].y = 8 * 32;
		enemiesPos[5].x = 15 * 32;  enemiesPos[5].y = 15 * 32;
		enemiesPos[6].x = 5 * 32;  enemiesPos[6].y = 8 * 32;
		enemiesPos[7].x = 17 * 32;  enemiesPos[7].y = 16 * 32;
		enemiesPos[8].x = 13 * 32;  enemiesPos[8].y = 4 * 32;
		enemiesPos[9].x = 20 * 32;  enemiesPos[9].y = 3 * 32;

		pickupsPos[0].x = 5*32;  pickupsPos[0].y = 11*32;
		pickupsPos[1].x = 9*32;  pickupsPos[1].y = 14*32;
		pickupsPos[2].x = 17*32;  pickupsPos[2].y = 5*32;
		pickupsPos[3].x = 5*32;  pickupsPos[3].y = 15*32;

		exitDoorPos.x = 12*32;  exitDoorPos.y = 10*32;
	}
}


Game::Game()
{
	Game::dim = 0;
	switch (Level::level)
	{
	case 1:
		Game::nrEnemies = 4;
		Game::nrPickups = 2;
		break;
	case 2:
		Game::nrEnemies = 8;
		Game::nrPickups = 3;
		break;
	case 3:
		Game::nrEnemies = 10;
		Game::nrPickups = 4;
		break;
	default:
		break;
	}

	setPositions();
}

Game::~Game()
{
	delete player;
	for (int i = 0; i < Game::dim; i++)
		delete Game::collidingBlocks[i];
	for (int i = 0; i < 10; i++) //stergem tot vectorul de inamici, nu doar nrEnemies
		delete Game::enemies[i];
	delete Game::bomb;
	delete map;
	delete Game::exitDoor;
	for (int i = 0; i < 4; i++)
		delete Game::pickups[i];
	Game::dim = 0;
}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)  //returneaza -1 in caz de eroare si 0 daca merge ok
	{
		std::cout << "Subsystems Initialised ..." << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			std::cout << "Window created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //parameters are renderer, red, green, blue, opacity
			std::cout << "Renderer created!" << std::endl;
		}

		isRunning = true;
	}
	else
	{
		isRunning = false;
	}

	map = new Map();

	player = new Player("assets/spritesheet_Bomberman.png", 1.6, true, 96, 96, 16, 16);  //initializam obiectele (in fct init)
	player->init();
	Game::enemies[0] = new Enemy("assets/spritesheet_Bomberman.png", 2, true, 1, true, (int)enemiesPos[0].x, (int)enemiesPos[0].y, 16, 16);
	Game::enemies[1] = new Enemy("assets/spritesheet_Bomberman.png", 2, true, 2, false, (int)enemiesPos[1].x, (int)enemiesPos[1].y, 16, 16);
	Game::enemies[2] = new Enemy("assets/spritesheet_Bomberman.png", 2, true, 3, true, (int)enemiesPos[2].x, (int)enemiesPos[2].y, 16, 16);
	Game::enemies[3] = new Enemy("assets/spritesheet_Bomberman.png", 2, true, 1, false, (int)enemiesPos[3].x, (int)enemiesPos[3].y, 16, 16);
	Game::enemies[4] = new Enemy("assets/spritesheet_Bomberman.png", 2, true, 2, true, (int)enemiesPos[4].x, (int)enemiesPos[4].y, 16, 16);
	Game::enemies[5] = new Enemy("assets/spritesheet_Bomberman.png", 2, true, 3, false, (int)enemiesPos[5].x, (int)enemiesPos[5].y, 16, 16);
	Game::enemies[6] = new Enemy("assets/spritesheet_Bomberman.png", 2, true, 1, true, (int)enemiesPos[6].x, (int)enemiesPos[6].y, 16, 16);
	Game::enemies[7] = new Enemy("assets/spritesheet_Bomberman.png", 2, true, 2, false, (int)enemiesPos[7].x, (int)enemiesPos[7].y, 16, 16);
	Game::enemies[8] = new Enemy("assets/spritesheet_Bomberman.png", 2, true, 3, true, (int)enemiesPos[8].x, (int)enemiesPos[8].y, 16, 16);
	Game::enemies[9] = new Enemy("assets/spritesheet_Bomberman.png", 2, true, 3, false, (int)enemiesPos[9].x, (int)enemiesPos[9].y, 16, 16);
	for (int i = 0; i < Game::nrEnemies; i++)
		Game::enemies[i]->init();
	Game::bomb = new Bomb("assets/spritesheet_Bomberman.png", 480, 480);
	map->PreparingSprites();
	for (int i=0;i<Game::dim;i++)
		Game::collidingBlocks[i]->init();
	Game::exitDoor = new ExitDoor("assets/spritesheet_Bomberman.png", 1, false, (int)exitDoorPos.x, (int)exitDoorPos.y, 32, 32);
	Game::exitDoor->init();
	Game::pickups[0] = new PickupRange("assets/spritesheet_Bomberman.png", 2, false, (int)pickupsPos[0].x, (int)pickupsPos[0].y, 16, 16);
	Game::pickups[1] = new PickupSpeed("assets/spritesheet_Bomberman.png", 2, false, (int)pickupsPos[1].x, (int)pickupsPos[1].y, 16, 16);
	Game::pickups[2] = new PickupRange("assets/spritesheet_Bomberman.png", 2, false, (int)pickupsPos[2].x, (int)pickupsPos[2].y, 16, 16);
	Game::pickups[3] = new PickupSpeed("assets/spritesheet_Bomberman.png", 2, false, (int)pickupsPos[3].x, (int)pickupsPos[3].y, 16, 16);
	for (int i = 0; i < Game::nrPickups; i++)
		Game::pickups[i]->init();
}

void Game::handleEvents()
{
	SDL_PollEvent(&event);
	
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update()
{
	player->update();
	if (player->isDead == true)
	{
		isRunning = false;
		std::cout << "Game OVER!!!\n";
	}

	if (Game::bomb->bombActive == false && Game::bomb->explosionActive == false) //daca bomba sau explozia sunt pe ecran, nu ii actualizam pozitia
	{
		Game::bomb->bombPositionUpdate(player->destRect);
	}
	if(player->isDead == false && player->startDeathAnimation == false) //nu putem pune bombe daca playerul e pe moarte sau a murit
		Game::bomb->KeyboardControllerBomb();
	
	updateEnemies(); //functie globala

	Game::exitDoor->update();

	if (player->collidedWithOpenDoor == true)
		isRunning = false;
}

void Game::render()
{
	SDL_RenderClear(renderer);   //elibereaza rendererul pt a putea fi incarcat cu obiectele updatate
	map->DrawMap();
	Game::exitDoor->draw();
	for (int i = 0; i < Game::nrPickups; i++)
		Game::pickups[i]->draw();
	player->draw();

	for (int i = 0; i < Game::nrEnemies; i++)
		Game::enemies[i]->draw();

	for (int i = 0; i<Game::dim; i++)
	{
		Game::collidingBlocks[i]->draw();
	}

	if (Game::bomb->spacebarPressed == true) //aceste 2 ifuri trebuie dupa desenarea blocurilor de coliziune pt a se putea vedea focul pe blocul care urmeaza a fi distrus.
	{
		Game::bomb->bombAnimation();
		Game::bomb->eraseBomb(2);
	}
	if (Game::bomb->explosionActive == true)
	{
		Game::bomb->explosion(map);
	}

	SDL_RenderPresent(renderer); //afisam pe ecran modificarile
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned!" << std::endl;
}

