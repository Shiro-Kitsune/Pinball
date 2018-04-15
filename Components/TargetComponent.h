#pragma once

#include "Component.h"
enum class TargetType { Small, Medium, Large };

class TargetComponent : public Component
{
public:
	TargetComponent(int value, const Color& standardColor, const Color& alternateColor);

	int GetValue() const;
	const Color& GetStandardColor() const;
	const Color& GetAlternateColor() const;
	bool ReadyToChangeColor() const;
	void IncreaseTimeElapsedSinceColorChange(float deltaTime);
	void ResetTimeElapsedSinceColorChange();
	bool WasHit() const;
	void SetWasHit(bool wasHit);
private:
	int m_value;
	Color m_standardColor;
	Color m_alternateColor;
	float m_colorDuration;
	float m_timeElapsedSinceColorChange;
	bool m_wasHit;
};
