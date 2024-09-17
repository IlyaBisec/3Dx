#pragma once
#ifndef DX_MOUSE_EVENT_H_
#define DX_MOUSE_EVENT_H_

// MousePoint - struct of position of the mouse
struct MousePoint
{
	int x;
	int y;
};

// DxMouseEvent - a class that contains keyboard events
class DxMouseEvent
{
public:
	enum EMEventType
	{
		tLeftPress,
		tLeftRelease,
		tRiftPress,
		tRigtRelease,
		tMiddlePress,
		tMiddleRelease,
		tWheelUp,
		tWheelDown,
		tMove,
		tRawMove,
		tIvalid
	};

	DxMouseEvent();
	DxMouseEvent(const EMEventType etype, const int x, const int y);

	bool isValid() const;
	
	EMEventType getType() const;
	MousePoint getPosition() const;

	int getPositionX() const;
	int getPositionY() const;

private:
	EMEventType m_etype;
	int m_x, m_y;
};



#endif // !3DX_MOUSE_EVENT_H_