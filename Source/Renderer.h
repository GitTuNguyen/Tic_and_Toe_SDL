#pragma once

#include <SDL.h>
#include "Board.h"
#include <map>
#include <string>
class Renderer
{
public:
	Renderer();
	void DrawCell(CellType i_cellType, int i_pixelX, int i_pixelY);
	void DrawTable();
	void PostFrame();
	void CleanUp();
	void LoadTexture(string i_imageName);
	void PreRendering();
private:
	SDL_Window* m_window = NULL;
	SDL_Renderer* m_sdlRenderer = NULL;
	map<string, SDL_Texture*> m_loadedTextures;
};

