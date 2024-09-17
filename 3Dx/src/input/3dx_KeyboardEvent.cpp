#include "../../include/Input/3dx_KeyboardEvent.h"

DxKeyboardEvent::DxKeyboardEvent() : m_etype(EKbEventType::tInvalid), m_key(0u)
{

}

DxKeyboardEvent::DxKeyboardEvent(const EKbEventType etype, const UCH key) : m_etype(etype), m_key(key)
{
}

bool DxKeyboardEvent::isPress() const
{
	return this->m_etype == EKbEventType::tPress;
}

bool DxKeyboardEvent::isRelease() const
{
	return this->m_etype == EKbEventType::tRelease;
}

bool DxKeyboardEvent::isValid() const
{
	return this->m_etype != EKbEventType::tInvalid;
}

UCH DxKeyboardEvent::getKeyCode() const
{
	return this->m_key;
}
