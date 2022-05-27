/*player board play*/
#pragma once
#include "Game.h"
#include "Board.h"

Game::Game()
{
	m_board = new Board();
	m_renderer = new Renderer();
	m_currentMoveType = CellType::X;
	m_isPlayerWantExit = false;
	m_renderer->LoadTexture("X");
	m_renderer->LoadTexture("O");
}

void Game::CreateNewMatch()
{
	m_board->Reset();
}
void Game::Rematch()
{
	char inputPlayer;
	cout << "Play again? (Y to play again, another key to quit): ";
	cin >> inputPlayer;
	if (inputPlayer == 'Y' || inputPlayer == 'y')
	{
		CreateNewMatch();
	}
	else {
		m_isPlayerWantExit = true;
	}
}
void Game::DrawBoad()
{

	CellType** boardData = m_board->getBoardData();
	for (int i = 0; i < TABLE_ROW; i++)
	{
		for (int j = 0; j < TABLE_COL; j++)
		{
			m_renderer->DrawCell(boardData[i][j], j * TABLE_CELL_SIZE, i * TABLE_CELL_SIZE);
		}
	}
}
void Game::Update()
{
	while (!m_isPlayerWantExit)
	{
		m_renderer->PreRendering();
		m_renderer->DrawTable();
		GameResult gameResult = m_board->GetGameResult();
		if (gameResult == GameResult::NONE)
		{
			SDL_Rect newRect;
			while (SDL_PollEvent(&mainEvent))
			{
				switch (mainEvent.type)
				{
				case SDL_QUIT:
				{
					m_isPlayerWantExit = true;
					break;
				}
				case SDL_MOUSEBUTTONDOWN:
				{
					newRect.x = mainEvent.motion.x;
					newRect.y = mainEvent.motion.y;
					if (newRect.x % TABLE_CELL_SIZE != 0 && newRect.y % TABLE_CELL_SIZE != 0 && m_board->ValidateMove(floor(newRect.y / TABLE_CELL_SIZE), floor(newRect.x / TABLE_CELL_SIZE)))
					{
						UpdateMove(floor(newRect.y / TABLE_CELL_SIZE), floor(newRect.x / TABLE_CELL_SIZE));
					}
				}
				default:
				{
					break;
				}
				}
			}
			DrawBoad();
		}
		else {
			Rematch();
		}
		m_renderer->PostFrame();
	}
	m_renderer->CleanUp();
}
void Game::UpdateMove(int i_X, int i_Y)
{
	m_board->Update(i_X, i_Y, m_currentMoveType);
	m_currentMoveType = m_currentMoveType == CellType::X ? CellType::O : CellType::X;
}
