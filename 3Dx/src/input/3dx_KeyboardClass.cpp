#include "../../include/Input/3dx_KeyboardClass.h"

InputKeyboardClass::InputKeyboardClass()
{
	for(int i = 0; i < 256; i++)
	{
		// Initialize all key states to off (false)
		this->m_keyStates[i] = false;
	}
}

bool InputKeyboardClass::keyIsPressed(const UCH keycode)
{
	return this->m_keyStates[keycode];
}

bool InputKeyboardClass::keyBufferIsEmpty()
{
	return this->m_keyBuffer.empty();
}

bool InputKeyboardClass::charBufferIsEmpty()
{
	return this->m_charBuffer.empty();
}

KeyboardEvent InputKeyboardClass::readKey()
{
	// If no keys to be read?
	if(this->m_keyBuffer.empty())
	{
		// Return empty keyboard event
		return KeyboardEvent(); 
	}
	else
	{
		// Get first keyboard Event from queue
		// Remove first item from queue
		// And returns keyboard event
		KeyboardEvent keybEvent = this->m_keyBuffer.front();
		this->m_keyBuffer.pop();
		return keybEvent;
	}
}

UCH InputKeyboardClass::readChar()
{
	// If no keys to be read?
	if(this->m_charBuffer.empty())
	{
		return 0u; // Return 0 (NULL char)
	}
	else
	{
		// Get first  char from queue
		// Remove first char from queue
		// And returns char
		UCH uch = this->m_charBuffer.front();
		this->m_charBuffer.pop();
		return uch;
	}
}

void InputKeyboardClass::onKeyPressed(const UCH key)
{
	this->m_keyStates[key] = true;
	this->m_keyBuffer.push(KeyboardEvent(KeyboardEvent::EEventType::tPress, key));
}

void InputKeyboardClass::onKeyReleased(const UCH key)
{
	this->m_keyStates[key] = false;
	this->m_keyBuffer.push(KeyboardEvent(KeyboardEvent::EEventType::tRelease, key));
}

void InputKeyboardClass::onChar(const UCH key)
{
	this->m_charBuffer.push(key);
}

void InputKeyboardClass::enableAutoRepeatKeys()
{
	this->m_autoRepeatKeys = true;
}

void InputKeyboardClass::disableAutoRepeatKeys()
{
	this->m_autoRepeatKeys = false;
}

void InputKeyboardClass::enableAutoRepeatChars()
{
	this->m_autoRepeatChars = true;
}

void InputKeyboardClass::disableAutoRepeatChars()
{
	this->m_autoRepeatChars = false;
}

bool InputKeyboardClass::isKeysAutoRepeat()
{
	return this->m_autoRepeatKeys;
}

bool InputKeyboardClass::isCharsAutoRepeat()
{
	return this->m_autoRepeatChars;
}
