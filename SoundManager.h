#pragma once
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
class SoundManager {
 public:
  SoundManager();
  sf::Sound& getFlapSound() { return m_flapSound; }
  sf::Sound& getScoreSound() { return m_scoreSound; }
  sf::Sound& getGameOverSound() { return m_gameOverSound; }

 private:
  void initSounds();
  sf::SoundBuffer m_flapSoundBuffer;
  sf::SoundBuffer m_scoreSoundBuffer;
  sf::SoundBuffer m_gameOverSoundBuffer;
  sf::Sound m_flapSound;
  sf::Sound m_scoreSound;
  sf::Sound m_gameOverSound;
  const std::string m_flapSoundPath = "assets/Sounds/sfx_wing.wav";
  const std::string m_scoreSoundPath = "assets/Sounds/sfx_point.wav";
  const std::string m_gameOverSoundPath = "assets/Sounds/sfx_hit.wav";
};
