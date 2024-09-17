#include "../../include/Input/3dx_MouseEvent.h"

DxMouseEvent::DxMouseEvent(): m_etype(EMEventType::tIvalid),
m_x(0), m_y(0)
{
}

DxMouseEvent::DxMouseEvent(const EMEventType etype, const int x, const int y):
	m_etype(etype), m_x(x), m_y(y)
{

}

bool DxMouseEvent::isValid() const
{
	return this->m_etype != EMEventType::tIvalid;
}

DxMouseEvent::EMEventType DxMouseEvent::getType() const
{
	return this->m_etype;
}

MousePoint DxMouseEvent::getPosition() const
{
	return { this->m_x, this->m_y };
}

int DxMouseEvent::getPositionX() const
{
	return this->m_x;
}

int DxMouseEvent::getPositionY() const
{
	return this->m_y;
}
