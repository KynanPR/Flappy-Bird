#pragma once
#include "Pipes.h"

class PipeManager
{
public:
	PipeManager();

	void update(sf::Time& deltaTime);
	
	void render(sf::RenderWindow& window);
	
private:
	Pipes m_testPipes;

	float m_moveAmount = 80.f;
};

