#include "Utils.h"
#include <iostream>

bool LoadTexture(const std::string& texPath, sf::Texture& tex)
{
    if (!tex.loadFromFile(texPath))
    {
        std::cout << "Failed to load texture: " << texPath << "\n";
        return false;
    }
    return true;
}
