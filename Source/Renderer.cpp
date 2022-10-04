#include "Renderer.h"
#ifndef __ANDROID__
#include <Windows.h>
#endif
#undef DrawText

Renderer::Renderer()
{
#ifndef __ANDROID__
	HWND windowHandle = GetConsoleWindow();
	ShowWindow(windowHandle, SW_HIDE);
#endif
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("Unable to initialize SDL %s\n", SDL_GetError());
		return;
	}

	//Create window
	SDL_DisplayMode MD;
	SDL_GetCurrentDisplayMode(0, &MD);
	m_windowHeight = MD.h;
	m_windowWidth = MD.w;
	if (m_windowHeight > m_windowWidth)
	{
		m_boardCollum = TABLE_WIDTH;
		m_cellSize = m_windowWidth / TABLE_WIDTH;
		m_boardRow = m_windowHeight / m_cellSize;
	} else {
		m_boardRow = TABLE_WIDTH;
		m_cellSize = m_windowHeight / TABLE_WIDTH;
		m_boardCollum = m_windowWidth / m_cellSize;
	}
	m_window = SDL_CreateWindow("Tic And Toe - SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_windowWidth , m_windowHeight, SDL_WINDOW_FULLSCREEN);
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
	//SDL_RenderSetLogicalSize(m_sdlRenderer, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (TTF_Init() < 0)
	{
		SDL_Log("%s", TTF_GetError());
		return;
	}

	m_mainFont = TTF_OpenFont("Data/font.ttf", TEXT_SIZE);
	SDL_SetHintWithPriority("SDL_ANDROID_TRAP_BACK_BUTTON", "0",SDL_HINT_OVERRIDE);
}

void Renderer::DrawCell(MoveType i_cellType, int i_pixelX, int i_pixelY)
{
	SDL_Rect newRect;
	newRect.w = m_cellSize - 1;
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
	SDL_Color whiteColor = { 255, 255, 255 };
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(m_mainFont, i_text.c_str(), whiteColor);
	SDL_Texture* message = SDL_CreateTextureFromSurface(m_sdlRenderer, surfaceMessage);
	SDL_Rect messageRect;
	messageRect.x = i_X;
	messageRect.y = i_Y;
	messageRect.w = i_W;
	messageRect.h = i_H;
	SDL_RenderCopy(m_sdlRenderer, message, NULL, &messageRect);
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(message);
}

void Renderer::DrawGameOverPopup()
{
	SDL_Rect newRect;
	newRect.w = GAME_OVER_POPUP_WIDTH * m_cellSize;
	newRect.h = GAME_OVER_POPUP_HEIGHT * m_cellSize;
	newRect.x = (m_windowWidth - newRect.w) / 2;
	newRect.y = (m_windowHeight - newRect.h) / 2;

	SDL_SetRenderDrawColor(m_sdlRenderer, 0, 0, 0, 255);

	SDL_RenderFillRect(m_sdlRenderer, &newRect);

	DrawText("GAME OVER", TEXT_SIZE, newRect.x + ((GAME_OVER_POPUP_WIDTH - TEXT_GAME_OVER_WIDTH) * m_cellSize) / 2, newRect.y + m_cellSize/2, TEXT_GAME_OVER_HEIGHT * m_cellSize, TEXT_GAME_OVER_WIDTH * m_cellSize);
	
	DrawText("PLAY AGAIN?", TEXT_SIZE, newRect.x + ((GAME_OVER_POPUP_WIDTH - TEXT_PLAY_AGAIN_WIDTH) * m_cellSize) / 2, newRect.y + m_cellSize * 2 + m_cellSize/2, TEXT_PLAY_AGAIN_HEIGHT * m_cellSize, TEXT_PLAY_AGAIN_WIDTH * m_cellSize);

	newRect.x = newRect.x + m_cellSize * 2;
	newRect.y = newRect.y + m_cellSize * 3 + m_cellSize / 2;
	newRect.w = YES_BUTTON_WIDTH * m_cellSize;
	newRect.h = YES_BUTTON_HEIGHT * m_cellSize;
	

	SDL_RenderCopy(m_sdlRenderer, m_loadedTextures["YES"], NULL, &newRect);

	newRect.x = newRect.x + m_cellSize * 2;
	newRect.y = newRect.y;
	newRect.w = NO_BUTTON_WIDTH * m_cellSize;
	newRect.h = NO_BUTTON_HEIGHT * m_cellSize;
	
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
	for (int i = 0; i <= m_boardCollum; i++)
	{
		int lineXPos = i * m_cellSize;
		if (i == m_boardCollum)
		{
			--lineXPos;
		}
		startPoint = { lineXPos, 0 };
		endPoint = { lineXPos, m_windowHeight};
		SDL_RenderDrawLine(m_sdlRenderer, startPoint.x, startPoint.y, endPoint.x, endPoint.y);
	}
	for (int i = 0; i <= m_boardRow; i++)
	{
		int lineYPos = i * m_cellSize;
		if (i == m_boardRow)
		{
			--lineYPos;
		}
		startPoint = { 0, lineYPos };
		endPoint = { m_windowWidth, lineYPos };
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
	string str = "Data/" + i_ImageName + ".bmp";
	tempSurface = SDL_LoadBMP(str.c_str());	
	texture = SDL_CreateTextureFromSurface(m_sdlRenderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	m_loadedTextures.insert(pair<string, SDL_Texture*>(i_ImageName, texture));
}

int Renderer::GetWindowHeight()
{
	return m_windowHeight;
}

int Renderer::GetWindowWidth()
{
	return m_windowWidth;
}

int Renderer::GetBoardCollum()
{
	return m_boardCollum;
}

int Renderer::GetBoardRow()
{
	return m_boardRow;
}

int Renderer::GetCellSize()
{
	return m_cellSize;
}
