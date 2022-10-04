#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include "Board.h"
#include <map>
#include <string>

class Renderer
{
public:
	Renderer();
	void DrawCell(MoveType i_cellType, int i_pixelX, int i_pixelY);
	void DrawTable(int i_boardColumn, int i_boardRow);
	void DrawText(std::string i_text, int i_size, int i_X, int i_Y, int i_H, int i_W);
	void DrawGameOverPopup();
	void PostFrame();
	void CleanUp();
	void LoadTexture(string i_imageName);
	void PreRendering();
	int GetWindowHeight();
	int GetWindowWidth();
	int GetCellSize();
private:
	SDL_Window* m_window = NULL;
	SDL_Renderer* m_sdlRenderer = NULL;
	TTF_Font* m_mainFont = NULL;
	int m_windowHeight;
	int m_windowWidth;	
	int m_cellSize;
	map<string, SDL_Texture*> m_loadedTextures;
};

