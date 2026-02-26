#include "GameManager.h"

GameManager::GameManager() {
  initWindow();
  loadAssets();
  currentGameState = Startscreen;
}

void GameManager::run() {
  // function to run the game loop
  while (window.isOpen()) {
    deltaTime = gameClock.restart();
    pollEvents();
    if (currentGameState != Startscreen) {
      updateGame();
    }
    renderGame();
  }
}

void GameManager::initWindow() {
  windowSize = sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT);
  videoMode = sf::VideoMode(windowSize.x, windowSize.y);
  window.create(videoMode, windowTitleText,
                sf::Style::Close | sf::Style::Titlebar);
  // window.setFramerateLimit(60);
  // window.setVerticalSyncEnabled(true);
}

void GameManager::updateGame() {
  // update game here
  if (currentGameState == Playing) {
    inputManager.updateInput();
    background.update(deltaTime, score);
    // Pipe update here
    pipeManager.update(deltaTime);
  }
  player.update(inputManager.getPlayerMoveUp(), deltaTime,
                m_soundManager.getFlapSound());

  // check collision here and if it collides change the game to game over and
  // render the end screen
  if (currentGameState == Playing) {
    if (player.checkFloorCollision() || pipeManager.checkCollision(player)) {
      currentGameState = GameOver;

      if (!hasGameoverSoundPlayed) {
        m_soundManager.getGameOverSound().play();
        hasGameoverSoundPlayed = true;
      }
    }
  }
  updateScore();
  // isTheGameOver = player.checkFloorCollision() ||
  // pipeManager.checkCollision(player);
  if (currentGameState == GameOver) {
    inputManager.updateRestartGameInput();
    restartGame = inputManager.getRestartGame();
    if (restartGame) {
      resetGame();
    }
  }

  //// background scroll + transitions based on score
  // background.update(deltaTime, score);
}

void GameManager::resetGame() {
  currentGameState = Playing;
  player.resetPlayer();
  pipeManager.reset();
  isTheGameOver = false;
  scoreManager.resetScore();
  hasGameoverSoundPlayed = false;
}

void GameManager::pollEvents() {
  // poll events here
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed ||
        event.type == sf::Event::KeyPressed &&
            event.key.code == sf::Keyboard::Escape) {
      window.close();
    }
    if (currentGameState == Startscreen &&
        event.type == sf::Event::KeyPressed &&
        event.key.code == sf::Keyboard::Space) {
      currentGameState = Playing;
    }
  }
}

void GameManager::renderGame() {
  // clear window
  window.clear();
  // render background here
  background.draw(window);
  // draw objects here
  if (currentGameState == Playing || currentGameState == GameOver) {
    pipeManager.render(window);
    player.render(window);
    // player.renderTestHitbox(window);
    m_textManager.m_score.render(window);
    m_textManager.m_highscore.render(window);
  }
  if (currentGameState == Startscreen || currentGameState == GameOver) {
    renderText();
  }

  // display window contents
  window.display();
}

void GameManager::renderText() {
  if (currentGameState == Startscreen) {
    m_textManager.m_startScreen.render(window);
    m_textManager.m_title.render(window);
  }
  if (currentGameState == GameOver) {
    m_textManager.m_gameOver.render(window);
    m_textManager.m_restartGame.render(window);
  }
}

void GameManager::loadAssets() {
  std::vector<std::string> paths = {
      "assets/Background/Background1.png", "assets/Background/Background2.png",
      "assets/Background/Background3.png", "assets/Background/Background4.png",
      "assets/Background/Background5.png"};

  backgroundTextures.clear();

  for (const auto& path : paths) {
    sf::Texture tex;
    LoadTexture(path, tex);

    backgroundTextures.push_back(std::move(tex));
  }

  // Create vector of pointers
  std::vector<sf::Texture*> texturePtrs;
  for (auto& tex : backgroundTextures)
    texturePtrs.push_back(&tex);

  background.init(window.getSize(), texturePtrs);

  background.setScoreStep(5);
  background.setTransitionDuration(1.0f);
}

void GameManager::updateScore() {
  score = scoreManager.updateScore(pipeManager, player,
                                   m_soundManager.getScoreSound());
  scoreManager.updateScoreDisplay(m_textManager.m_score);
  scoreManager.updateHighscoreDisplay(m_textManager.m_highscore);
}
