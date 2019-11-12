// Sound object
// Loads sound file and stores related key.

#pragma once
#include "SFML\Audio.hpp"

class Sound
{
public:
	Sound();
	~Sound();

	void loadSound(std::string filename, std::string lname);

	sf::Sound sound;
	std::string name;

private:
	// Sound buffer must not leave scope or sound will be destroyed.
	sf::SoundBuffer* buffer;
	
};

