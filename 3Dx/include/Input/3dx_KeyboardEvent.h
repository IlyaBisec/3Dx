#pragma once

typedef unsigned char UCH;

// KeyboardEvent - a class that contains keyboard events
class DxKeyboardEvent
{
public:
	enum EKbEventType
	{
		tPress, tRelease, tInvalid
	};

	DxKeyboardEvent();
	DxKeyboardEvent(const EKbEventType etype, const UCH key);

	bool isPress() const;
	bool isRelease() const;
	bool isValid() const;

	UCH getKeyCode() const;

private:
	EKbEventType m_etype;
	UCH m_key;
};