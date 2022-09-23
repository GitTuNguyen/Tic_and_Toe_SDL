#pragma once
#include "GameDefinitions.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

enum GameResult
{
	NONE,
	X_WIN,
	O_WIN,
	DRAW
};

enum MoveType {
	UNDEFINED,
	X,
	O
};

class Board {	
private:
	MoveType** m_boardData;
	GameResult m_gameResult;
	size_t m_movesPlayed;
public:
	Board();
	void Reset();
	GameResult GetGameResult();
	MoveType** getBoardData();
	void Update(int i_X, int i_Y, MoveType i_moveType);
	void UpdateGameResult(int i_X, int i_Y, MoveType i_moveType);
	bool ValidateMove(int i_X, int i_Y);
};