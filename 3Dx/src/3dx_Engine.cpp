#include "../include/3dx_Engine.h"

bool DxEngine::initialize(HINSTANCE hInstance, std::string windowTitle, std::string windowClass, int width, int height)
{
	return this->renderWindow.initialize(hInstance, windowTitle, windowTitle, width, height);
}

bool DxEngine::processMessages()
{
	return this->renderWindow.processMessages();
}

void DxEngine::update()
{
	while (!keyboard.charBufferIsEmpty())
	{
		UCH uch = keyboard.readChar();

		// For console out
		std::string out_message = "Char: ";
		out_message += uch;
		out_message += "\n";
		OutputDebugStringA(out_message.c_str());
	}

	while (!keyboard.keyBufferIsEmpty())
	{
		KeyboardEvent keybEvent = keyboard.readKey();
		UCH keyCode = keybEvent.getKeyCode();
		
		// For console out
		std::string out_message = "";
		if(keybEvent.isPress())
		{
			out_message += "Key press: ";
		}
		if(keybEvent.isRelease())
		{
			out_message += "Key release: ";
		}
		out_message += keyCode;
		out_message += "\n";
		OutputDebugStringA(out_message.c_str());
	}
}
