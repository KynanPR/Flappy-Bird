#include "PipeManager.h"
#include <random>
#include <ctime>

PipeManager::PipeManager() 
{
	srand(static_cast<unsigned>(time(0)));
	rand();
	reset();
	
}

void PipeManager::update(sf::Time& deltaTime)
{
	movePipes(deltaTime);
	//recycleOffscreenPipes();
}

void PipeManager::render(sf::RenderWindow& gameWindow)
{
	for (PipeObstacle& pipe : m_pipes) {
		pipe.render(gameWindow);
	}
}

void PipeManager::initPipeObstacle(PipeObstacle& pipe, float xOffset)
 {
	// Double check it's not on screen
	//if (!isPipeOffscreenLeft(pipe)) return;

	// Set to be off right side of screen ready to scroll on
	float pipeX = static_cast<float>(WINDOW_WIDTH) + xOffset + m_offscreenBuffer;
	// Randomly set height & gap within range
	float pipeY = static_cast<float>(rand() % WINDOW_HEIGHT);
	int gapSize = (rand() % (m_maxPipeObstacleGap - m_minPipeObstacleGap)) + m_minPipeObstacleGap;
	pipe.setPosition({ pipeX, pipeY });
	pipe.setGapSize(gapSize);
	pipe.setHasScore(true);
}

void PipeManager::recycleOffscreenPipes()
{
	int recycledCounter = 0;
	for (PipeObstacle& pipe : m_pipes) {
		// Check if pipe is offscreen
		if (isPipeOffscreenLeft(pipe)) {
			// Recycle pipe, accounting for needed offset if we're recylcing more than one pipe
 			recycledCounter++;
			initPipeObstacle(pipe, recycledCounter * m_xOffsetIncrement);
		}
	}
}


// Moves each pipe in m_pipes left towards player

void PipeManager::movePipes(sf::Time& deltaTime)
{
	for (PipeObstacle& pipe : m_pipes) {
		// Move pipe
		float moveAmount = m_pipeObstacleVelocity * deltaTime.asSeconds();
		sf::Vector2f newPosition = pipe.move({ -moveAmount, 0 });

		if (isPipeOffscreenLeft(pipe)) {
			initPipeObstacle(pipe);
		}
		
	}
}

/*
Checks collision of player with all PipeObjects m_pipes
\returns true on first collision found
\returns false if no collision found
*/
bool PipeManager::checkCollision(Player& player)
{
	for (PipeObstacle& pipe : m_pipes)
	{
		if (pipe.checkCollision(player))
			return true;
	}
	return false;
}

void PipeManager::reset()
{
	for (int i = 0; i < m_pipeObstacleCount; i++)
	{
		initPipeObstacle(m_pipes[i], (i + 1) * m_xOffsetIncrement);
	}
}

inline bool PipeManager::isPipeOffscreenLeft(PipeObstacle& pipe)
{
	return pipe.getPosition().x <= (0.f - m_offscreenBuffer);
}
