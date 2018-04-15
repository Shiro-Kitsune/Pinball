#pragma once

#include "GameState.h"

class IntroGameState : public GameState
{
public:
	void Init();
	void Cleanup();

	void HandleEvents(GameEngine& game);
	void Update(GameEngine& game, float deltaTime);

	static IntroGameState* Instance() {
		return &m_introState;
	}

protected:
	IntroGameState() { }
private:
	void CreateMainGameUI();
private:
	static IntroGameState m_introState;
};