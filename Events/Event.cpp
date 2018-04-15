#include "stdafx.h"
#include "Event.h"

Event::Event(EventType type) : m_type(type), m_read(false)
{
}

EventType Event::GetEventType() const
{
	return m_type;
}

void Event::MarkAsRead()
{
	m_read = true;
}

bool Event::WasRead() const
{
	return m_read;
}


GameEvent::GameEvent(GameEventType type, int value) : Event(EventType::GameEvent), m_type(type)
{
	m_value = value;
}

GameEventType GameEvent::GetGameEventType() const
{
	return m_type;
}

int GameEvent::GetValue() const
{
	return m_value;
}


UIEvent::UIEvent(const std::string& buttonName) : Event(EventType::UIEvent), m_buttonName(buttonName)
{
}

const std::string& UIEvent::GetButtonName() const
{
	return m_buttonName;
}
