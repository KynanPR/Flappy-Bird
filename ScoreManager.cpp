#include "ScoreManager.h"

ScoreManager::ScoreManager() {}

int ScoreManager::updateScore(PipeManager& pipeManager, Player player,sf::Sound &pointSFX) {
  float playerX = player.getPosition().x;
  auto pipes = pipeManager.getPipes();
  int amountOfPipes = pipeManager.getAmountOfPipes();
  for (int loopcounter = 0; loopcounter < amountOfPipes; loopcounter++) {
    if (pipes[loopcounter].getHasScore() &&
        pipes[loopcounter].getPosition().x < playerX) {
      m_score++;
	  pointSFX.play();
      pipes[loopcounter].setHasScore(false);
    }
  }

  // Update highscore if it's now beaten
  if (m_score > m_highscore)
    m_highscore = m_score;

  return m_score;
}

void ScoreManager::updateScoreDisplay(Text& scoreTextDisplay) {
  std::string newScoreText = m_baseScoreText + std::to_string(m_score);
  scoreTextDisplay.setText(newScoreText);
}

void ScoreManager::updateHighscoreDisplay(Text& highscoreTextDisplay) {
  std::string newHighscoreText =
      m_baseHighscoreText + std::to_string(m_highscore);
  highscoreTextDisplay.setText(newHighscoreText);
}
