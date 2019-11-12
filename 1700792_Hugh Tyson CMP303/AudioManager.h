// Audio Manager
// Maintains lists of Sound and Music for playback in game
#pragma once

#include "Sound.h"
#include "MusicObject.h"
#include "SFML\Audio.hpp"

class AudioManager
{
public:
	AudioManager();
	~AudioManager();

	void addSound(std::string filename, std::string lname);
	void playSoundbyName(std::string lname);
	void stopAllSounds();

	void addMusic(std::string filename, std::string lname);
	void playMusicbyName(std::string lname);
	void stopAllMusic();

private:
	// List of sounds
	std::vector<Sound> sounds;
	// List of Musics
	std::vector<MusicObject> musics;
	// Single Music object as the stream cannot be copied.
	sf::Music music;
	// Re-useable sound object
	Sound s;
};

