#pragma once
#include "PipeObstacle.h"


class PipeManager
{
public:
	PipeManager();

	void update(sf::Time& deltaTime);
	
	void render(sf::RenderWindow& gameWindow);

	void movePipes(sf::Time& deltaTime);

	bool checkCollision(Player& player);

	void reset();

private:
	static const int m_pipeObstacleCount = 5;
	PipeObstacle m_pipes[m_pipeObstacleCount];

	// PipeObstacle Spawning/Respawning bits
	static constexpr float m_offscreenBuffer = 50.f;
	static constexpr int m_minPipeObstacleGap = 100;
	static constexpr int m_maxPipeObstacleGap = 800;
	static constexpr float m_xOffsetIncrement = static_cast<float>(WINDOW_WIDTH / m_pipeObstacleCount);
	void initPipeObstacle(PipeObstacle& pipe, float xOffset = 0);
	void recycleOffscreenPipes();

	// Pipes moving bits
	float m_pipeObstacleVelocity = 500.f;

	// Pipes collision checking bits
	

	static inline bool isPipeOffscreenLeft(PipeObstacle& pipe);
};

