#pragma once

#include "System.h"
class Entity;
class TargetComponent;

class TargetSystem : public System
{
public:
	void Init(GameState& gameState) {}
	void Update(float deltaTime, GameState& gameState);
private:
	void ChangeTargetColorToAlternative(Entity& entity, TargetComponent& target);
	void ChangeTargetColorToStandard(Entity& entity, TargetComponent& target);
};
