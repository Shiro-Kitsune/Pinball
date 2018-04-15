#include "stdafx.h"
#include "LauncherComponent.h"

LauncherComponent::LauncherComponent(int launchKeyCode, float verticalSpeed, float currentY) : m_launchKeyCode(launchKeyCode), m_verticalSpeed(verticalSpeed)
{
	m_maxY = currentY;
	m_minY = 0.0f;
	m_lastY = currentY;
	m_moving = false;
}

bool LauncherComponent::LaunchAction() const
{
	return App::IsKeyPressed(m_launchKeyCode);;
}

float LauncherComponent::GetVerticalSpeed() const
{
	return m_verticalSpeed;
}

float LauncherComponent::GetMaxPositionY() const
{
	return m_maxY;
}

float LauncherComponent::GetMinPositionY() const
{
	return m_minY;
}

float LauncherComponent::GetLastPositionY() const
{
	return m_lastY;
}

void LauncherComponent::SetLastPositionY(float y)
{
	m_lastY = y;
}

bool LauncherComponent::IsMoving() const
{
	return m_moving;
}

void LauncherComponent::SetMoving(bool moving)
{
	m_moving = moving;
}