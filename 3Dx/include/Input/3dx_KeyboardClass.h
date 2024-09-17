#pragma once
#include "3dx_KeyboardEvent.h"
#include <queue>

// InputKeyboardClass - a class that handles keyboard keystrokes
class InputKeyboardClass
{
public:
	InputKeyboardClass();

	bool keyIsPressed(const UCH keycode);
	bool keyBufferIsEmpty();
	bool charBufferIsEmpty();

	DxKeyboardEvent readKey();
	UCH readChar();

	void onKeyPressed(const UCH key);
	void onKeyReleased(const UCH key);
	void onChar(const UCH key);

	void enableAutoRepeatKeys();
	void disableAutoRepeatKeys();
	void enableAutoRepeatChars();
	void disableAutoRepeatChars();

	bool isKeysAutoRepeat();
	bool isCharsAutoRepeat();

private: 
	bool m_autoRepeatKeys = false;
	bool m_autoRepeatChars = false;
	bool m_keyStates[256];

	std::queue<DxKeyboardEvent> m_keyBuffer;
	std::queue<UCH> m_charBuffer;
};