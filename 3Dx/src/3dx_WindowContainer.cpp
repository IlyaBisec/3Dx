#include "../include/3dx_WindowContainer.h"

LRESULT WindowContainer::WindowProc(HWND hWnd, UINT message, WPARAM param, LPARAM lParam)
{
	return DefWindowProc(hWnd, message, param, lParam);
}
