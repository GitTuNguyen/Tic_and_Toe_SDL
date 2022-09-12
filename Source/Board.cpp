#include "Board.h"

Board::Board()
{
	Reset();
}

CellType** Board::getBoardData()
{
	return m_boardData;
}
void Board::Reset()
{
	m_boardData = (CellType**)malloc(sizeof(CellType*) * TABLE_ROW);
	for (int i = 0; i < TABLE_ROW; i++) {
		m_boardData[i] = (CellType*)malloc(sizeof(CellType) * TABLE_COL);
	}
	for (int i = 0; i < TABLE_ROW ; i++)
	{
		for (int j = 0; j < TABLE_COL; j++)
		{
			m_boardData[i][j] = CellType::UNDEFINED;
		}
		
	}
	m_movesPlayed = 0;
	m_gameResult = GameResult::NONE;
}

GameResult  Board::GetGameResult()
{
	return m_gameResult;
}
void Board::UpdateGameResult(int i_X, int i_Y, CellType i_moveType)
{
	bool isLastPlayerWin = false;
	size_t count_1 = 1;
	size_t count_2 = 1;
	size_t count_3 = 1;
	size_t count_4 = 1;
	for (int i = 1; i <= 4 && i_Y + i < TABLE_COL; i++)
	{
		if (m_boardData[i_X][i_Y + i] == m_boardData[i_X][i_Y + i - 1])
		{
			count_1++;
		}
		else break;
	}
	for (int i = 1; i <= 4 && i_Y - i >= 0; i++)
	{
		if (m_boardData[i_X][i_Y - i] == m_boardData[i_X][i_Y - i + 1])
		{
			count_1++;
		}
		else break;
	}
	for (int i = 1; i <= 4 && i_X + i < TABLE_ROW; i++)
	{
		if (m_boardData[i_X + i][i_Y] == m_boardData[i_X + i - 1][i_Y])
		{
			count_2++;
		}
		else break;
	}
	for (int i = 1; i_X - i >= 0 && i <= 4; i++)
	{
		if (m_boardData[i_X - i][i_Y] == m_boardData[i_X - i + 1][i_Y])
		{
			count_2++;
		}
		else break;
	}
	for (int i = 1; i <= 4 && i_X + i < TABLE_ROW && i_Y + i < TABLE_COL ; i++)
	{
		if (m_boardData[i_X + i][i_Y + i] == m_boardData[i_X + i - 1][i_Y + i - 1])
		{
			count_3++;
		}
		else break;
	}
	for (int i = 1; i <= 4 && i_X - i >= 0 && i_Y - i >=0 ; i++)
	{
		if (m_boardData[i_X - i][i_Y - i] == m_boardData[i_X - i + 1][i_Y - i + 1])
		{
			count_3++;
		}
		else break;
	}
	for (int i = 1; i <= 4 && i_X - i >= 0 && i_Y + i < TABLE_COL; i++)
	{
		if (m_boardData[i_X - i][i_Y + i] == m_boardData[i_X - i + 1][i_Y + i - 1])
		{
			count_4++;
		}
		else break;
	}
	for (int i = 1; i <= 4 && i_X + i < TABLE_ROW && i_Y - i >= 0; i++)
	{
		if (m_boardData[i_X + i][i_Y - i] == m_boardData[i_X + i - 1][i_Y - i + 1])
		{
			count_4++;
		}
		else break;
	}
	if (count_1 >= 5 || count_2 >= 5 || count_3 >= 5 || count_4 >= 5)
	{
		isLastPlayerWin = true;
	}
	if (isLastPlayerWin)
	{
		if (i_moveType == CellType::X)
		{
			m_gameResult = GameResult::X_WIN;
		}
		else {
			m_gameResult = GameResult::O_WIN;
		}
	}
	else if (m_movesPlayed == TABLE_SIZE)
	{
		m_gameResult = GameResult::DRAW;
	}
	else
	{
		m_gameResult = GameResult::NONE;
	}
}
void Board::Update(int i_X, int i_Y, CellType i_moveType)
{
	m_boardData[i_X][i_Y] = i_moveType;
	++m_movesPlayed;
	UpdateGameResult(i_X, i_Y, i_moveType);
}
bool Board::ValidateMove(int i_X, int i_Y)
{
	CellType valueCurrentPlay = m_boardData[i_X][i_Y];
	if (valueCurrentPlay == CellType::X || valueCurrentPlay == CellType::O)
	{
		return false;
	}
	return true;
}
