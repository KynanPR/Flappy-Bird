#pragma once
#include <SFML/Graphics.hpp>
#include <string>

bool LoadTexture(const std::string& texPath, sf::Texture& tex);

static const unsigned WINDOW_WIDTH = 1280;
static const unsigned WINDOW_HEIGHT = 720;
