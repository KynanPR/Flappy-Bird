#include "GameManager.h"
#include <string>

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

    background.init(window.getSize(), paths, 80.f);

    // Change these values however you want:
    background.setScoreStep(5);            // switch every 5 score (easy to test)
    background.setTransitionDuration(1.0f); // 1 second fade
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
