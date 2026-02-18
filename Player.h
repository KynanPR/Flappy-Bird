#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

static const std::string PLAYER_TEX_PATH= "assets/Player/StyleBird1/Bird1-7.png";
static const sf::Vector2i PLAYER_TEX_SIZE = { 16, 16 };

class Player : public GameObject
{
public:
	void update(bool isFlapping, sf::Time& deltaTime);
	Player();
	
	bool checkFloorCollision();
	void resetPlayer();
private:
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2f prevPosition;

	int m_flapFrames = 10;
	int m_flapFrameCounter = 1;
	bool m_isFlappedLastFrame = true;
	const sf::Vector2f m_startingPosition = { static_cast<float>(WINDOW_WIDTH / 5), static_cast<float>(WINDOW_HEIGHT / 2) };
	const float m_gravityAccel = 75.f;
	const float m_terminalGrav = 10.f;
	const float m_flapAccel = 250.f;
	const float m_flapEaseCoefficient = 0.3f;
	const float m_flapAccelCap = 250.f;
	const float m_flapMaxVel = 10.f;

	const float m_rotationSpeed = 4.f;
	const float m_flapRotation = -45.f;
	const float m_maxDownwardsRotation = 90.f;


};

