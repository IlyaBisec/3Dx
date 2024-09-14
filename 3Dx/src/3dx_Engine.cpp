#include "../include/3dx_Engine.h"

bool DxEngine::initialize(HINSTANCE hInstance, std::string windowTitle, std::string windowClass, int width, int height)
{
	return this->renderWindow.initialize(hInstance, windowTitle, windowTitle, width, height);
}

bool DxEngine::processMessages()
{
	return this->renderWindow.processMessages();
}
