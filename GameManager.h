#pragma once
#include <SFML/Graphics.hpp>
#include "Background.h"
#include "InputManager.h"
#include "PipeManager.h"
#include "Player.h"
#include "ScoreManager.h"
#include "SoundManager.h"
#include "TextManager.h"
#include "Utils.h"

#include <iostream>
#include <string>
#include <vector>

class GameManager {
 public:
  GameManager();
  // public functions
  void run();

 private:
  // private functions
  void initWindow();
  void updateGame();
  void resetGame();
  void pollEvents();
  void renderGame();
  void renderText();
  void loadAssets();
  void updateScore();

  // game vairables
  sf::RenderWindow window;
  sf::Clock gameClock;
  sf::VideoMode videoMode;
  sf::Vector2u windowSize;
  sf::Time deltaTime;
  sf::Event event;
  enum GameState { Startscreen, Playing, GameOver };
  GameState currentGameState;
  bool isTheGameOver = false;
  bool restartGame = false;
  bool hasGameoverSoundPlayed = false;
  int score = 0;

  std::vector<sf::Texture> backgroundTextures;

  const std::string windowTitleText = "Flappy Bird";

  // game objects
  Player player;
  Background background;
  PipeManager pipeManager;
  InputManager inputManager;
  ScoreManager scoreManager;
  TextManager m_textManager;
  SoundManager m_soundManager;
};
