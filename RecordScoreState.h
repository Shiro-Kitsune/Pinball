#pragma once

#include "GameState.h"
#include "System.h"

class RecordScoreState : public GameState
{
public:
	void Init();
	void Cleanup();

	void HandleEvents(GameEngine& game);
	void Update(GameEngine& game, float deltaTime);

	static RecordScoreState* Instance() {
		return &m_scoreState;
	}

protected:
	RecordScoreState() { }
private:
	void CreateSystems();
	void CreateUI();
private:
	static RecordScoreState m_scoreState;
	std::vector<std::unique_ptr<System>> m_systems;
};