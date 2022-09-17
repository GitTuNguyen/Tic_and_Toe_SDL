/*player board play*/
#pragma once
#include "Game.h"
#include "Board.h"

Game::Game()
{
	m_board = new Board();
	m_renderer = new Renderer();
	m_currentMoveType = MoveType::X;
	m_isPlayerWantExit = false;
	std::vector<string> gameTextures{ "X", "O", "YES", "NO"};
	for (string texture : gameTextures)
	{
		m_renderer->LoadTexture(texture);
	}
}

void Game::CreateNewMatch()
{
	m_board->Reset();
}

void Game::Rematch(int i_mouse_X, int i_mouse_Y)
{
	
	if (i_mouse_X >= YES_CELL_X && i_mouse_X <= YES_CELL_X + YES_CELL_WIDTH && i_mouse_Y >= YES_CELL_Y && i_mouse_Y <= YES_CELL_Y + YES_CELL_HEIGHT)
	{
		CreateNewMatch();
	}
	else if (i_mouse_X >= NO_CELL_X && i_mouse_X <= NO_CELL_X + NO_CELL_WIDTH && i_mouse_Y >= NO_CELL_Y && i_mouse_Y <= NO_CELL_Y + NO_CELL_HEIGHT) {
		m_isPlayerWantExit = true;
	}
}

void Game::DrawBoad()
{

	MoveType** boardData = m_board->getBoardData();
	for (int i = 0; i < TABLE_ROW; i++)
	{
		for (int j = 0; j < TABLE_COL; j++)
		{
			m_renderer->DrawCell(boardData[i][j], j * TABLE_CELL_SIZE, i * TABLE_CELL_SIZE);
		}
	}
}

void Game::DrawGameOverScreen()
{
	m_renderer->DrawGameOverPopup();
	std::string game_result;
	switch (m_board->GetGameResult())
	{
	case X_WIN:
		game_result = "X WIN";
		break;
	case O_WIN:
		game_result = "O WIN";
		break;
	case DRAW:
		game_result = "DRAW";
		break;
	default:
		break;
	}
	m_renderer->DrawText(game_result, TEXT_GAME_RESULT_SIZE, TEXT_GAME_RESULT_X, TEXT_GAME_RESULT_Y, TEXT_GAME_RESULT_HEIGHT, TEXT_GAME_RESULT_WIDTH);
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
			DrawGameOverScreen();
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
					Rematch(newRect.x, newRect.y);
				}
				default:
				{
					break;
				}
				}
			}
		}
		m_renderer->PostFrame();
	}
	m_renderer->CleanUp();
}

void Game::UpdateMove(int i_X, int i_Y)
{
	m_board->Update(i_X, i_Y, m_currentMoveType);
	m_currentMoveType = m_currentMoveType == MoveType::X ? MoveType::O : MoveType::X;
}

Game::~Game()
{
	delete m_board;
	delete m_renderer;
}
