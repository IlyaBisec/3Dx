#pragma once
#include "3dx_WindowContainer.h"

class DxEngine : WindowContainer
{
public:
	bool initialize(HINSTANCE hInstance, std::string windowTitle, std::string windowClass, int width, int height);
	bool processMessages();
};