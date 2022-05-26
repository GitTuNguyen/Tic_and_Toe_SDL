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
	for (int i = 0; i < TABLE_COL; i++)
	{
		for (int j = 0; j < TABLE_ROW; j++)
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

/*
* void Board::Render()
{
	const char* gameName1 = "\t\t\t      GAME---TIC---TAC---TOE \n";
	const char* gameName2 = "\t\t\t\t FOR\t 2    Player\n\n";
	const char* guideGame = "\t\t PLAYER - 1 [X] \t - \tPLAYER - 2 [O]\n\n";
	cout << gameName1 << gameName2 << guideGame;
	cout << k_padding << k_padding << "   +---+---+---+\n";
	cout << k_padding << k_padding << "   | " << m_boardData[0] << " | " << m_boardData[1] << " | " << m_boardData[2] << " |\n";
	cout << k_padding << k_padding << "   +---+---+---+\n";
	cout << k_padding << k_padding << "   | " << m_boardData[3] << " | " << m_boardData[4] << " | " << m_boardData[5] << " |\n";
	cout << k_padding << k_padding << "   +---+---+---+\n";
	cout << k_padding << k_padding << "   | " << m_boardData[6] << " | " << m_boardData[7] << " | " << m_boardData[8] << " |\n";
	cout << k_padding << k_padding << "   +---+---+---+\n\n";
}
*/
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
	for (int i = 1; i <= 4 && i_X + i < TABLE_COL && i_Y + i < TABLE_COL ; i++)
	{
		if (m_boardData[i_X + i][i_Y + i] == m_boardData[i_X + i - 1][i_Y + i - 1])
		{
			count_2++;
		}
		else break;
	}
	for (int i = 1; i <= 4 && i_X - i >= 0 && i_Y - i >=0 ; i++)
	{
		if (m_boardData[i_X - i][i_Y - i] == m_boardData[i_X - i + 1][i_Y - i + 1])
		{
			count_2++;
		}
		else break;
	}
	for (int i = 1; i <= 4 && i_X - i >= 0 && i_Y + i < TABLE_COL; i++)
	{
		if (m_boardData[i_X - i][i_Y + i] == m_boardData[i_X - i + 1][i_Y + i - 1])
		{
			count_2++;
		}
		else break;
	}
	for (int i = 1; i <= 4 && i_X + i < TABLE_COL && i_Y - i >= 0; i++)
	{
		if (m_boardData[i_X + i][i_Y - i] == m_boardData[i_X + i - 1][i_Y - i + 1])
		{
			count_2++;
		}
		else break;
	}
	if (count_1 == 5 || count_2 == 5 || count_3 == 5 || count_4 == 5)
	{
		isLastPlayerWin = true;
	}
	if (isLastPlayerWin)
	{
		if (i_moveType == 'X')
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
