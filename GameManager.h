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
	void initText();
	void updateGame();
	void pollEvents();
	void renderGame();
	void renderText();
	

	// game vairables
	sf::RenderWindow window;
	sf::Clock gameClock;
	sf::VideoMode videoMode;
	sf::Vector2u windowSize;
	const std::string windowTitle = "Flappy Bird";
	sf::Time deltaTime;
	sf::Event event;
	enum GameState { Startscreen, Playing, GameOver }; GameState currentGameState = Playing;
	sf::Text startSceenText; 
	sf::Text titleText;
	sf::Text gameOverText;
	sf::Font gameFont;
	const std::string fontPath = "assets/Font/Pixellettersfull-BnJ5.ttf";
	const std::string startScreenTextString = "Press Space to start";
	const std::string gameOverTextString = "Game Over!";
	const int startScreenCharacterSize = 50;
	const int titleCharacterSize = 100;
	const int gameOverCharacterSize = 200;
	const std::string title = "FLAPPY BIRD";
	const float titleYOffset = 200.f;
	bool isTheGameOver = false;
	


	// game objects
	Player player;
	Background background;
	PipeManager pipeManager;
	InputManager inputManager;

};

