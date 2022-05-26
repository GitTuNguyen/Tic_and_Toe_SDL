/*
* #include <stdio.h>
#include <SDL.h>

#undef main
#define windows_size 400
int main()
{
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Surface* tempSurface = NULL;
	SDL_Texture* texture_X = NULL;
	SDL_Texture* texture_O = NULL;
	SDL_Event mainEvent;
	SDL_Rect sourceRect;
	SDL_Rect desRect;
	bool isRunning = true;

	//initializes  the subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("Unable to initialize SDL %s\n", SDL_GetError());
		return -1;
	}

	//Create window
	window = SDL_CreateWindow("Stdio.vn - SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windows_size, windows_size, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("Could not create window %s", SDL_GetError());
		return -1;
	}


	//create a renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		printf("Could not create render %s", SDL_GetError());
		return -1;
	}

	//create a tempSurface
	tempSurface = SDL_LoadBMP("X.bmp");
	//create a texutre from surface
	texture_X = SDL_CreateTextureFromSurface(renderer, tempSurface);
	//free surface
	SDL_FreeSurface(tempSurface);
	tempSurface = SDL_LoadBMP("O.bmp");
	//create a texutre from surface
	texture_O = SDL_CreateTextureFromSurface(renderer, tempSurface);
	//free surface
	SDL_FreeSurface(tempSurface);


	SDL_QueryTexture(texture, NULL, NULL, &sourceRect.w, &sourceRect.h);

	sourceRect.x = 0;
	sourceRect.y = 0;
	//sourceRect.w = sourceRect.w / 2;
	//sourceRect.h = sourceRect.h / 2;

	desRect.x = 200;
	desRect.y = 200;
	desRect.w = sourceRect.w;
	desRect.h = sourceRect.h;
	
	//main loop
	while (isRunning)
	{
		// clear the window to black
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_Point startPoint = { 0, 0 };
		SDL_Point endPoint = { 0, 0 };
		for (int i = 0; i < 800; i += 40)
		{
			startPoint = { i, 0 };
			endPoint = { i, 640 };
			SDL_RenderDrawLine(renderer, startPoint.x, startPoint.y, endPoint.x, endPoint.y);
		}
		for (int i = 0; i < 640; i += 40)
		{
			startPoint = { 0, i };
			endPoint = { 800, i };
			SDL_RenderDrawLine(renderer, startPoint.x, startPoint.y, endPoint.x, endPoint.y);
		}

		//main event
		SDL_Rect newRect;
		newRect.w = sourceRect.w;
		newRect.h = sourceRect.h;
		while (SDL_PollEvent(&mainEvent))
		{
			switch (mainEvent.type)
			{
				//User - requested quit
				case SDL_QUIT:
				{
					isRunning = false;
					break;
				}
				case SDL_MOUSEBUTTONDOWN:
				{
					newRect.x = mainEvent.motion.x;
					newRect.y = mainEvent.motion.y;
					startPoint = endPoint;
					endPoint = { mainEvent.motion.x , mainEvent.motion.y };
				}
				default:
				{
					break;
				}
			}
		}

		// copy a portion of the texture to the current rendering target.
		SDL_RenderCopy(renderer, texture, NULL, &newRect);
		//SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		//SDL_RenderDrawLine(renderer, startPoint.x, startPoint.y, endPoint.x, endPoint.y);
		//draw to the screen
		SDL_RenderPresent(renderer);
	}

	//Destroy a window.
	SDL_DestroyWindow(window);

	//Destroy a renderer
	SDL_DestroyRenderer(renderer);

	//cleans up all initialized subsystems
	SDL_Quit();
	return 0;
}
*/