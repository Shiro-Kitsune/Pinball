#include "stdafx.h"
#include "TargetComponent.h"

TargetComponent::TargetComponent(int value, const Color& standardColor, const Color& alternateColor) : m_value(value), m_standardColor(standardColor), m_alternateColor(alternateColor)
{
	m_colorDuration = 300.0f;
	m_timeElapsedSinceColorChange = 0.0f;
	m_wasHit = false;
}

int TargetComponent::GetValue() const
{
	return m_value;
}

const Color & TargetComponent::GetStandardColor() const
{
	return m_standardColor;
}

const Color & TargetComponent::GetAlternateColor() const
{
	return m_alternateColor;
}

bool TargetComponent::ReadyToChangeColor() const
{
	return m_timeElapsedSinceColorChange >= m_colorDuration;
}

void TargetComponent::IncreaseTimeElapsedSinceColorChange(float deltaTime)
{
	m_timeElapsedSinceColorChange += deltaTime;
}

void TargetComponent::ResetTimeElapsedSinceColorChange()
{
	m_timeElapsedSinceColorChange = 0.0f;
}

bool TargetComponent::WasHit() const
{
	return m_wasHit;
}

void TargetComponent::SetWasHit(bool wasHit)
{
	m_wasHit = wasHit;
}
