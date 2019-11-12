#include "Cursor.h"



Cursor::Cursor()
{

	//setting up the bobbing animation for the curosr
	bob.addFrame(sf::IntRect(0, 0, 216, 233));
	bob.addFrame(sf::IntRect(0, 233, 216, 233));
	bob.addFrame(sf::IntRect(0, 466, 216, 233));
	bob.addFrame(sf::IntRect(0, 699, 216, 233));
	bob.addFrame(sf::IntRect(0, 932, 216, 233));
	bob.addFrame(sf::IntRect(0, 1165, 216, 233));
	bob.addFrame(sf::IntRect(0, 1398, 216, 233));
	bob.addFrame(sf::IntRect(0, 1631, 216, 233));
	bob.addFrame(sf::IntRect(0, 1864, 216, 233));
	bob.addFrame(sf::IntRect(0, 2097, 216, 233));
	bob.setFrameSpeed(1.f / 10.f);

	//setting up the swinging animation for the cursor
	swing.addFrame(sf::IntRect(0, 0, 216, 233));
	swing.addFrame(sf::IntRect(0, 233, 216, 233));
	swing.addFrame(sf::IntRect(0, 466, 216, 233));
	swing.addFrame(sf::IntRect(0, 699, 216, 233));
	swing.addFrame(sf::IntRect(0, 932, 216, 233));
	swing.addFrame(sf::IntRect(0, 1165, 216, 233));
	swing.addFrame(sf::IntRect(0, 1398, 216, 233));
	swing.addFrame(sf::IntRect(0, 1631, 216, 233));
	swing.addFrame(sf::IntRect(0, 1864, 216, 233));
	swing.addFrame(sf::IntRect(0, 2097, 216, 233));
	swing.setFrameSpeed(1.f / 10.f);

}


Cursor::~Cursor()
{
}

void Cursor::update(float deltatime, Input* input, int mousex, int mousey) {

	this->setPosition(mousex, mousey);
	
	bob.animate(deltatime);
	setTextureRect(bob.getCurrentFrame());

}

void Cursor::collisionResponse(MySprite* sp)
{
}

void Cursor::swingUpdate(float deltatime, Input* input, int mousex, int mousey)
{
	this->setPosition(mousex, mousey);

	swing.animate(deltatime);
	setTextureRect(swing.getCurrentFrame());
}