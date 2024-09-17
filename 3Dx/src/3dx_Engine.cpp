#include "../include/3dx_Engine.h"

bool DxEngine::initialize(HINSTANCE hInstance, std::string windowTitle, std::string windowClass, int width, int height)
{
	if (!this->renderWindow.initialize(this, hInstance, windowTitle, windowClass, width, height))
		return false;

	if (!graphics.initialize(this->renderWindow.getHWND(), width, height))
		return false;

	return true;

	///return this->renderWindow.initialize(hInstance, windowTitle, windowTitle, width, height);
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
		/*std::string out_message = "Char: ";
		out_message += uch;
		out_message += "\n";
		OutputDebugStringA(out_message.c_str());*/
	}

	while (!keyboard.keyBufferIsEmpty())
	{
		DxKeyboardEvent keybEvent = keyboard.readKey();
		UCH keyCode = keybEvent.getKeyCode();
		
		// For console out
		/*std::string out_message = "";
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
		OutputDebugStringA(out_message.c_str());*/
	}

	while (!mouse.eventByfferIsEmpty())
	{
		DxMouseEvent mevent = mouse.readEvent();
		// For console out
		/*if(mevent.getType() == DxMouseEvent::EMEventType::tRawMove)
		{
			std::string msg = "X: ";
			msg += std::to_string(mevent.getPositionX());
			msg += ", ";
			msg += "X: ";
			msg += std::to_string(mevent.getPositionY());
			msg += "\n";
			OutputDebugStringA(msg.c_str());
		}*/
	}
}
