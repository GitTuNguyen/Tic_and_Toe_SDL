#include "Board.h"

Board::Board( int i_boardCollum, int i_boardRow)
{
	m_boardCollum = i_boardCollum;
	m_boardRow = i_boardRow;
	Reset();
}

MoveType** Board::GetBoardData()
{
	return m_boardData;
}

void Board::Reset()
{
	m_boardData = (MoveType**)malloc(sizeof(MoveType*) * m_boardRow);
	for (int i = 0; i < m_boardRow; i++) {
		m_boardData[i] = (MoveType*)malloc(sizeof(MoveType) * m_boardCollum);
	}
	for (int i = 0; i < m_boardRow ; i++)
	{
		for (int j = 0; j < m_boardCollum; j++)
		{
			m_boardData[i][j] = MoveType::UNDEFINED;
		}
		
	}
	m_movesPlayed = 0;
	m_gameResult = GameResult::NONE;
}

GameResult  Board::GetGameResult()
{
	return m_gameResult;
}

int Board::CountSameMoveByDirection(int i_startCellX, int i_startCellY, Direction i_dir, int maxStep)
{
	int count = 0;
	for (int i = 1; i <= maxStep; i++)
	{
		int nextCellX = i_startCellX + i_dir.x * i;
		int nextCellY = i_startCellY + i_dir.y * i;
		if (nextCellX < 0 || nextCellX >= m_boardRow || nextCellY < 0 || nextCellY >= m_boardCollum)
		{
			break;
		}
		else if (m_boardData[i_startCellX][i_startCellY] == m_boardData[nextCellX][nextCellY])
		{
			count++;
		}
		else {
			break;
		}
	}
	return count;
}

void Board::UpdateGameResult(int i_startCellX, int i_startCellY, MoveType i_moveType)
{
	bool isLastPlayerWin = false;

	std::vector<Direction> directions;
	directions.push_back(Direction(0, 1));
	directions.push_back(Direction(1, 0));
	directions.push_back(Direction(1, -1));
	directions.push_back(Direction(1, 1));

	for (Direction dir : directions)
	{
		Direction oppositeDir = dir * -1;
		int count = CountSameMoveByDirection(i_startCellX, i_startCellY, dir);
		int oppositeCount = CountSameMoveByDirection(i_startCellX, i_startCellY, oppositeDir);
		int finalCount = count + oppositeCount + 1;
		if (finalCount >= 5)
		{
			isLastPlayerWin = true;
			break;
		}
	}

	if (isLastPlayerWin)
	{
		if (i_moveType == MoveType::X)
		{
			m_gameResult = GameResult::X_WIN;
		}
		else {
			m_gameResult = GameResult::O_WIN;
		}
	}
	else if (m_movesPlayed == (m_boardCollum * m_boardRow))
	{
		m_gameResult = GameResult::DRAW;
	}
	else
	{
		m_gameResult = GameResult::NONE;
	}
}

void Board::Update(int i_x, int i_y, MoveType i_moveType)
{
	m_boardData[i_x][i_y] = i_moveType;
	++m_movesPlayed;
	UpdateGameResult(i_x, i_y, i_moveType);
}

bool Board::ValidateMove(int i_x, int i_y)
{
	MoveType valueCurrentPlay = m_boardData[i_x][i_y];
	if (valueCurrentPlay == MoveType::X || valueCurrentPlay == MoveType::O)
	{
		return false;
	}
	return true;
}
