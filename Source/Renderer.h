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
	void DrawTable();
	void DrawText(std::string i_text, int i_size, int i_X, int i_Y, int i_H, int i_W);
	void DrawGameOverPopup();
	void PostFrame();
	void CleanUp();
	void LoadTexture(string i_imageName);
	void PreRendering();
private:
	SDL_Window* m_window = NULL;
	SDL_Renderer* m_sdlRenderer = NULL;
	TTF_Font* m_mainFont = NULL;
	map<string, SDL_Texture*> m_loadedTextures;
};

