#pragma once

#include "GameState.h"
#include "../Systems/System.h"

class StartMenuState : public GameState
{
public:
	void Init();
	void Cleanup();

	void HandleEvents(GameEngine& game);
	void Update(GameEngine& game, float deltaTime);

	static StartMenuState* Instance() {
		return &m_startMenuState;
	}

protected:
	StartMenuState() { }
private:
	void CreateSystems();
	void CreateMainGameUI();
private:
	static StartMenuState m_startMenuState;
	std::vector<std::unique_ptr<System>> m_systems;
};
