#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Pipe.h"
#include "SFML/Audio.hpp"
static const std::string PLAYER_TEX_PATH =
    "assets/Player/StyleBird1/Bird1-7.png";
static const sf::Vector2i PLAYER_TEX_SIZE = {16, 16};

class Pipe;

class Player : public GameObject {
 public:
  void update(bool isFlapping, sf::Time& deltaTime, sf::Sound& flapSFX);
  Player();
  bool checkFloorCollision();
  void resetPlayer();
  bool checkCollision(Pipe& pipe, const bool isTopPipe);
  void renderTestHitbox(sf::RenderWindow& window);
  void flapAnimation(bool isFlapping, sf::Time dt);

 private:
  sf::Vector2f m_position;
  sf::Vector2f m_velocity;
  sf::Vector2f prevPosition;
  sf::CircleShape m_collisionCircle;
  sf::IntRect m_animationRect;

  // int m_flapFrames = 100;
  // int m_flapFrameCounter = 1;
  const float m_flapDuration = 0.167f;  // 167.f;
  float m_flapElapsed = 0.000f;
  bool m_isFlappedLastFrame = true;
  bool m_isAnimatingFlap = false;
  const sf::Vector2f m_startingPosition = {
      static_cast<float>(WINDOW_WIDTH / 5),
      static_cast<float>(WINDOW_HEIGHT / 2)};
  const float m_gravityAccel = 5.f;
  const float m_terminalGrav = 750.f;
  const float m_gravDuration = 1.f;
  const float m_gravTotalDeltaVel = 1350.f;
  const float m_flapAccel = 70.f;
  const float m_flapEaseCoefficient = 2.f;  // 0.3f;
  const float m_flapAccelCap = 350.f;
  const float m_flapMaxVel = 750.f;
  const float m_flapTotalDeltaVel = 1650.f;
  const float m_animationSpeed = 0.1f;
  float m_animationTimer = 0.f;
  const float m_rotationSpeed = 4.f;
  const float m_flapRotation = -45.f;
  const float m_maxDownwardsRotation = 90.f;
};
