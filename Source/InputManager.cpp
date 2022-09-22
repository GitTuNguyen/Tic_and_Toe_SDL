#include "InputManager.h"

InputManager::InputManager()
{
	m_mouseX = 0;
	m_mouseY = 0;
	m_isQuit = false;
	m_isMouseDown = false;
}

void InputManager::UpdateInput()
{
	while (SDL_PollEvent(&mainEvent))
	{
		switch (mainEvent.type)
		{
		case SDL_QUIT:
		{
			m_isQuit = true;
			break;
		}
		case SDL_MOUSEBUTTONDOWN:
		{
			m_isMouseDown = true;
			
		}
		case SDL_MOUSEBUTTONUP:
		{
			m_mouseX = mainEvent.motion.x;
			m_mouseY = mainEvent.motion.y;
			m_isMouseDown = false;
		}
		default:
		{
			break;
		}
		}
	}
}

int InputManager::getMouseX()
{
	return m_mouseX;
}

int InputManager::getMouseY()
{
	return m_mouseY;
}

bool InputManager::getIsQuit()
{
	return m_isQuit;
}

bool InputManager::getIsMouseDown()
{
	return m_isMouseDown;
}
