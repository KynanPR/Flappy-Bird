#include "Player.h"

#include <iostream>

Player::Player() : GameObject(PLAYER_TEX_PATH) {
  m_position = m_startingPosition;
  sf::IntRect texRect = m_sprite.getTextureRect();
  m_sprite.setOrigin({static_cast<float>(texRect.width) / 2.f},
                     static_cast<float>(texRect.height) / 2.f);
  m_sprite.setPosition(m_position);
  texRect.width = PLAYER_TEX_SIZE.x;
  texRect.height = PLAYER_TEX_SIZE.y;
  m_sprite.setTextureRect(texRect);
  m_sprite.setOrigin(static_cast<float>(texRect.width / 2),
                     static_cast<float>(texRect.height / 2));
  m_sprite.setPosition({100.f, 100.f});
  m_sprite.setScale({3.f, 3.f});
  // make collision circle slightly smaller than the bird for gameplay reasons
  m_collisionCircle.setRadius(PLAYER_TEX_SIZE.x * 3.f / 2.5);
  m_collisionCircle.setOrigin(m_collisionCircle.getRadius(),
                              m_collisionCircle.getRadius());
  m_collisionCircle.setPosition(m_sprite.getPosition());
  m_collisionCircle.setFillColor(sf::Color::Red);
  m_animationRect = m_sprite.getTextureRect();
}

bool Player::checkFloorCollision() {
  return (m_sprite.getPosition().y >=
          WINDOW_HEIGHT - (m_sprite.getGlobalBounds().height / 2));
}

void Player::resetPlayer() {
  m_position = m_startingPosition;
  m_velocity = {0.f, 0.f};
  m_sprite.setPosition(m_position);
  m_sprite.setRotation(0.f);
}

bool Player::checkCollision(Pipe& pipe, const bool isTopPipe) {
  // Pipe
  sf::Vector2f pipePos = pipe.getPosition();
  sf::FloatRect pipeBounds = pipe.getGlobalBounds();
  // Player
  sf::Vector2f playerPos = m_collisionCircle.getPosition();
  float playerRadius = m_collisionCircle.getRadius();

  sf::Vector2f distance = pipePos - playerPos;
  float radiusSumWidth = m_collisionCircle.getRadius() + pipeBounds.width / 2;

  // Check if in width bounds
  bool isWidthCollide = std::abs(distance.x) <= radiusSumWidth;

  // Check if in height bounds accounting for top vs bottom pipe
  bool isHeightCollide = false;
  if (isTopPipe) {
    isHeightCollide =
        playerPos.y - playerRadius <= pipeBounds.top + pipeBounds.height;
  } else {
    isHeightCollide = playerPos.y + playerRadius >= pipeBounds.top;
  }

  // Only colliding if in both width and height bounds
  return isWidthCollide && isHeightCollide;
}

void Player::renderTestHitbox(sf::RenderWindow& window) {
  window.draw(m_collisionCircle);
}

void Player::flapAnimation(bool isFlapping, sf::Time deltaTime)
{
    // increase the animation timer using delta time 
    m_animationTimer += deltaTime.asSeconds();
    // if the bird is flapping 
    if (m_flapFrameCounter == m_flapFrames - 1)
    {
		// reset the animation frame to the first 
		m_animationRect = sf::IntRect{ 0,0 , PLAYER_TEX_SIZE.x, PLAYER_TEX_SIZE.y };
		// and set the bool to true to start the animation
		m_isAnimatingFlap = true;
    }
    // if the animation timer has reached the animation speed and the bird is animating
    if (m_isAnimatingFlap && m_animationTimer >= m_animationSpeed)
    {
		// move to the next frame and reset the timer
        m_animationRect.left += PLAYER_TEX_SIZE.x;
		m_animationTimer = 0.f;
    }
	// if you reach the end of the animation frames reset back to the first frame and stop animating
    if (m_animationRect.left >= PLAYER_TEX_SIZE.x * 3)
    {
        m_animationRect.left = 0;
		m_isAnimatingFlap = false;
    }
	// set the texture rect to the current animation frame
	m_sprite.setTextureRect(m_animationRect);
}

void Player::update(bool isFlapping, sf::Time& deltaTime) {
  // Start flapping

  if (isFlapping && !m_isFlappedLastFrame) {
    m_isFlappedLastFrame = true;
    m_flapFrameCounter = m_flapFrames;
  }

  // Continue flap
  if (m_flapFrameCounter <= m_flapFrames && m_flapFrameCounter > 0) {
    // Apply accel
    float easeOut = static_cast<float>(
        1 - std::pow(2, m_flapFrameCounter *
                            -m_flapEaseCoefficient));  // Exponential ease out
    float accel = m_flapAccel * easeOut;
    // accel = std::min(accel, m_flapAccelCap);
    m_velocity.y -= accel * deltaTime.asSeconds();

    m_flapFrameCounter--;
  } else {
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
  } else if (m_velocity.y < -m_flapMaxVel) {
    m_velocity.y = -m_flapMaxVel;
  }

  // Apply the velocity
  m_sprite.move(m_velocity);
  m_collisionCircle.setPosition(m_sprite.getPosition());
  flapAnimation(isFlapping, deltaTime);
  //rotation based on velocity
  float targetRotation = 0.f;

  if (m_velocity.y < 0.f) {
    m_sprite.setRotation(m_flapRotation);  // snap upward
  } else {
    // calculates the target rotation based on velocity.
    // first calculate the ratio of current velocity to terminal velocity
    float terminalVelocityRatio = m_velocity.y / m_terminalGrav;
    if (terminalVelocityRatio < 0) {
      terminalVelocityRatio = 0;  // 0 velocity would be a 0 degree rotation
    } else if (terminalVelocityRatio > 1) {
      terminalVelocityRatio = 1;  // 1 or above would be a 90 degree rotation
    }
    // multiply the ratio by the max downwards rotation to get the target
    // rotation
    targetRotation = terminalVelocityRatio * m_maxDownwardsRotation;
  }
  float currentRotation = m_sprite.getRotation();
  // convert to -180 to 180 range
  if (currentRotation > 180.f) {
    currentRotation -= 360.f;
  } else if (currentRotation < -180.f) {
    currentRotation += 360.f;
  }

  // find the diffrence between the current and target rotation, and convert to
  // -180 to 180 range
  float rotationDifference = targetRotation - currentRotation;
  if (rotationDifference > 180.f) {
    targetRotation -= 360.f;
  } else if (rotationDifference < -180.f) {
    targetRotation += 360.f;
  }
  // calculate the new rotation based on the rotation difference, a speed
  // factor, and delta time
  float newRotation = currentRotation + rotationDifference * m_rotationSpeed *
                                            deltaTime.asSeconds();
  m_sprite.setRotation(newRotation);

  // Don't go off bottom of screen
  sf::Vector2f currentPos = m_sprite.getPosition();
  float maxAllowablePos =
      WINDOW_HEIGHT - (m_sprite.getGlobalBounds().height / 2);
  m_sprite.setPosition(currentPos.x, std::min(currentPos.y, maxAllowablePos));
}
