#pragma once

class Entity;

enum class EventType { GameEvent, UIEvent };
enum class GameEventType { PlayerDied, ScoreChanged, LivesDecreased, LivesIncreased, LaunchBall };

class Event
{
public:
	virtual ~Event() {}
	virtual EventType GetEventType() const final;
	virtual void MarkAsRead() final;
	virtual bool WasRead() const final;
protected:
	Event(EventType type);
private:
	EventType m_type;
	bool m_read;
};


class GameEvent : public Event
{
public:
	GameEvent(GameEventType type, int value);
	GameEventType GetGameEventType() const;
	int GetValue() const;
private:
	GameEventType m_type;
	int m_value;
};


class UIEvent : public Event
{
public:
	UIEvent(const std::string& buttonName);
	const std::string& GetButtonName() const;
private:
	std::string m_buttonName;
};