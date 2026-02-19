#include "TextManager.h"

TextManager::TextManager()
    : m_startScreen(m_smallCharSize),
      m_title(m_mediumCharSize),
      m_gameOver(m_largeCharSize),
      m_restartGame(m_smallCharSize),
      m_score(m_smallCharSize, 5, left),
      m_highscore(m_smallCharSize, 5, left) {
  // Load Font
  m_gameFont.loadFromFile(m_gameFontPath);

  // Start Screen
  m_startScreen.setFont(m_gameFont);
  m_startScreen.setText(m_startScreenText);
  m_startScreen.setPosition(m_centerPosition);
  // Title
  m_title.setFont(m_gameFont);
  m_title.setText(m_titleText);
  m_title.setPosition(m_titlePosition);
  // GameOver
  m_gameOver.setFont(m_gameFont);
  m_gameOver.setText(m_gameOverText);
  m_gameOver.setPosition(
      {static_cast<float>(WINDOW_WIDTH) / 2.f,
       static_cast<float>(WINDOW_HEIGHT) / 5.f - m_titleOffsetY / 2.f});
  // RestartGame
  m_restartGame.setFont(m_gameFont);
  m_restartGame.setText(m_restartGameText);
  m_restartGame.setPosition(m_centerPosition);
  // Score
  m_score.setFont(m_gameFont);
  m_score.setPosition(m_scorePosition);
  // Highscore
  m_highscore.setFont(m_gameFont);
  m_highscore.setPosition(m_highscorePosition);
}
