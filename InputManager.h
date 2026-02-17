#pragma once
#include <SFML/Graphics.hpp>
class InputManager
{
public:
	InputManager();
	//public functions
	void updateInput();
	void updateRestartGameInput();
	bool getPlayerMoveUp() { return playerMoveUp; }
	bool getRestartGame() { return playerRestartGame; }

private:
	bool playerMoveUp = false;
	bool playerRestartGame = false;
};

