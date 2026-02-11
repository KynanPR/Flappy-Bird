#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

class Player : public GameObject
{
public:
	void update(bool isFlapping, sf::Time deltaTime);
	const std::string m_playerTexPath = "assets/Player/StyleBird1/Bird1-7.png";
	Player();

private:
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	bool m_isFlappedLastFrame;
	const sf::Vector2f m_startingPosition = { static_cast<float>(WINDOW_WIDTH / 5), static_cast<float>(WINDOW_HEIGHT / 2) };
	const float m_gravityAccel = 100.f;
	const float m_terminalVel = 100.f;

	const float m_flapAccel = 100.f;
	


};

