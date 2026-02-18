#pragma once
#include <string>
#include <SFML/Graphics.hpp>


bool LoadTexture(const std::string &texPath, sf::Texture& tex);

static unsigned WINDOW_WIDTH = 1280;
static unsigned WINDOW_HEIGHT = 720;

bool LoadTexture(const std::string& texPath, sf::Texture& tex);
