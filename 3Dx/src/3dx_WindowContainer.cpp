#include "../include/3dx_WindowContainer.h"
#include <memory>

WindowContainer::WindowContainer()
{
	static bool rawInputInit = false;

	if(rawInputInit == false)
	{
		RAWINPUTDEVICE rid;

		// Mouse
		rid.usUsagePage = 0x01;
		rid.usUsage = 0x02;
		rid.dwFlags = 0;
		rid.hwndTarget = NULL;

		if(RegisterRawInputDevices(&rid, 1, sizeof(rid)) == FALSE)
		{
			ErrorLogger::log(GetLastError(), "Failed to register raw input devices");
			exit(-1);
		}

		rawInputInit = true;
	}
}

LRESULT WindowContainer::WindowProc(HWND hWnd, UINT message, WPARAM param, LPARAM lParam)
{
	switch (message)
	{
		// Keyboard
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
		// Mouse
		case WM_MOUSEMOVE:
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);
			mouse.onMouseMove(x, y);
			return 0;
		}
		case WM_LBUTTONDOWN:
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);
			mouse.onLeftPressed(x, y);
			return 0;
		}
		case WM_RBUTTONDOWN:
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);
			mouse.onRightPressed(x, y);
			return 0;
		}
		case WM_MBUTTONDOWN:
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);
			mouse.onMiddlePressed(x, y);
			return 0;
		}
		case WM_LBUTTONUP:
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);
			mouse.onLeftReleased(x, y);
			return 0;
		}
		case WM_RBUTTONUP:
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);
			mouse.onRightReleased(x, y);
			return 0;
		}
		case WM_MBUTTONUP:
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);
			mouse.onMiddleReleased(x, y);
			return 0;
		}
		case WM_MOUSEWHEEL:
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);
			if (GET_WHEEL_DELTA_WPARAM(param) > 0)
			{
				mouse.onWheelUp(x, y);
			}
			else if (GET_WHEEL_DELTA_WPARAM(param) < 0)
			{
				mouse.onWheelDown(x, y);
			}
			return 0;
		}
		case WM_INPUT:
		{
			UINT dataSize;
			//Need to populate data size first
			GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, NULL, &dataSize, sizeof(RAWINPUTHEADER)); 
		
			if (dataSize > 0)
			{
				std::unique_ptr<BYTE[]> rawdata = std::make_unique<BYTE[]>(dataSize);
				if (GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, rawdata.get(), &dataSize, sizeof(RAWINPUTHEADER)) == dataSize)
				{
					RAWINPUT* raw = reinterpret_cast<RAWINPUT*>(rawdata.get());
					if (raw->header.dwType == RIM_TYPEMOUSE)
					{
						mouse.onMouseMoveRaw(raw->data.mouse.lLastX, raw->data.mouse.lLastY);
					}
				}
			}
			//Need to call DefWindowProc for WM_INPUT messages
			return DefWindowProc(hWnd, message, param, lParam); 
		}
		default:
			return DefWindowProc(hWnd, message, param, lParam);
	}
}
