#pragma once
#include "PipeObstacle.h"

class PipeManager {
 public:
  PipeManager();

  void update(sf::Time& deltaTime);

  void render(sf::RenderWindow& gameWindow);

  void movePipes(sf::Time& deltaTime);

  bool checkCollision(Player& player);

  void reset();

 private:
  static const int m_pipeObstacleCount = 4;
  PipeObstacle m_pipes[m_pipeObstacleCount];

  // PipeObstacle Spawning/Respawning bits
  static constexpr float m_offscreenBuffer = 50.f;
  static constexpr int m_pipeObstacleGapMin = 200;
  static constexpr int m_pipeObstacleGapMax = 600;
  static constexpr float m_xOffsetIncrement =
      static_cast<float>(WINDOW_WIDTH / m_pipeObstacleCount);
  static constexpr int m_pipeObstacleSpawnHeightMin = WINDOW_HEIGHT / 5;
  static constexpr int m_pipeObstacleSpawnHeightMax =
      WINDOW_HEIGHT - m_pipeObstacleSpawnHeightMin;
  static constexpr float m_pipeObstacleHeightDifferenceMax = 500.f;
  float m_pipeObstacleLastSpawnHeight = 0.f;
  void initPipeObstacle(PipeObstacle& pipe, float xOffset = 0);
  void recycleOffscreenPipes();

  // Pipes moving bits
  float m_pipeObstacleVelocity = 450.f;

  // Pipes collision checking bits

  static inline bool isPipeOffscreenLeft(PipeObstacle& pipe);
};
