#pragma once
#include "SFML/Graphics.hpp"
#include "Utils.h"

class GameObject
{
public:
	GameObject(std::string texturePath);

	// Get current position of GameObject's sprite
	sf::Vector2f getPosition() { return m_sprite.getPosition(); }
	// Set position of GameObject's sprite \return new position
	sf::Vector2f setPosition(const sf::Vector2f& newPosition) {
		m_sprite.setPosition(newPosition);
		return m_sprite.getPosition();
	}
	sf::Vector2f move(const sf::Vector2f& moveOffset) {
		m_sprite.move(moveOffset);
		return m_sprite.getPosition();
	}

	void render(sf::RenderWindow &window) {
		window.draw(m_sprite);
	}



protected:
	sf::Vector2f m_scale;
	sf::Texture m_baseTexture;
	sf::Sprite m_sprite;

};

