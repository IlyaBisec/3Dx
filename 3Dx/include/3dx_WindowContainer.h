#pragma once
#include "3dx_RenderWindow.h"
#include "Input/3dx_KeyboardClass.h"
#include "Input/3dx_MouseClass.h"
#include "graphics/3dx_Graphics.h"

class WindowContainer
{
public:
	WindowContainer();
	LRESULT WindowProc(HWND hWnd, UINT message, WPARAM param, LPARAM lParam);

protected:
	RenderWindow renderWindow;
	DxGraphics graphics;
	InputKeyboardClass keyboard;
	InputMouseClass mouse;
private:
};