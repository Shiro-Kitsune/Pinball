#include "stdafx.h"
#include "EventManager.h"

struct predicate
{
	bool operator()(const std::unique_ptr<Event> & event) const
	{
		return event->WasRead();
	}
};

void EventManager::AddEvent(std::unique_ptr<Event> event)
{
	m_events.push_back(std::move(event));
}

const std::vector<std::unique_ptr<Event>>& EventManager::GetEvents() const
{
	return m_events;
}

int EventManager::GetNumberOfEvents() const
{
	return m_events.size();
}

void EventManager::RemoveAllEvents()
{
	m_events.clear();
}

void EventManager::RemoveReadEvents()
{
	m_events.erase(std::remove_if(m_events.begin(), m_events.end(), predicate()), m_events.end());
}