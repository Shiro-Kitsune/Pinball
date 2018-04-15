#pragma once

#include "System.h"
class TextComponent;

class TextUpdateSystem : public System
{
public:
	void Init(GameState& gameState);
	void Update(float deltaTime, GameState& gameState);
private:
	void UpdateScoreText();
	void UpdateLivesText();
private:
	int m_score;
	int m_lives = 5;
	TextComponent* m_scoreText;
	TextComponent* m_livesText;
};
