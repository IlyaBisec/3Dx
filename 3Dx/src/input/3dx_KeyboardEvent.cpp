#include "../../include/Input/3dx_KeyboardEvent.h"

KeyboardEvent::KeyboardEvent() : m_etype(EEventType::tInvalid), m_key(0u)
{

}

KeyboardEvent::KeyboardEvent(const EEventType etype, const UCH key) : m_etype(etype), m_key(key)
{
}

bool KeyboardEvent::isPress() const
{
	return this->m_etype == EEventType::tPress;
}

bool KeyboardEvent::isRelease() const
{
	return this->m_etype == EEventType::tRelease;
}

bool KeyboardEvent::isValid() const
{
	return this->m_etype != EEventType::tInvalid;
}

UCH KeyboardEvent::getKeyCode() const
{
	return this->m_key;
}
