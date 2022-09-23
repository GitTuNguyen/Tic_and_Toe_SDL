#pragma once
#include "Board.h"
#include "Renderer.h"
#include "InputManager.h"
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
	Board* m_board;
	Renderer* m_renderer;
	InputManager* m_inputManager;
	MoveType m_currentMoveType;
	bool m_isPlayerWantExit;
};