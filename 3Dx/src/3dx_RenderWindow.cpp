#include "../include/3dx_WindowContainer.h"

bool RenderWindow::initialize(WindowContainer *ptr_WindowContainer, HINSTANCE hInstance, std::string windowTitle, std::string windowClass, int width, int height)
{
	this->m_hInstance = hInstance;
	this->m_width = width;
	this->m_height = height;
	this->m_windowTitle = windowTitle;
	this->m_windowTitleWide = StringConverter::stringToWide(this->m_windowTitle);
	this->m_windowClass = windowClass;
	this->m_windowClassWide = StringConverter::stringToWide(this->m_windowClass);

	this->registerWindow();

	this->m_handle = CreateWindowEx
	(
		0, // Extended window style
		this->m_windowClassWide.c_str(),  // Window class name
		this->m_windowTitleWide.c_str(),  // Window title
		WS_CAPTION | WS_MAXIMIZEBOX | WS_SYSMENU, // Window style
		0,	// X position
		0,  // Y position
		this->m_width,	// Window width
		this->m_height, // Window height
		NULL, //Handle to parent of this window. Since this is the first window, it has no parent window
		NULL, //Handle to menu or child window identifier.
			  // Can be set to NULL and use menu in WindowClassEx if a menu is desired to be used.
		this->m_hInstance, //Handle to the instance of module to be used with this window
		nullptr  // Param to create window
	);

	if(this->m_handle == NULL)
	{
		ErrorLogger::log(GetLastError(), "Create windowEX failed for window: " + this->m_windowTitle);
		return false;
	}

	// Bring the window up on the screen and set it as main focus
	ShowWindow(this->m_handle, SW_SHOW);
	SetForegroundWindow(this->m_handle);
	SetFocus(this->m_handle);

	return true;
}

bool RenderWindow::processMessages()
{
	// Handle the window message
	MSG message;
	// Initialize message structure
	ZeroMemory(&message, sizeof(MSG));

	if(PeekMessage(
		&message, // Where store message(if one exists)
		this->m_handle, // Handle to window we are checking messages for
		0, // Minimum filter message value - We are not filtering for specific messages,
		   // but the min/max could be used to filter only mouse messages for example
		0, // Maximum filter message value
		PM_REMOVE // Remove message after capturing it via PeekMessage
		))
	{
		// Translate message from virtual key messages into 
		// character messages so we can dispatch the message
		TranslateMessage(&message);
		// Dispatch message to our Window Proc for this window
		DispatchMessage(&message);
	}

	// Check if the window was closed
	if(message.message == WM_NULL)
	{
		if(!IsWindow(this->m_handle))
		{
			//Message processing loop takes care of destroying this window
			this->m_handle = NULL;
			UnregisterClass(this->m_windowClassWide.c_str(), this->m_hInstance);
			return false;
		}
	}

	return true;
}

HWND RenderWindow::getHWND() const
{
	return this->m_handle;
}

RenderWindow::~RenderWindow()
{
	if(this->m_handle != NULL)
	{
		UnregisterClass(this->m_windowClassWide.c_str(), this->m_hInstance);
		DestroyWindow(m_handle);
	}
}

LRESULT CALLBACK HandleMessageRedirect(HWND hWnd, UINT message, WPARAM param, LPARAM lParam)
{
	switch (message)
	{
		case WM_CLOSE: 
			DestroyWindow(hWnd);
			return 0;
		default:
		{
			// Retrieve ptr to window class
			WindowContainer *const ptr_window = reinterpret_cast<WindowContainer *>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
			// Forward message to window class handler
			return ptr_window->WindowProc(hWnd, message, param, lParam);
		}
	}
}

LRESULT CALLBACK HandleMessageSetup(HWND hWnd, UINT message, WPARAM param, LPARAM lParam)
{
	switch (message)
	{
		case WM_NCCREATE:
		{
			const CREATESTRUCTW *const ptr_create = reinterpret_cast<CREATESTRUCTW *>(lParam);
			WindowContainer *ptr_wndContainer = reinterpret_cast<WindowContainer *>(ptr_create->lpCreateParams);
			// Sanity check
			if(ptr_wndContainer == nullptr)
			{
				ErrorLogger::log("Critical Error: Pointer to window container is null during WN_NCCREATE");
				exit(-1);
			}

			SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(ptr_wndContainer));
			SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(HandleMessageRedirect));
			return ptr_wndContainer->WindowProc(hWnd, message, param, lParam);
		}
		default:
			return DefWindowProc(hWnd, message, param, lParam);
	}
}


void RenderWindow::registerWindow()
{
	WNDCLASSEX windClass;
	// Flags [Redraw on width/height change from resize/movement] 
	windClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	// Pointer to Window Proc function for handling messages from this window
	windClass.lpfnWndProc = DefWindowProc;
	windClass.cbClsExtra = 0; // Extra bytes to allocate following the window-class structure
	windClass.cbWndExtra = 0; // Extra bytes to allocate following the window instance
	windClass.hInstance = this->m_hInstance; // Handle to the instance that contains the Window Procedure
	windClass.hIcon = NULL;    // Handle to the class icon. Must be a handle to an icon resource
	windClass.hIconSm = NULL;  // Handle to small icon for this class
	// Default Cursor - If we leave this null we have to explicitly set the cursor's
	// shape each time it enters the window
	windClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	// Handle to the class background brush for the window's background color
	windClass.hbrBackground = NULL; 
	// Pointer to a null terminated character string for the menu
	windClass.lpszMenuName = NULL; 
	// Pointer to null terminated string of our class name for this window
	windClass.lpszClassName = this->m_windowClassWide.c_str();
	windClass.cbSize = sizeof(WNDCLASSEX); // Need to fill in the size of our struct for cbSize
	RegisterClassEx(&windClass); // Register the class so that it is usable
}
