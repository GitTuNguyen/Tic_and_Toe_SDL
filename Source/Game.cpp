#pragma once
#include "Game.h"

Game::Game()
{	
	m_renderer = new Renderer();
	m_board = new Board(m_renderer->GetBoardCollum(), m_renderer->GetBoardRow());	
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
	for (int i = 0; i < m_renderer->GetBoardRow(); i++)
	{
		for (int j = 0; j < m_renderer->GetBoardCollum(); j++)
		{
			m_renderer->DrawCell(boardData[i][j], j * m_renderer->GetCellSize(), i * m_renderer->GetCellSize());
		}
	}
}

void Game::DrawGameResultText()
{
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

	int windowPopupX = (m_renderer->GetWindowWidth() - GAME_OVER_POPUP_WIDTH * m_renderer->GetCellSize()) / 2;
	int windowPopupY = (m_renderer->GetWindowHeight() - GAME_OVER_POPUP_HEIGHT * m_renderer->GetCellSize()) / 2;
	m_renderer->DrawText(game_result, TEXT_SIZE, windowPopupX + ((GAME_OVER_POPUP_WIDTH - TEXT_GAME_RESULT_WIDTH) * m_renderer->GetCellSize()) / 2, windowPopupY + m_renderer->GetCellSize() + m_renderer->GetCellSize() / 2, TEXT_GAME_RESULT_HEIGHT * m_renderer->GetCellSize(), TEXT_GAME_RESULT_WIDTH * m_renderer->GetCellSize());
}

void Game::DrawGameOverScreen()
{
	m_renderer->DrawGameOverPopup();
	DrawGameResultText();	
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
				if (mouseX % m_renderer->GetCellSize() != 0 && mouseY % m_renderer->GetCellSize() != 0 && m_board->ValidateMove(floor(mouseY / m_renderer->GetCellSize()), floor(mouseX / m_renderer->GetCellSize())))
				{
					UpdateMove(floor(mouseY / m_renderer->GetCellSize()), floor(mouseX / m_renderer->GetCellSize()));
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
								
				int yesButtonX = (m_renderer->GetWindowWidth() - GAME_OVER_POPUP_WIDTH * m_renderer->GetCellSize()) / 2 + m_renderer->GetCellSize() * 2;
				int yesButtonY = (m_renderer->GetWindowHeight() - GAME_OVER_POPUP_HEIGHT * m_renderer->GetCellSize()) / 2 + m_renderer->GetCellSize() * 3 + m_renderer->GetCellSize() / 2;
				int noButtonX = yesButtonX + m_renderer->GetCellSize() * 2;
				int noButtonY = yesButtonY;

				if (mouseX >= yesButtonX && mouseX <= yesButtonX + YES_BUTTON_WIDTH * m_renderer->GetCellSize() && mouseY >= yesButtonY && mouseY <= yesButtonY + YES_BUTTON_HEIGHT * m_renderer->GetCellSize())
				{
					CreateNewMatch();
				}
				else if (mouseX >= noButtonX && mouseX <= noButtonX + NO_BUTTON_WIDTH * m_renderer->GetCellSize() && mouseY >= noButtonY && mouseY <= noButtonY + NO_BUTTON_HEIGHT * m_renderer->GetCellSize()) {
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
