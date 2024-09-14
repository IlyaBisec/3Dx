#pragma once
#include "3dx_ErrLogger.h"

// RenderWindow - the class that displays the 3Dx editor window
class RenderWindow
{
public:
	bool initialize(HINSTANCE hInstance, std::string windowTitle,
		std::string windowClass, int width, int height);
	bool processMessages();

	~RenderWindow();
private:
	void registerWindow();

	// Handle to this window
	HWND m_handle = NULL;
	// Handle to application instance
	HINSTANCE m_hInstance = NULL; 

	std::string  m_windowTitle = "";
	// Wide string representation of window title
	std::wstring m_windowTitleWide = L"";
	std::string  m_windowClass = "";
	// Wide string representation of window class name
	std::wstring m_windowClassWide = L"";

	int m_width = 0;
	int m_height = 0;
};