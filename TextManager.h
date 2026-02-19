#pragma once
#include "Text.h"
#include "Utils.h"

class TextManager {
 public:
  TextManager();

  Text m_startScreen;
  Text m_title;
  Text m_gameOver;
  Text m_restartGame;
  Text m_score;
  Text m_highscore;

 private:
  sf::Font m_gameFont;
  const std::string m_gameFontPath = "assets/Font/Pixellettersfull-BnJ5.ttf";

  static const int m_smallCharSize = 50;
  static const int m_mediumCharSize = 100;
  static const int m_largeCharSize = 200;
  const sf::Vector2f m_centerPosition = {
      static_cast<float>(WINDOW_WIDTH) / 2.f,
      static_cast<float>(WINDOW_HEIGHT) / 2.f};

  // Start Screen
  const std::string m_startScreenText = "Press Space to start";
  // Title
  const float m_titleOffsetY = 200.f;
  const sf::Vector2f m_titlePosition = {
      static_cast<float>(WINDOW_WIDTH) / 2.f,
      static_cast<float>(WINDOW_HEIGHT) / 2.f - m_titleOffsetY};
  const std::string m_titleText = "FLAPPY BIRD";
  // GameOver
  const std::string m_gameOverText = "Game Over!";
  const sf::Vector2f m_gameOverPosition = {
      static_cast<float>(WINDOW_WIDTH) / 2.f,
      static_cast<float>(WINDOW_HEIGHT) / 5.f - m_titleOffsetY / 2.f};
  // Restart
  const std::string m_restartGameText = "Press R to Restart";
  // Score
  const sf::Vector2f m_scorePosition = {10.f, 10.f};
  // Highscore
  const sf::Vector2f m_highscorePosition = {m_scorePosition.x,
                                            m_scorePosition.y + 50};
};
