#include "GameManager.h"

GameManager::GameManager() {
  initWindow();
  loadAssets();
  initText();
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
  window.create(videoMode, windowTitle, sf::Style::Close | sf::Style::Titlebar);
  window.setFramerateLimit(60);
}

void GameManager::initText() {
  // Initalize the font
  gameFont.loadFromFile(fontPath);
  startScreenText.setFont(gameFont);
  titleText.setFont(gameFont);
  gameOverText.setFont(gameFont);
  restartGameText.setFont(gameFont);

  scoreText.setFont(gameFont);
  // Initalize the startscreen text and title
  startScreenText.setString(startScreenTextString);
  startScreenText.setCharacterSize(startScreenCharacterSize);
  startScreenText.setOutlineColor(sf::Color::Black);
  startScreenText.setOutlineThickness(3.f);
  startScreenText.setOrigin(startScreenText.getLocalBounds().width / 2,
                            startScreenText.getLocalBounds().height / 2);
  startScreenText.setPosition(static_cast<float>(windowSize.x / 2),
                              static_cast<float>(windowSize.y / 2));

  titleText.setString(title);
  titleText.setCharacterSize(titleCharacterSize);
  titleText.setOutlineColor(sf::Color::Black);
  titleText.setOutlineThickness(5.f);
  titleText.setOrigin(titleText.getLocalBounds().width / 2,
                      titleText.getLocalBounds().height / 2);
  titleText.setPosition(static_cast<float>(windowSize.x / 2),
                        static_cast<float>(windowSize.y / 2) - titleYOffset);

  // initalize the game over text
  gameOverText.setString(gameOverTextString);
  gameOverText.setCharacterSize(gameOverCharacterSize);
  gameOverText.setOrigin(gameOverText.getLocalBounds().width / 2,
                         gameOverText.getLocalBounds().height / 2);
  gameOverText.setOutlineColor(sf::Color::Black);
  gameOverText.setOutlineThickness(5.f);
  gameOverText.setPosition(
      static_cast<float>(windowSize.x / 2),
      static_cast<float>(windowSize.y / 5) - titleYOffset / 2);

  restartGameText.setString(restartGameTextString);
  restartGameText.setCharacterSize(startScreenCharacterSize);
  restartGameText.setOrigin(restartGameText.getLocalBounds().width / 2,
                            restartGameText.getLocalBounds().height / 2);
  restartGameText.setOutlineColor(sf::Color::Black);
  restartGameText.setOutlineThickness(3.f);
  restartGameText.setPosition(static_cast<float>(windowSize.x / 2),
                              static_cast<float>(windowSize.y / 2));

  // initalize the score text
  scoreText.setString(scoreTextString + std::to_string(score));
  scoreText.setCharacterSize(startScreenCharacterSize);
  scoreText.setOutlineColor(sf::Color::Black);
  scoreText.setOutlineThickness(3.f);
  scoreText.setOrigin(scoreText.getLocalBounds().width / 2,
                      scoreText.getLocalBounds().height / 2);
  scoreText.setPosition(scoreTextOffset);
}

void GameManager::updateGame() {
  // update game here
  if (currentGameState == Playing) {
    inputManager.updateInput();
    background.update(deltaTime, score);
    // Pipe update here
    pipeManager.update(deltaTime);
  }
  player.update(inputManager.getPlayerMoveUp(), deltaTime);

  // check collision here and if it collides change the game to game over and
  // render the end screen
  if (player.checkFloorCollision()) {
    currentGameState = GameOver;
  }
  if (pipeManager.checkCollision(player)) {
    currentGameState = GameOver;
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
    window.draw(scoreText);
  }
  if (currentGameState == Startscreen || currentGameState == GameOver) {
    renderText();
  }

  // display window contents
  window.display();
}

void GameManager::renderText() {
  if (currentGameState == Startscreen) {
    window.draw(startScreenText);
    window.draw(titleText);
  }
  if (currentGameState == GameOver) {
    window.draw(gameOverText);
    window.draw(restartGameText);
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
  score = scoreManager.updateScore(pipeManager, player);
  scoreText.setString(scoreTextString + std::to_string(score));
}
