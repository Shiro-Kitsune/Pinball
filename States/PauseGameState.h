#pragma once

#include "GameState.h"
#include "../Systems/System.h"

class PauseGameState : public GameState
{
public:
	void Init();
	void Cleanup();

	void HandleEvents(GameEngine& game);
	void Update(GameEngine& game, float deltaTime);

	static PauseGameState* Instance() {
		return &m_pauseState;
	}

protected:
	PauseGameState() { }
private:
	void CreateSystems();
	void CreateUI();
private:
	static PauseGameState m_pauseState;
	std::vector<std::unique_ptr<System>> m_systems;
};
