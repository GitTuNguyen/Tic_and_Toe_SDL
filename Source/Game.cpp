/*player board play*/
#pragma once
#include "Game.h"
#include "Board.h"

Game::Game()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("Unable to initialize SDL %s\n", SDL_GetError());
		return;
	}

	//Create window
	window = SDL_CreateWindow("Stdio.vn - SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windows_size, windows_size, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("Could not create window %s", SDL_GetError());
		return;
	}


	//create a renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		printf("Could not create render %s", SDL_GetError());
		return;
	}
	m_board = new Board();
	m_currentMoveType = CellType::X;
	m_isPlayerWantExit = false;
	tempSurface = SDL_LoadBMP("X.bmp");
	//create a texutre from surface
	texture_X = SDL_CreateTextureFromSurface(renderer, tempSurface);
	//free surface
	SDL_FreeSurface(tempSurface);
	tempSurface = SDL_LoadBMP("O.bmp");
	//create a texutre from surface
	texture_O = SDL_CreateTextureFromSurface(renderer, tempSurface);
	//free surface
	SDL_FreeSurface(tempSurface);
}

void Game::CreateNewMatch()
{
	m_board->Reset();
}
void Game::drawBoad()
{
	SDL_Rect newRect;
	newRect.w = 39;
	newRect.h = 39;
	CellType** boardData = m_board->getBoardData();
	for (int i = 0; i < TABLE_COL; i++)
	{
		for (int j = 0; j < TABLE_ROW; j++)
		{
			if (boardData[i][j] == CellType::X)
			{
				newRect.x = i * 40 + 1;
				newRect.y = j * 40 + 1;
				SDL_RenderCopy(renderer, texture_X, NULL, &newRect);
			}
			else if (boardData[i][j] == CellType::O)
			{
				newRect.x = i * 40 + 1;
				newRect.y = j * 40 + 1;
				SDL_RenderCopy(renderer, texture_O, NULL, &newRect);
			}
		}
	}
}
void Game::Rematch()
{
	char inputPlayer;
	cout << k_padding << "Play again? (Y to play again, another key to quit): ";
	cin >> inputPlayer;
	if (inputPlayer == 'Y' || inputPlayer == 'y')
	{
		CreateNewMatch();
	}
	else {
		m_isPlayerWantExit = true;
	}
}
void Game::Update()
{
	while (!m_isPlayerWantExit)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_Point startPoint = { 0, 0 };
		SDL_Point endPoint = { 0, 0 };
		for (int i = 0; i < 400; i += 40)
		{
			startPoint = { i, 0 };
			endPoint = { i, 400 };
			SDL_RenderDrawLine(renderer, startPoint.x, startPoint.y, endPoint.x, endPoint.y);
		}
		for (int i = 0; i < 400; i += 40)
		{
			startPoint = { 0, i };
			endPoint = { 400, i };
			SDL_RenderDrawLine(renderer, startPoint.x, startPoint.y, endPoint.x, endPoint.y);
		}

		//m_board->Render();

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

						if (newRect.x % 40 != 0 && newRect.y % 40 != 0)
						{
							UpdateMove(newRect.x / 40, newRect.y / 40);
						}
					}
					default:
					{
						break;
					}
				}
			}
			drawBoad();
		}
		else {
			Rematch();
		}
		SDL_RenderPresent(renderer);
		SDL_Delay(16);
	}
	//RenderGameOver();
	SDL_DestroyWindow(window);

	//Destroy a renderer
	SDL_DestroyRenderer(renderer);

	//cleans up all initialized subsystems
	SDL_Quit();
}

void Game::UpdateMove(int i_X, int i_Y)
{
	bool isValidMove = false;
	while (!isValidMove)
	{	
		isValidMove = m_board->ValidateMove(i_X, i_Y);
	}
	m_board->Update(i_X, i_Y, m_currentMoveType);
	m_currentMoveType = m_currentMoveType == CellType::X ? CellType::O : CellType::X;
}


/*
void Game::RenderGameOver()
{
	cout << k_padding << "\t       ---Game---+---OVER--- \n";
	GameResult gameResult = m_board->GetGameResult();
	switch (gameResult)
	{
	case NONE:
		break;
	case X_WIN:
		cout << k_padding << "\t+--- Player 1 [X] WIN! Conratulation ---+\n";
		break;
	case O_WIN:
		cout << k_padding << "+--- Player 2 [O] WIN! Conratulation ---+\n";
		break;
	case DRAW:
		cout << k_padding << "+--- Game draw! ---+\n";
		break;
	default:
		break;
	}
}
*/
