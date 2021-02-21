#pragma once

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "Vector2D.h"

class SpriteComponent;
class Enemy;
class Bomb;

class Game
{
	int cnt = 0;
	bool isRunning;
	SDL_Window *window;

	Vector2D enemiesPos[10];
	Vector2D pickupsPos[4];
	Vector2D exitDoorPos;
public:
	Game(); 
	~Game(); 
	
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);  //initialize SDL properly
	void handleEvents();  
	void update();   //here we implement the game logic
	void render();  //we display on the screen everything that has changed - positions, colors etc. (from user input etc.)
	void clean();   //we clean everything when the game is closed

	bool running() { return isRunning; }  //inline function -> returns 1 if the game is running correctly

	void setPositions();

	static SDL_Renderer *renderer; //il transmitem destul de des ca parametru si e mai usor daca acesta exista intr-un singur exemplar peste tot, in loc sa se transmita mai multe copii
	static SDL_Event event;
	static SpriteComponent *collidingBlocks[500];
	static int dim;
	static Enemy *enemies[10];
	static int nrEnemies;
	static Bomb *bomb;
	static SpriteComponent *exitDoor;
	static SpriteComponent *pickups[4];
	static int nrPickups;
};
