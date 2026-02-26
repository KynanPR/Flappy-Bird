#pragma once
#include "PipeManager.h"
#include "Player.h"
#include "SFML/Audio.hpp"
#include "Text.h"

class ScoreManager {
 public:
  ScoreManager();
  int updateScore(PipeManager& pipeManager, Player player, sf::Sound& pointSFX);
  void updateScoreDisplay(Text& scoreTextDisplay);
  void resetScore() { m_score = 0; }

  void updateHighscoreDisplay(Text& highscoreTextDisplay);

 private:
  int m_score = 0;
  const std::string m_baseScoreText = "Score: ";
  int m_highscore = 0;
  const std::string m_baseHighscoreText = "Highscore: ";
};
