#include "GameManager.h"
#include <string>
#include <iostream>
GameManager::GameManager()
{
    window.create(sf::VideoMode(800, 600), "Background Test");
    window.setFramerateLimit(60);

    loadAssets();
}

void GameManager::loadAssets()
{
    
    
        std::vector<std::string> paths = {
            "assets/Background/Background1.png",
            "assets/Background/Background2.png",
            "assets/Background/Background3.png",
            "assets/Background/Background4.png",
            "assets/Background/Background5.png",
            "assets/Background/Background6.png"
        };

        backgroundTextures.clear();

        for (const auto& path : paths)
        {
            sf::Texture tex;
            if (!tex.loadFromFile(path))
            {
                std::cout << "Failed to load: " << path << "\n";
                continue;
            }

            backgroundTextures.push_back(std::move(tex));
        }

        // Create vector of pointers
        std::vector<sf::Texture*> texturePtrs;
        for (auto& tex : backgroundTextures)
            texturePtrs.push_back(&tex);

        background.init(window.getSize(), texturePtrs, 80.f);

        background.setScoreStep(5);
        background.setTransitionDuration(1.0f);
    
}

void GameManager::run()
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float dt = clock.restart().asSeconds();

        update(dt);
        render();
    }
}

void GameManager::update(float dt)
{
    // Auto-increase score once per second (testing only)
    scoreTimer += dt;
    if (scoreTimer >= 1.0f)
    {
        scoreTimer -= 1.0f;
        score++;

        // show score in window title so you can see it change without fonts
        window.setTitle("Background Test - Score: " + std::to_string(score));
    }

    // background scroll + transitions based on score
    background.update(dt, score);
}

void GameManager::render()
{
    window.clear();
    background.draw(window);
    window.display();
}
