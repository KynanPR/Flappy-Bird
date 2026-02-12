#include "GameManager.h"

GameManager::GameManager()
{
	initWindow();
	initText();
	currentGameState = Startscreen;
}

void GameManager::run()
{
	// function to run the game loop
	while (window.isOpen())
	{
		
		deltaTime = gameClock.restart();
		pollEvents();
		if (currentGameState == Playing)
		{
			updateGame();
		}
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

void GameManager::initText()
{
	// Initalize the font
	gameFont.loadFromFile(fontPath);
	startSceenText.setFont(gameFont);
	titleText.setFont(gameFont);
	gameOverText.setFont(gameFont);
	// Initalize the startscreen text and title
	startSceenText.setString(startScreenTextString);
	startSceenText.setCharacterSize(startScreenCharacterSize);
	startSceenText.setOrigin(startSceenText.getLocalBounds().width / 2, startSceenText.getLocalBounds().height / 2); 
	startSceenText.setPosition(static_cast<float>(windowSize.x / 2), static_cast<float>( windowSize.y / 2));

	titleText.setString(title);
	titleText.setCharacterSize(titleCharacterSize);
	titleText.setOrigin(titleText.getLocalBounds().width / 2, titleText.getLocalBounds().height / 2);
	titleText.setPosition(static_cast<float>(windowSize.x / 2) , static_cast<float>(windowSize.y / 2) - titleYOffset);
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
		if (currentGameState == Startscreen && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
		{
			currentGameState = Playing;
		}
	}
}

void GameManager::renderGame()
{
	// clear window
	window.clear();

	// draw objects here
	if (currentGameState == Startscreen || currentGameState == GameOver)
	{
		renderText();
	}
	else if (currentGameState == Playing)
	{
		player.render(window);
	}
	

	// display window contents
	window.display();
}

void GameManager::renderText()
{
	if (currentGameState == Startscreen)
	{
		window.draw(startSceenText);
		window.draw(titleText);
	}
	if (currentGameState == GameOver)
	{
		window.draw(gameOverText);
	}
}