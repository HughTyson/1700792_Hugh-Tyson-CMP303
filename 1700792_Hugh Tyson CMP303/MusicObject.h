// Music object
// Store the filename/path and key for a music file.
// Music files are not loaded into memory due to size.

#pragma once
#include "SFML\Audio.hpp"

class MusicObject
{
public:
	MusicObject();
	~MusicObject();

	void setMusic(std::string lfilename, std::string lname);

	std::string filename;
	std::string name;


};

