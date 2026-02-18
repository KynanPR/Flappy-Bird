#include "Pipe.h"

Pipe::Pipe(bool isDownFacing) : GameObject(PIPE_TEX_PATH)
{
	sf::IntRect texRect = m_sprite.getTextureRect();
	texRect.width = PIPE_TEX_SIZE.x;
	texRect.height = PIPE_TEX_SIZE.y;
	m_sprite.setTextureRect(texRect);
	m_sprite.setScale({ 3.f, 3.f });
	m_sprite.setOrigin({ static_cast<float>(texRect.width) / 2.f, 0.f }); // top middle

	// Setup direction bits
	if (isDownFacing) {
		m_sprite.rotate(180);
	}
}

bool Pipe::checkCollision(Player& player)
{
	return false;
}
