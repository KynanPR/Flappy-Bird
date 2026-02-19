#pragma once
#include "PipeManager.h"
#include "Player.h"
class ScoreManager
{

public:
	ScoreManager();
	int updateScore(PipeManager & pipeManager, Player player);

private:
	int score = 0;
};

