#pragma once
#include<SFML/Graphics.hpp>
#include "Player.h"
#include"Background.h"
#include "PipeManager.h"

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
	const int windowWidth = 1280, windowHeight = 720;
	const std::string windowTitle = "Flappy Bird";
	sf::Time deltaTime;
	sf::Event event;

	// game objects
	Player player;
	Background background;
	PipeManager pipeManager;

};

