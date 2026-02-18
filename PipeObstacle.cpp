#include "PipeObstacle.h"

PipeObstacle::PipeObstacle() : m_topPipe(true), m_bottomPipe()
{
	
}

sf::Vector2f PipeObstacle::setPosition(const sf::Vector2f& newPosition)
{
	//TODO maybe add checks for valid on screen centre

	m_position = newPosition;
	setPipesPositions();
	
	return m_position;
}

int PipeObstacle::setGapSize(const int newGapSize)
{
	m_gapSize = newGapSize;
	setPipesPositions();

	return m_gapSize;

}

bool PipeObstacle::checkCollision(Player& player)
{
	return (m_topPipe.checkCollision(player) || m_bottomPipe.checkCollision(player));
}

sf::Vector2f PipeObstacle::move(const sf::Vector2f moveOffset)
{
	sf::Vector2f oldPos = getPosition();
	sf::Vector2f newPos;
	newPos.x = oldPos.x + moveOffset.x;
	newPos.y = oldPos.y + moveOffset.y;

	setPosition(newPos);
	return newPos;
}

void PipeObstacle::update(sf::Time& deltaTime)
{

}

void PipeObstacle::render(sf::RenderWindow& gameWindow)
{
	m_topPipe.render(gameWindow);
	m_bottomPipe.render(gameWindow);
}

void PipeObstacle::setPipesPositions()
{
	m_topPipe.setPosition({ m_position.x, m_position.y - (m_gapSize / 2) });
	m_bottomPipe.setPosition({ m_position.x, m_position.y + (m_gapSize / 2) });
}
