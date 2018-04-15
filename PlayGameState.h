#pragma once

#include "GameState.h"
#include "System.h"

class PlayGameState : public GameState
{
public:
	void Init();
	void Cleanup();

	void HandleEvents(GameEngine& game);
	void Update(GameEngine& game, float deltaTime);

	static PlayGameState* Instance() { return &m_playGameState; }
protected:
	PlayGameState() { }
private:
	void CreateField();
	void CreateObjects();
	void CreateSystems();
	void CreateMainGameUI();
	void CreateEndGameUI(int score);
private:
	static PlayGameState m_playGameState;
	std::vector<std::unique_ptr<System>> m_systems;
	bool m_gameOver;
};