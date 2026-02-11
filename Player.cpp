#include "Player.h"

Player::Player() : GameObject(PLAYER_TEX_PATH)
{
	m_position = m_startingPosition;
	m_sprite.setPosition({100.f, 100.f});
	m_sprite.setScale({ 3.f, 3.f });
}

void Player::update(bool isFlapping, sf::Time deltaTime)
{
	if (m_flapFrameCounter <= m_flapFrames && m_flapFrameCounter > 0) {
		// Apply accel
		float accel = m_flapAccel * ((1 / m_flapFrameCounter));
		m_velocity.y -= accel * deltaTime.asSeconds();

		m_flapFrameCounter--;
	}

	if (isFlapping && !m_isFlappedLastFrame) {
		// Reset velocity
		m_velocity.y = 0;

		// Apply accel
		m_velocity.y -= m_flapAccel * deltaTime.asSeconds();

		m_isFlappedLastFrame = true;
		m_flapFrameCounter = m_flapFrames;
	}
	else {
	// Apply gravity
	m_velocity.y += m_gravityAccel * deltaTime.asSeconds();
	}

	// Reset flapping tracker
	if (!isFlapping && m_isFlappedLastFrame) {
		m_isFlappedLastFrame = false;
	}

	// Cap velocity
	if (m_velocity.y > m_terminalVel) {
		m_velocity.y = m_terminalVel;
	}

	// Apply the velocity
	m_sprite.move(m_velocity);

}

