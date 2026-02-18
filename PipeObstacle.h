#pragma once
#include "Pipe.h"

class PipeObstacle
{
public:
	PipeObstacle();

	sf::Vector2f const getPosition() { return m_position; }
	// Set position of gap between top and bottom Pipe \returns new position
	sf::Vector2f setPosition(const sf::Vector2f& newPosition);
	// Overload of move to handle both pipes \returns new position
	sf::Vector2f move(const sf::Vector2f moveOffset);

	int const getGapSize() { return m_gapSize; }
	// Set size of gap between top and bottom Pipe \returns new gapSize
	int setGapSize(const int newGapSize);

	bool checkCollision(Player& player);

	// Overload of update to handle both pipes
	void update(sf::Time& deltaTime);
	// Overload of render to handle both pipes
	void render(sf::RenderWindow& gameWindow);

private:
	// Pipes
	Pipe m_topPipe;
	Pipe m_bottomPipe;

	sf::Vector2f m_position = { static_cast<float>(WINDOW_WIDTH / 2) , static_cast<float>(WINDOW_HEIGHT - 100)};
	int m_gapSize = 0; //WINDOW_HEIGHT / 5;

	// Set position of both pipes accounting for gap size
	void setPipesPositions();

};

