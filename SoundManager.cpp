#include "SoundManager.h"

SoundManager::SoundManager()
{
	initSounds();
}

void SoundManager::initSounds()
{
	// loat the sounds from the file paths and set the buffers for the sound objects
	m_flapSoundBuffer.loadFromFile(m_flapSoundPath);
	m_flapSound.setBuffer(m_flapSoundBuffer);
	m_flapSound.setVolume(50.f);  

	m_scoreSoundBuffer.loadFromFile(m_scoreSoundPath);
	m_scoreSound.setBuffer(m_scoreSoundBuffer);
	m_scoreSound.setVolume(25.f);  

	m_gameOverSoundBuffer.loadFromFile(m_gameOverSoundPath);
	m_gameOverSound.setBuffer(m_gameOverSoundBuffer);
	m_gameOverSound.setVolume(50.f);  
}
