#pragma once
#include "3dx_MouseEvent.h"
#include <queue>

// InputMouseClass - a class that handles mouse keystrokes
class InputMouseClass
{
public:
	void onLeftPressed(int x, int y);
	void onRightPressed(int x, int y);
	void onMiddlePressed(int x, int y);
	void onLeftReleased(int x, int y);
	void onRightReleased(int x, int y);
	void onMiddleReleased(int x, int y);
	
	void onWheelUp(int x, int y);
	void onWheelDown(int x, int y);
	void onMouseMove(int x, int y);
	void onMouseMoveRaw(int x, int y);

	bool isLeftDown();
	bool isRightDown();
	bool isMiddleDown();

	int getPositionX();
	int getPositionY();
	MousePoint getPostiotion();

	bool eventByfferIsEmpty();
	DxMouseEvent readEvent();

private:
	std::queue<DxMouseEvent> m_eventBuffer;

	bool m_leftIsDown = false;
	bool m_rightIsDown = false;
	bool m_mbuttonDown = false;
	
	int  m_x = 0;
	int  m_y = 0;
};