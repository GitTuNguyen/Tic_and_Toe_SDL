#pragma once
#include "Board.h"
#include <SDL.h>
#define windows_size 400
class Game {
public:
	Game();
	void Update();
private:
	void drawBoad();
	void CreateNewMatch();
	void UpdateMove(int i_X, int i_Y);
	//void RenderGameOver();
	void Rematch();
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Surface* tempSurface = NULL;
	SDL_Texture* texture_X = NULL;
	SDL_Texture* texture_O = NULL;
	SDL_Event mainEvent;
	SDL_Rect sourceRect;
	SDL_Rect desRect;
	Board* m_board;
	CellType m_currentMoveType;
	bool m_isPlayerWantExit;
};