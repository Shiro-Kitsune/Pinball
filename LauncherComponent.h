#pragma once

#include "Component.h"

class LauncherComponent : public Component
{
public:
	LauncherComponent(int launchKeyCode, float verticalSpeed, float currentY);
	bool LaunchAction() const;
	float GetVerticalSpeed() const;
	float GetMaxPositionY() const;
	float GetMinPositionY() const;
	float GetLastPositionY() const;
	void SetLastPositionY(float y);
	bool IsMoving() const;
	void SetMoving(bool moving);
private:
	int m_launchKeyCode;
	float m_verticalSpeed;
	float m_maxY;
	float m_minY;
	float m_lastY;
	bool m_moving;
};