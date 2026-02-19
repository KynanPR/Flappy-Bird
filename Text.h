#pragma once
#include <SFML/Graphics.hpp>

enum OriginDirection { centre, left };

class Text {
 public:
  Text(int charSize,
       int outlineThickness = -1.f,
       OriginDirection originLocation = centre,
       sf::Color textColour = sf::Color::White,
       sf::Color outlineColour = sf::Color::Black);

  std::string getText() { return m_textString; };
  std::string setText(const std::string newTextString);

  sf::Vector2f getPosition() { return m_textDisplay.getPosition(); }
  sf::Vector2f setPosition(sf::Vector2f newPosition);

  void setFont(sf::Font& font);

  void render(sf::RenderWindow& renderWindow);

 private:
  sf::Text m_textDisplay;
  std::string m_textString = "";

  OriginDirection m_originLocation;
  void resetOrigin();
};
