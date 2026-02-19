#pragma once
#include<SFML/Graphics.hpp>
#include "Utils.h"
#include "Player.h"
#include"Background.h"
#include "PipeManager.h"
#include "InputManager.h"
#include "ScoreManager.h"

#include <iostream>
#include <vector>
#include <string>


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
	void resetGame();
	void pollEvents();
	void renderGame();
	void renderText();
	void loadAssets();
	void updateScore();
	

	// game vairables
	sf::RenderWindow window;
	sf::Clock gameClock;
	sf::VideoMode videoMode;
	sf::Vector2u windowSize;
	sf::Time deltaTime;
	sf::Event event;
	enum GameState { Startscreen, Playing, GameOver };
	GameState currentGameState;
	bool isTheGameOver = false;
	bool restartGame = false;

	// Text vars
	const std::string windowTitle = "Flappy Bird";
	sf::Text startSceenText; 
	sf::Text titleText;
	sf::Text gameOverText;
	sf::Text restartGameText;
	sf::Text scoreText;
	sf::Font gameFont;
	const std::string fontPath = "assets/Font/Pixellettersfull-BnJ5.ttf";
	const std::string startScreenTextString = "Press Space to start";
	const std::string gameOverTextString = "Game Over!";
	const std::string restartGameTextString = "Press R to Restart";
	const std::string scoreTextString = "Score: ";
	const int startScreenCharacterSize = 50;
	const int titleCharacterSize = 100;
	const int gameOverCharacterSize = 200;
	int score = 0;
	const std::string title = "FLAPPY BIRD";
	const float titleYOffset = 200.f;
	const sf::Vector2f scoreTextOffset = { 100.f, 10.f };
	std::vector<sf::Texture> backgroundTextures;

	// game objects
	Player player;
	Background background;
	PipeManager pipeManager;
	InputManager inputManager;
	ScoreManager scoreManager;
};
