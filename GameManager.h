#pragma once
#include<SFML/Graphics.hpp>
#include "Utils.h"
#include "Player.h"
#include"Background.h"
#include "PipeManager.h"
#include "InputManager.h"

class GameManager
{
public:
	GameManager();
	// public functions
	void run();


private:
	// private functions
	void initWindow();
	void updateGame();
	void pollEvents();
	void renderGame();


	// game vairables
	sf::RenderWindow window;
	sf::Clock gameClock;
	sf::VideoMode videoMode;
	sf::Vector2u windowSize;
	const std::string windowTitle = "Flappy Bird";
	sf::Time deltaTime;
	sf::Event event;

	// game objects
	Player player;
	Background background;
	PipeManager pipeManager;
	InputManager inputManager;

};

