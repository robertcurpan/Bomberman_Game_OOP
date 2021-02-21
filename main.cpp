#include "SDL.h"
#include "Game.h"
#include "Level.h"

Game *game = nullptr; //in loc de declararea globala a acestui obiect, am fi putut crea un membru static in clasa Game (el va exista intr-un singur exemplar pt toate instantele).
int Level::level;

int main(int argc, char *argv[])
{
	std::cout << "Dati nivelul: ";
	std::cin >> Level::level;

	while (Level::level != 0)
	{
		const int FPS = 60;
		const int frameDelay = 1000 / FPS;

		Uint32 frameStart;
		int frameTime;

		game = new Game(); //apel constructor implicit
		game->init("MyGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false); //last argument is fullscreen

		while (game->running())
		{
			frameStart = SDL_GetTicks();

			game->handleEvents();
			game->update();
			game->render();

			frameTime = SDL_GetTicks() - frameStart;

			if (frameDelay > frameTime)
				SDL_Delay(frameDelay - frameTime);
		}

		game->clean();
		delete game;

		std::cout << "Dati nivelul: ";
		std::cin >> Level::level;
	}
	std::cout << "Game Quit.\n";
	return 0;
}