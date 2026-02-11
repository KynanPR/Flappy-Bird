#include "Utils.h"

inline bool LoadTexture(const std::string texPath, sf::Texture& tex)
{

    if (tex.loadFromFile(texPath)) {
        tex.setSmooth(true);
        return true;
    }
    else {
        return false;
    }
    return false;
}
