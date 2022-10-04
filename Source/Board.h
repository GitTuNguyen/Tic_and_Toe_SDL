#pragma once
#include "GameDefinitions.h"
#include <iostream>
#include <stdlib.h>
#include <vector>

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

struct Direction {
	int x;
	int y;

	Direction(int i_x, int i_y)
	{
		x = i_x;
		y = i_y;
	}

	Direction operator * (int a) {
		return Direction(x * a, y * a);
	}
};

class Board {
public:
	Board(int i_boardCollum, int i_boardRow);
	void Reset();
	GameResult GetGameResult();
	MoveType** GetBoardData();
	void Update(int i_X, int i_Y, MoveType i_moveType);
	int CountSameMoveByDirection(int startCellX, int startCellY, Direction i_dir, int maxStep = 4);
	void UpdateGameResult(int i_startCellX, int i_startCellY, MoveType i_moveType);
	bool ValidateMove(int i_X, int i_Y);
private:
	MoveType** m_boardData;
	GameResult m_gameResult;
	size_t m_movesPlayed;
	int m_boardCollum;
	int m_boardRow; 
};