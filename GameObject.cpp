#include "GameObject.h"

GameObject::GameObject(std::string texturePath) : m_sprite(m_baseTexture) {
  LoadTexture(texturePath, m_baseTexture);
  m_sprite.setTexture(m_baseTexture);
}
