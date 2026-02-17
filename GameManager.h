#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Background.h"

class GameManager
{
public:
    GameManager();
    void run();

private:
    void update(float dt);
    void render();
    void loadAssets();

private:
    sf::RenderWindow window;
    sf::Clock clock;
    std::vector<sf::Texture> backgroundTextures;
    Background background;

    int score = 0;

    // test-only: automatically increases score once per second
    float scoreTimer = 0.f;
};
