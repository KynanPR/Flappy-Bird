#include "Text.h"

Text::Text(int charSize,
           int outlineThickness,
           OriginDirection originLocation,
           sf::Color textColour,
           sf::Color outlineColour) {
  m_originLocation = originLocation;

  m_textDisplay.setCharacterSize(charSize);
  m_textDisplay.setFillColor(textColour);
  int finalOutlineThickness =
      outlineThickness == -1 ? charSize / 10 : outlineThickness;
  finalOutlineThickness = std::min(finalOutlineThickness, 6);
  m_textDisplay.setOutlineThickness(finalOutlineThickness);
  m_textDisplay.setOutlineColor(outlineColour);

  resetOrigin();
}

std::string Text::setText(const std::string newTextString) {
  m_textString = newTextString;
  m_textDisplay.setString(m_textString);
  resetOrigin();
  return m_textString;
}

sf::Vector2f Text::setPosition(sf::Vector2f newPosition) {
  m_textDisplay.setPosition(newPosition);
  return m_textDisplay.getPosition();
}

void Text::setFont(sf::Font& font) {
  m_textDisplay.setFont(font);
}

void Text::render(sf::RenderWindow& renderWindow) {
  renderWindow.draw(m_textDisplay);
}

void Text::resetOrigin() {
  sf::Vector2f finalOriginLocation;
  switch (m_originLocation) {
    case centre:
      finalOriginLocation = {m_textDisplay.getLocalBounds().width / 2,
                             m_textDisplay.getLocalBounds().height / 2};
      break;
    case left:
      finalOriginLocation = {0, m_textDisplay.getLocalBounds().height / 2};
      break;
    default:
      finalOriginLocation = {m_textDisplay.getLocalBounds().width / 2,
                             m_textDisplay.getLocalBounds().height / 2};
      break;
  }
  m_textDisplay.setOrigin(finalOriginLocation);
}
