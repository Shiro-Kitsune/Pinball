#pragma once

#include "Event.h"

class EventManager
{
public:
	void AddEvent(std::unique_ptr<Event> event);
	const std::vector<std::unique_ptr<Event>>& GetEvents() const;
	int GetNumberOfEvents() const;
	void RemoveAllEvents();
	void RemoveReadEvents();
private:
	std::vector<std::unique_ptr<Event>> m_events;
};