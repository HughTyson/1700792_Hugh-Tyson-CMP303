#include "Button.h"



Button::Button()
{

	//setting up the animation for the pulsing buttons
	pulse.addFrame(sf::IntRect(0, 0, 64, 48));
	pulse.addFrame(sf::IntRect(0, 48, 64, 48));
	pulse.addFrame(sf::IntRect(0, 96, 64, 48));
	pulse.addFrame(sf::IntRect(0, 144, 64, 48));
	pulse.addFrame(sf::IntRect(0, 192, 64, 48));
	pulse.addFrame(sf::IntRect(0, 240, 64, 48));
	pulse.addFrame(sf::IntRect(0, 288, 64, 48));
	pulse.addFrame(sf::IntRect(0, 336, 64, 48));
	pulse.addFrame(sf::IntRect(0, 384, 64, 48));
	pulse.addFrame(sf::IntRect(0, 432, 64, 48));
	pulse.setFrameSpeed(1.f / 10.f);
}


Button::~Button()
{
}

void Button::update(float dt) {

	pulse.animate(dt);
	setTextureRect(pulse.getCurrentFrame());

}

void Button::collisionResponse(MySprite * sp)
{
}
