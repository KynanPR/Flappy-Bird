#include "ScoreManager.h"

ScoreManager::ScoreManager()
{
}

int ScoreManager::updateScore(PipeManager& pipeManager, Player player)
{
	float playerX = player.getPosition().x;
	auto pipes = pipeManager.getPipes();
	int amountOfPipes = pipeManager.getAmountOfPipes();
	for (int loopcounter = 0; loopcounter < amountOfPipes; loopcounter++)
	{
		if (pipes[loopcounter].getHasScore() && pipes[loopcounter].getPosition().x < playerX)
		{
			score++;
			pipes[loopcounter].setHasScore(false);
		}
	}
	return score;
}
