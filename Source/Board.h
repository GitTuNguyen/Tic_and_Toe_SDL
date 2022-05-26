#pragma once
#include "GameConst.h"
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
enum CellType {
	UNDEFINED,
	X,
	O
};
#define TABLE_ROW 10
#define TABLE_COL 10
#define TABLE_SIZE (TABLE_ROW * TABLE_COL)
class Board {	
private:
	CellType** m_boardData;
	GameResult m_gameResult;
	size_t m_movesPlayed;
public:
	Board();
	void Reset();
	GameResult GetGameResult();
	CellType** getBoardData();
	//void Render();
	void Update(int i_X, int i_Y, CellType i_moveType);
	void UpdateGameResult(int i_X, int i_Y, CellType i_moveType);
	bool ValidateMove(int i_X, int i_Y);
};