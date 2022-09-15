#include "Renderer.h"

Renderer::Renderer()
{
	
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("Unable to initialize SDL %s\n", SDL_GetError());
		return;
	}

	//Create window
	m_window = SDL_CreateWindow("Tic And Toe - SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (m_window == NULL)
	{
		printf("Could not create window %s", SDL_GetError());
		return;
	}


	//create a renderer
	m_sdlRenderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	if (m_sdlRenderer == NULL)
	{
		printf("Could not create render %s", SDL_GetError());
		return;
	}
		
}

void Renderer::DrawCell(CellType i_cellType, int i_pixelX, int i_pixelY)
{
	SDL_Rect newRect;
	newRect.w = TABLE_CELL_SIZE - 1;
	newRect.h = newRect.w;
	newRect.x = i_pixelX + 1;
	newRect.y = i_pixelY + 1;

	if (i_cellType == CellType::X)
	{
		SDL_RenderCopy(m_sdlRenderer, m_loadedTextures["X"], NULL, &newRect);
	}
	else if (i_cellType == CellType::O)
	{
		SDL_RenderCopy(m_sdlRenderer, m_loadedTextures["O"], NULL, &newRect);
	}
}

void Renderer::PreRendering()
{
	SDL_SetRenderDrawColor(m_sdlRenderer, 0, 0, 0, 255);
	SDL_RenderClear(m_sdlRenderer);
}
void Renderer::DrawTable()
{
	SDL_SetRenderDrawColor(m_sdlRenderer, 255, 255, 255, 255);
	SDL_Point startPoint = { 0, 0 };
	SDL_Point endPoint = { 0, 0 };
	for (int i = 0; i < WINDOW_WIDTH; i += TABLE_CELL_SIZE)
	{
		startPoint = { i, 0 };
		endPoint = { i, WINDOW_HEIGHT };
		SDL_RenderDrawLine(m_sdlRenderer, startPoint.x, startPoint.y, endPoint.x, endPoint.y);
	}
	for (int i = 0; i < WINDOW_HEIGHT; i += TABLE_CELL_SIZE)
	{
		startPoint = { 0, i };
		endPoint = { WINDOW_WIDTH, i };
		SDL_RenderDrawLine(m_sdlRenderer, startPoint.x, startPoint.y, endPoint.x, endPoint.y);
	}
}

void Renderer::PostFrame()
{
	SDL_RenderPresent(m_sdlRenderer);
	SDL_Delay(16);
}

void Renderer::CleanUp()
{

	SDL_DestroyWindow(m_window);

	//Destroy a renderer
	SDL_DestroyRenderer(m_sdlRenderer);

	//cleans up all initialized subsystems
	SDL_Quit();
}

void Renderer::LoadTexture(string i_ImageName)
{
	SDL_Surface* tempSurface = NULL;
	SDL_Texture* texture = NULL;
	string str = "./Data/" + i_ImageName + ".bmp";
	tempSurface = SDL_LoadBMP(str.c_str());	
	texture = SDL_CreateTextureFromSurface(m_sdlRenderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	m_loadedTextures.insert(pair<string, SDL_Texture*>(i_ImageName, texture));
}
