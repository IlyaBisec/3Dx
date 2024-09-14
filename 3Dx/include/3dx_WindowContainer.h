#pragma once
#include "3dx_RenderWindow.h"

class WindowContainer
{
public:
	LRESULT WindowProc(HWND hWnd, UINT message, WPARAM param, LPARAM lParam);

protected:
	RenderWindow renderWindow;

private:
};