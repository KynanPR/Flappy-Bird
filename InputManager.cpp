#include "InputManager.h"

InputManager::InputManager() {}

void InputManager::updateInput() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) ||
      sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    playerMoveUp = true;
  } else {
    playerMoveUp = false;
  }
}

void InputManager::updateRestartGameInput() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
    playerRestartGame = true;
  } else {
    playerRestartGame = false;
  }
}
