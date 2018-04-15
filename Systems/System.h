#pragma once

class GameState;

class System
{
public:
	virtual ~System() {}
	virtual void Init(GameState& gameState) = 0;
	virtual void Update(float deltaTime, GameState& gameState) = 0;
};
