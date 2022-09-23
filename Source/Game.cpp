#pragma once
#include "Game.h"

Game::Game()
{
	m_board = new Board();
	m_renderer = new Renderer();
	m_inputManager = new InputManager();
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

void Game::DrawBoad()
{

	MoveType** boardData = m_board->GetBoardData();
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
	m_renderer->DrawText(game_result, TEXT_SIZE, TEXT_GAME_RESULT_X, TEXT_GAME_RESULT_Y, TEXT_GAME_RESULT_HEIGHT, TEXT_GAME_RESULT_WIDTH);
}

void Game::Update()
{
	while (!m_isPlayerWantExit)
	{
		m_renderer->PreRendering();
		m_renderer->DrawTable();
		m_inputManager->UpdateInput();
		m_isPlayerWantExit = m_inputManager->IsGoingToQuit();
		GameResult gameResult = m_board->GetGameResult();
		if (gameResult == GameResult::NONE)
		{
			if (m_inputManager->IsMouseUp())
			{
				int mouseX = m_inputManager->GetMouseX();
				int mouseY = m_inputManager->GetMouseY();
				if (mouseX % TABLE_CELL_SIZE != 0 && mouseY % TABLE_CELL_SIZE != 0 && m_board->ValidateMove(floor(mouseY / TABLE_CELL_SIZE), floor(mouseX / TABLE_CELL_SIZE)))
				{
					UpdateMove(floor(mouseY / TABLE_CELL_SIZE), floor(mouseX / TABLE_CELL_SIZE));
				}
			}			
			DrawBoad();
		}
		else {
			DrawGameOverScreen();			
			if (m_inputManager->IsMouseUp())
			{
				int mouseX = m_inputManager->GetMouseX();
				int mouseY = m_inputManager->GetMouseY();
				if (mouseX >= YES_BUTTON_X && mouseX <= YES_BUTTON_X + YES_BUTTON_WIDTH && mouseY >= YES_BUTTON_Y && mouseY <= YES_BUTTON_Y + YES_BUTTON_HEIGHT)
				{
					CreateNewMatch();
				}
				else if (mouseX >= NO_BUTTON_X && mouseX <= NO_BUTTON_X + NO_BUTTON_WIDTH && mouseY >= NO_BUTTON_Y && mouseY <= NO_BUTTON_Y + NO_BUTTON_HEIGHT) {
					m_isPlayerWantExit = true;
				}
			}
		}
		m_renderer->PostFrame();
	}
	m_renderer->CleanUp();
}

void Game::UpdateMove(int i_x, int i_y)
{
	m_board->Update(i_x, i_y, m_currentMoveType);
	m_currentMoveType = m_currentMoveType == MoveType::X ? MoveType::O : MoveType::X;
}

Game::~Game()
{
	delete m_board;
	delete m_renderer;
	delete m_inputManager;
}
