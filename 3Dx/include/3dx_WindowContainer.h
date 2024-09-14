#pragma once
#include "3dx_RenderWindow.h"
#include "Input/3dx_KeyboardClass.h"

class WindowContainer
{
public:
	LRESULT WindowProc(HWND hWnd, UINT message, WPARAM param, LPARAM lParam);

protected:
	RenderWindow renderWindow;
	InputKeyboardClass keyboard;

private:
};