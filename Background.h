#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

/*
    Background
    ----------

    How it works:
      - "current" layer is the background you're seeing now.
      - "next" layer is the new background (only used during transitions).
      - During a transition, current fades out while next fades in.
*/
class Background {
public:
    Background() = default;

    /*
        init()
        ------
        Call this once after:
          - your window exists (so we know window size)
          - your background textures are loaded
    */
    void init(sf::Vector2u windowSize,
        const std::vector<sf::Texture*>& textures,
        float scrollSpeedPxPerSec = 80.f);

    /*
        update()
        --------
        Call every frame (during gameplay).
        dt    = time since last frame (seconds)
        score = current player score (used to decide when to transition)
    */
    void update(float dt, int score);

    /*
        draw()
        ------
        Draws the background layers.
        Call this BEFORE drawing pipes, player, UI, etc.
    */
    void draw(sf::RenderTarget& target);

    /*
        reset()
        -------
        Call when restarting the game.
        Puts background back to first texture and resets the scroll/transition.
    */
    void reset();

    void setTransitionDuration(float seconds) { transitionDuration = seconds; }
    void setScoreStep(int step) { scoreStep = step; } // change every N points

private:
    /*
        Layer
        -----
        A Layer is one repeating scrolling texture:
          - sprite "a" and sprite "b" are placed side-by-side.
          - when one moves completely off-screen, it jumps to the right again.
    */
    struct Layer {
        const sf::Texture* texture = nullptr;  // pointer to an existing texture
        sf::Sprite a, b;                       // the two sprites used for tiling

        float scaleX = 1.f;                    // scaling to match window width
        float scaleY = 1.f;                    // scaling to match window height

       
        void set(const sf::Texture& tex, sf::Vector2u winSize);

        
        void setAlpha(sf::Uint8 alpha);

       
        void setX(float xA, float xB);

       
        void update(float dt, float speed);

       
        void draw(sf::RenderTarget& target) const;

        float width() const;
    };

private:
    // Start cross-fading to a specific background index
    void beginTransitionToIndex(std::size_t idx);

    // Decide which background index to use based on current score
    std::size_t pickIndexForScore(int score) const;

private:
    sf::Vector2u winSize{};         // window size in pixels
    float speed = 80.f;             // scrolling speed in pixels/sec

    
    std::vector<sf::Texture*> bgTextures;

    Layer current;                  
    Layer next;                   

    bool transitioning = false;     
    float t = 0.f;                  // time elapsed in the transition
    float transitionDuration = 1.0f;

    int scoreStep = 10;             // change background every 10 points by default
    std::size_t currentIndex = 0;   
    std::size_t pendingIndex = 0;   
};
