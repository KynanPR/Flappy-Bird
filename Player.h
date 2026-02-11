#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

static const std::string PLAYER_TEX_PATH= "assets/Player/StyleBird1/Bird1-7.png";

class Player : public GameObject
{
public:
	void update(bool isFlapping, sf::Time deltaTime);
	Player();

private:
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	bool m_isFlappedLastFrame = false;
	const sf::Vector2f m_startingPosition = { static_cast<float>(WINDOW_WIDTH / 5), static_cast<float>(WINDOW_HEIGHT / 2) };
	const float m_gravityAccel = 15.f;
	const float m_terminalVel = 8.f;

	const float m_flapAccel = 250.f;
	


};

