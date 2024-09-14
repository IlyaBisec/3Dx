#pragma once

typedef unsigned char UCH;

// KeyboardEvent - a class that contains keyboard events
class KeyboardEvent
{
public:
	enum EEventType
	{
		tPress, tRelease, tInvalid
	};

	KeyboardEvent();
	KeyboardEvent(const EEventType etype, const UCH key);

	bool isPress() const;
	bool isRelease() const;
	bool isValid() const;

	UCH getKeyCode() const;

private:
	EEventType m_etype;
	UCH m_key;
};