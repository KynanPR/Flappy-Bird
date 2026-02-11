#include "Player.h"

Player::Player() : GameObject(m_playerTexPath)
{
	m_position = m_startingPosition;
}

void Player::update(bool isFlapping, sf::Time deltaTime)
{
	// Apply gravity
	m_velocity.y -= m_gravityAccel * deltaTime.asSeconds();

	if (isFlapping && !m_isFlappedLastFrame) {
		// Reset velocity
		m_velocity.y = 0;

		// Apply accel
		m_velocity.y += m_flapAccel * deltaTime.asSeconds();

		m_isFlappedLastFrame = true;
	}
	// Reset flapping
	else if (!isFlapping && m_isFlappedLastFrame) {
		m_isFlappedLastFrame = false;
	}

	// Cap velocity
	if (m_velocity.y > m_terminalVel) {
		m_velocity.y = m_terminalVel;
	}
	else if (m_velocity.y < -m_terminalVel)
	{
		m_velocity.y = -m_terminalVel;
	}

	// Apply the velocity
	m_sprite.move(m_velocity);

}

