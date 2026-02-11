#pragma once
#include <SFML/Graphics.hpp>
class InputManager
{
public:
	InputManager();
	//public functions
	void updateInput();
	bool getPlayerMoveUp() { return playerMoveUp; }
	

private:
	bool playerMoveUp = false;

};

