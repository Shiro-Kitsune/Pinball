#pragma once

#include "System.h"

class MovingPlatformSystem : public System
{
public:
	void Init(GameState& gameState) {}
	void Update(float deltaTime, GameState& gameState);
};