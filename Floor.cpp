#include "Floor.h"

Floor::Floor() : GameObject(floorTexPath)
{
	sf::IntRect texRect = floorTexRect;
	m_sprite.setTextureRect(texRect);
	m_sprite.setOrigin(texRect.width / 2, texRect.height / 2);
	m_sprite.setPosition({ static_cast<float>(WINDOW_WIDTH / 2), static_cast<float>(WINDOW_HEIGHT - (texRect.height * 3) / 2) });
	m_sprite.setScale({ 2.f, 2.f });
}
