#pragma once
#include "Board.h"
#include "Renderer.h"
#include <vector>

class Game {
public:
	Game();
	void Update();
	~Game();
private:
	void DrawBoad();
	void DrawGameOverScreen();
	void CreateNewMatch();
	void UpdateMove(int i_X, int i_Y);
	void Rematch(int i_mouse_X, int i_mouse_Y);
	Board* m_board;
	Renderer* m_renderer;
	MoveType m_currentMoveType;
	bool m_isPlayerWantExit;
	SDL_Event mainEvent;
};