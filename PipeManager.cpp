#include "PipeManager.h"

PipeManager::PipeManager(): m_testPipes()
{
}

void PipeManager::update(sf::Time& deltaTime)
{
	m_testPipes.move({ -m_moveAmount * deltaTime.asSeconds(), 0.f});
}

void PipeManager::render(sf::RenderWindow& window)
{
	m_testPipes.render(window);
}
