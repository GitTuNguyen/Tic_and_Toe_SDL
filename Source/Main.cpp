#define SDL_MAIN_HANDLED
#include "Game.h"

void main()
{
	Game* game = new Game();

	game->Update();

	getchar();
}