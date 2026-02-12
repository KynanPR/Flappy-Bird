#include "Player.h"
#include <iostream>

Player::Player() : GameObject(PLAYER_TEX_PATH)
{
	m_position = m_startingPosition;
	sf::IntRect texRect = m_sprite.getTextureRect();
	m_sprite.setOrigin(texRect.width / 2, texRect.height / 2);
	m_sprite.setPosition({100.f, 100.f});
	m_sprite.setScale({ 3.f, 3.f });
}

bool Player::checkFloorCollision()
{
	
	return (m_sprite.getPosition().y >= WINDOW_HEIGHT - (m_sprite.getGlobalBounds().height / 2));

		std::cout << "Floor!" << std::endl;
		return true;
	}
	return false;
}

void Player::update(bool isFlapping, sf::Time deltaTime)
{
	// Start flapping
	if (isFlapping && !m_isFlappedLastFrame) {
		m_isFlappedLastFrame = true;
		m_flapFrameCounter = m_flapFrames;
	}
	if (m_flapFrameCounter <= m_flapFrames && m_flapFrameCounter > 0) {
		// Apply accel
		float easeOut = (1 - std::pow(2, m_flapFrameCounter * -m_flapEaseCoefficient)); // Exponential ease out
		float accel = m_flapAccel * easeOut;
		//accel = std::min(accel, m_flapAccelCap);
		m_velocity.y -= accel * deltaTime.asSeconds();

		m_flapFrameCounter--;
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
	if (m_velocity.y > m_terminalGrav) {
		m_velocity.y = m_terminalGrav;
	}
	else if (m_velocity.y < -m_flapMaxVel) {
		m_velocity.y = -m_flapMaxVel;
	}

	// Apply the velocity
	m_sprite.move(m_velocity);

	// Don't go off bottom of screen
	sf::Vector2f currentPos = m_sprite.getPosition();
	float maxAllowablePos =WINDOW_HEIGHT - (m_sprite.getGlobalBounds().height / 2) ;
	m_sprite.setPosition(currentPos.x, std::min(currentPos.y, maxAllowablePos));

}

