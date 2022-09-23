#include "Renderer.h"
#include <Windows.h>
#undef DrawText

Renderer::Renderer()
{
	HWND windowHandle = GetConsoleWindow();
	ShowWindow(windowHandle, SW_HIDE);
		
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
	
	if (TTF_Init() < 0)
	{
		SDL_Log("%s", TTF_GetError());
		return;
	}
}

void Renderer::DrawCell(MoveType i_cellType, int i_pixelX, int i_pixelY)
{
	SDL_Rect newRect;
	newRect.w = TABLE_CELL_SIZE - 1;
	newRect.h = newRect.w;
	newRect.x = i_pixelX + 1;
	newRect.y = i_pixelY + 1;

	if (i_cellType == MoveType::X)
	{
		SDL_RenderCopy(m_sdlRenderer, m_loadedTextures["X"], NULL, &newRect);
	}
	else if (i_cellType == MoveType::O)
	{
		SDL_RenderCopy(m_sdlRenderer, m_loadedTextures["O"], NULL, &newRect);
	}
}

void Renderer::DrawText(std::string i_text, int i_size, int i_X, int i_Y, int i_H, int i_W)
{
	TTF_Font* font = TTF_OpenFont("./Data/font.TTF", i_size);
	SDL_Color White = { 255, 255, 255 };
	const char* renderText = i_text.c_str();
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, renderText, White);
	SDL_Texture* message = SDL_CreateTextureFromSurface(m_sdlRenderer, surfaceMessage);
	SDL_Rect Message_rect;
	Message_rect.x = i_X;
	Message_rect.y = i_Y;
	Message_rect.w = i_W;
	Message_rect.h = i_H;
	SDL_RenderCopy(m_sdlRenderer, message, NULL, &Message_rect);
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(message);
}

void Renderer::DrawGameOverPopup()
{
	SDL_Rect newRect;
	newRect.w = GAME_OVER_POPUP_WIDTH;
	newRect.h = GAME_OVER_POPUP_HEIGHT;
	newRect.x = GAME_OVER_POPUP_X;
	newRect.y = GAME_OVER_POPUP_Y;

	SDL_SetRenderDrawColor(m_sdlRenderer, 0, 0, 0, 255);

	SDL_RenderFillRect(m_sdlRenderer, &newRect);

	DrawText("GAME OVER", TEXT_GAME_OVER_SIZE, TEXT_GAME_OVER_X, TEXT_GAME_OVER_Y, TEXT_GAME_OVER_HEIGHT, TEXT_GAME_OVER_WIDTH);
	
	DrawText("PLAY AGAIN?", TEXT_PLAY_AGAIN_SIZE, TEXT_PLAY_AGAIN_X, TEXT_PLAY_AGAIN_Y, TEXT_PLAY_AGAIN_HEIGHT, TEXT_PLAY_AGAIN_WIDTH);

	newRect.w = YES_BUTTON_WIDTH;
	newRect.h = YES_BUTTON_HEIGHT;
	newRect.x = YES_BUTTON_X;
	newRect.y = YES_BUTTON_Y;
	SDL_RenderCopy(m_sdlRenderer, m_loadedTextures["YES"], NULL, &newRect);

	newRect.w = NO_BUTTON_WIDTH;
	newRect.h = NO_BUTTON_HEIGHT;
	newRect.x = NO_BUTTON_X;
	newRect.y = NO_BUTTON_Y;
	SDL_RenderCopy(m_sdlRenderer, m_loadedTextures["NO"], NULL, &newRect);
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
	SDL_DestroyRenderer(m_sdlRenderer);

	//cleans up all initialized subsystems

	SDL_DestroyWindow(m_window);

	//Destroy a renderer
	
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
