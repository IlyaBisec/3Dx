#include "../include/3dx_WindowContainer.h"

LRESULT WindowContainer::WindowProc(HWND hWnd, UINT message, WPARAM param, LPARAM lParam)
{
	switch (message)
	{
		case WM_KEYDOWN:
		{
			UCH keyCode = static_cast<UCH>(param);
			if(keyboard.isKeysAutoRepeat())
			{
				keyboard.onKeyPressed(keyCode);
			}
			else
			{
				const bool wasPressed = lParam & 0x40000000;
				if (!wasPressed)
					keyboard.onKeyPressed(keyCode);
			}
			return 0;
		}
		case WM_KEYUP:
		{
			UCH keyCode = static_cast<UCH>(param);
			keyboard.onKeyReleased(keyCode);
			return 0;
		}
		case WM_CHAR:
		{
			UCH uch = static_cast<UCH>(param);
			if(keyboard.isCharsAutoRepeat())
			{
				keyboard.onChar(uch);
			}
			else
			{
				const bool wasPressed = lParam & 0x40000000;
				if (!wasPressed)
					keyboard.onChar(uch);
			}
			return 0;
		}
		default:
			return DefWindowProc(hWnd, message, param, lParam);
	}
}
