#include "GameObject.h"

GameObject::GameObject(std::string texturePath) : m_sprite(m_baseTexture)
{
	LoadTexture(texturePath, m_baseTexture);
	m_sprite.setTexture(m_baseTexture);
	sf::IntRect texRect = m_sprite.getTextureRect();
	texRect.width = 16;
	texRect.height = 16;
	m_sprite.setTextureRect(texRect);
}
