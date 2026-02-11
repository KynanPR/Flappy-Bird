#include "GameManager.h"

GameManager::GameManager()
{
	initWindow();
}

void GameManager::run()
{
	// function to run the game loop
	while (window.isOpen())
	{
		deltaTime = gameClock.restart();
		pollEvents();
		updateGame();
		renderGame();
	}
}

void GameManager::initWindow()
{
	windowSize = sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT);
	videoMode = sf::VideoMode(windowSize.x, windowSize.y);
	window.create(videoMode, windowTitle, sf::Style::Close | sf::Style::Titlebar);
	window.setVerticalSyncEnabled(true);

}

void GameManager::updateGame()
{
	// update game here
	inputManager.updateInput();
	player.update(inputManager.getPlayerMoveUp(), deltaTime);
}

void GameManager::pollEvents()
{
	// poll events here
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		{
			window.close();
		}
	}
}

void GameManager::renderGame()
{
	// clear window
	window.clear();

	// draw objects here
	player.render(window);

	// display window contents
	window.display();
}
