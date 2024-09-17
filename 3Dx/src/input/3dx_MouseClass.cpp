#include "../../include/Input/3dx_MouseClass.h"

void InputMouseClass::onLeftPressed(int x, int y)
{
	this->m_leftIsDown = true;
	DxMouseEvent mevent(DxMouseEvent::EMEventType::tLeftPress, x, y);
	this->m_eventBuffer.push(mevent);
}

void InputMouseClass::onRightPressed(int x, int y)
{
	this->m_rightIsDown = true;
	this->m_eventBuffer.push(DxMouseEvent(DxMouseEvent::EMEventType::tRiftPress, x, y));
}

void InputMouseClass::onMiddlePressed(int x, int y)
{
	this->m_mbuttonDown = true;
	this->m_eventBuffer.push(DxMouseEvent(DxMouseEvent::EMEventType::tMiddlePress, x, y));
}

void InputMouseClass::onLeftReleased(int x, int y)
{
	this->m_leftIsDown = false;
	this->m_eventBuffer.push(DxMouseEvent(DxMouseEvent::EMEventType::tLeftRelease, x, y));
}

void InputMouseClass::onRightReleased(int x, int y)
{
	this->m_rightIsDown = false;
	this->m_eventBuffer.push(DxMouseEvent(DxMouseEvent::EMEventType::tRigtRelease, x, y));
}

void InputMouseClass::onMiddleReleased(int x, int y)
{
	this->m_mbuttonDown = false;
	this->m_eventBuffer.push(DxMouseEvent(DxMouseEvent::EMEventType::tMiddleRelease, x, y));
}

void InputMouseClass::onWheelUp(int x, int y)
{
	this->m_eventBuffer.push(DxMouseEvent(DxMouseEvent::EMEventType::tWheelUp, x, y));
}

void InputMouseClass::onWheelDown(int x, int y)
{
	this->m_eventBuffer.push(DxMouseEvent(DxMouseEvent::EMEventType::tWheelDown, x, y));
}

void InputMouseClass::onMouseMove(int x, int y)
{
	this->m_x = x;
	this->m_y = y;
	this->m_eventBuffer.push(DxMouseEvent(DxMouseEvent::EMEventType::tMove, x, y));
}

void InputMouseClass::onMouseMoveRaw(int x, int y)
{
	this->m_eventBuffer.push(DxMouseEvent(DxMouseEvent::EMEventType::tRawMove, x, y));
}

bool InputMouseClass::isLeftDown()
{
	return this->m_leftIsDown;
}

bool InputMouseClass::isRightDown()
{
	return this->m_rightIsDown;
}

bool InputMouseClass::isMiddleDown()
{
	return this->m_mbuttonDown;
}

int InputMouseClass::getPositionX()
{
	return this->m_x;
}

int InputMouseClass::getPositionY()
{
	return this->m_y;
}

MousePoint InputMouseClass::getPostiotion()
{
	return { this->m_x, this->m_y };
}

bool InputMouseClass::eventByfferIsEmpty()
{
	return this->m_eventBuffer.empty();
}

DxMouseEvent InputMouseClass::readEvent()
{
	if (this->m_eventBuffer.empty())
	{
		return DxMouseEvent();
	}
	else
	{
		//Get first event from buffer
		//Remove first event from buffer
		DxMouseEvent mevent = this->m_eventBuffer.front();
		this->m_eventBuffer.pop();
		return mevent;
	}
}
