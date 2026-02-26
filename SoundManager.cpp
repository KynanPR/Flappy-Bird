#include "SoundManager.h"

SoundManager::SoundManager() {
  initSounds();
}

void SoundManager::initSounds() {
  // load the sounds from the file paths and set the buffers for the sound
  // objects
  m_flapSoundBuffer.loadFromFile(m_flapSoundPath);
  m_flapSound.setBuffer(m_flapSoundBuffer);
  m_flapSound.setVolume(65.f);

  m_scoreSoundBuffer.loadFromFile(m_scoreSoundPath);
  m_scoreSound.setBuffer(m_scoreSoundBuffer);
  m_scoreSound.setVolume(10.f);

  m_gameOverSoundBuffer.loadFromFile(m_gameOverSoundPath);
  m_gameOverSound.setBuffer(m_gameOverSoundBuffer);
  m_gameOverSound.setVolume(40.f);
}
