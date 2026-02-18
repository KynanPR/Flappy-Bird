#include "Background.h"
#include "Utils.h"
#include <algorithm>
#include <cmath>

static float clampf(float v, float lo, float hi)
{
    return std::max(lo, std::min(v, hi));
}

static float smoothstep(float x)
{
    x = clampf(x, 0.f, 1.f);
    return x * x * (3.f - 2.f * x);
}

// ---------- Layer ----------
void Background::Layer::set(const sf::Texture& tex, sf::Vector2u winSize)
{
    texture = &tex;

    a.setTexture(tex, true);
    b.setTexture(tex, true);

    const auto ts = tex.getSize();

    // Stretch to fill window (simple + common). If you want preserve aspect ratio, tell me.
    scaleX = static_cast<float>(winSize.x) / static_cast<float>(ts.x);
    scaleY = static_cast<float>(winSize.y) / static_cast<float>(ts.y);

    a.setScale(scaleX, scaleY);
    b.setScale(scaleX, scaleY);

    // place A then B immediately to its right
    a.setPosition(0.f, 0.f);
    b.setPosition(width(), 0.f);
}

float Background::Layer::width() const
{
    if (!texture) return 0.f;
    return static_cast<float>(texture->getSize().x) * scaleX;
}

void Background::Layer::setAlpha(sf::Uint8 alpha)
{
    auto ca = a.getColor(); ca.a = alpha; a.setColor(ca);
    auto cb = b.getColor(); cb.a = alpha; b.setColor(cb);
}

void Background::Layer::setX(float xA, float xB)
{
    a.setPosition(xA, 0.f);
    b.setPosition(xB, 0.f);
}

void Background::Layer::update(sf::Time& dt, float speed)
{
    if (!texture) return;

    const float dx = speed * dt.asSeconds();
    a.move(-dx, 0.f);
    b.move(-dx, 0.f);

    const float w = width();

    // seamless loop
    if (a.getPosition().x + w <= 0.f) a.setPosition(b.getPosition().x + w, 0.f);
    if (b.getPosition().x + w <= 0.f) b.setPosition(a.getPosition().x + w, 0.f);
}

void Background::Layer::draw(sf::RenderTarget& target) const
{
    if (!texture) return;
    target.draw(a);
    target.draw(b);
}

// ---------- Background ----------
void Background::init(sf::Vector2u windowSize,
    const std::vector<sf::Texture*>& textures,
    float scrollSpeedPxPerSec)
{
    winSize = windowSize;
    scrollSpeed = scrollSpeedPxPerSec;

    bgTextures = textures; 

    transitioning = false;
    t = 0.f;
    currentIndex = 0;
    pendingIndex = 0;

    if (!bgTextures.empty())
    {
        current.set(*bgTextures[0], winSize);
        current.setAlpha(255);
    }

    next.texture = nullptr;
    next.setAlpha(0);
}

std::size_t Background::pickIndexForScore(int score) const
{
    if (bgTextures.empty()) return 0;

    const int tier = (scoreStep > 0) ? (score / scoreStep) : 0;
    return static_cast<std::size_t>(tier) % bgTextures.size();
}

void Background::beginTransitionToIndex(std::size_t idx)
{
    if (bgTextures.empty()) return;
    if (idx == currentIndex) return;

    pendingIndex = idx;

    next.set(*bgTextures[pendingIndex], winSize);
    next.setAlpha(0);

    // keep scroll aligned (no visual jump)
    next.setX(current.a.getPosition().x, current.b.getPosition().x);

    transitioning = true;
    t = 0.f;
}

void Background::update(sf::Time& dt, int score)
{
    if (!current.texture) return;

    const std::size_t desired = pickIndexForScore(score);
    if (!transitioning && desired != currentIndex)
        beginTransitionToIndex(desired);

    current.update(dt, scrollSpeed);

    if (transitioning)
    {
        next.update(dt, scrollSpeed);

        t += dt.asSeconds();
        const float dur = std::max(transitionDuration, 0.01f);
        float u = smoothstep(t / dur);

        const sf::Uint8 aNext = static_cast<sf::Uint8>(std::round(255.f * u));
        const sf::Uint8 aCur = static_cast<sf::Uint8>(std::round(255.f * (1.f - u)));

        next.setAlpha(aNext);
        current.setAlpha(aCur);

        if (t >= dur)
        {
            current = next;
            current.setAlpha(255);
            currentIndex = pendingIndex;

            next.texture = nullptr;
            next.setAlpha(0);
            transitioning = false;
        }
    }
}

void Background::draw(sf::RenderTarget& target)
{
    current.draw(target);
    if (transitioning) next.draw(target);
}

void Background::reset()
{
}

