#include "Sound.h"

Sound::Sound()
{
}

Sound::~Sound()
{
}

// Loads sound into memory and can be identified by key (name).
void Sound::loadSound(std::string filename, std::string lname)
{
	buffer = new sf::SoundBuffer();
	buffer->loadFromFile(filename);
	sound.setBuffer(*buffer);
	name = lname;
}
