#pragma once
#include "SFML/Graphics.hpp"
#include "Utils.h"

class GameObject
{
protected:
	sf::Vector2f m_scale;
	sf::Texture m_baseTexture;
	sf::Sprite m_sprite;

public:
	GameObject(std::string texturePath);

	sf::Vector2f GetPosition() { return m_sprite.getPosition(); }
	sf::Vector2f SetPosition(const sf::Vector2f& newPosition) {
		m_sprite.setPosition(newPosition);
		return m_sprite.getPosition();
	}
};

