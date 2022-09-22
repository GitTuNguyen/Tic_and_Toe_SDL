#pragma once
#include "SDL.h"

class InputManager 
{
public:
	InputManager();
	void UpdateInput();
	int getMouseX();
	int getMouseY();
	bool getIsQuit();
	bool getIsMouseDown();
private:
	SDL_Event mainEvent;
	int m_mouseX;
	int m_mouseY;
	bool m_isQuit;
	bool m_isMouseDown;
};