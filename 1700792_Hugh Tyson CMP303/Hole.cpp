#include "Hole.h"



Hole::Hole()
{

	//setting up the animation for when the ball goes in the hole
	fade.addFrame(sf::IntRect(0, 0, 16, 16));
	fade.addFrame(sf::IntRect(0, 16, 16, 16));
	fade.addFrame(sf::IntRect(0, 32, 16, 16));
	fade.addFrame(sf::IntRect(0, 48, 16, 16));
	fade.addFrame(sf::IntRect(0, 64, 16, 16));
	fade.addFrame(sf::IntRect(0, 78, 16, 16));
	fade.addFrame(sf::IntRect(0, 80, 16, 16));
	fade.addFrame(sf::IntRect(0, 96, 16, 16));
	fade.addFrame(sf::IntRect(0, 112, 16, 16));
	setTextureRect(sf::IntRect(0, 0, 16, 16));
	fade.setFrameSpeed(1.f / 10.f);

	//setting up the animation for the portal holes
	portal.addFrame(sf::IntRect(0, 0, 16, 16));
	portal.addFrame(sf::IntRect(0, 16, 16, 16));
	portal.addFrame(sf::IntRect(0, 32, 16, 16));
	portal.addFrame(sf::IntRect(0, 48, 16, 16));
	portal.addFrame(sf::IntRect(0, 64, 16, 16));
	portal.addFrame(sf::IntRect(0, 80, 16, 16));
	portal.addFrame(sf::IntRect(0, 96, 16, 16));
	portal.addFrame(sf::IntRect(0, 112, 16, 16));
	portal.addFrame(sf::IntRect(0, 128, 16, 16));
	portal.setFrameSpeed(1.f / 10.f);

	in_hole = false;


}


Hole::~Hole()
{
}

void Hole::Update(float deltatime)
{

	if (in_hole == true) {
		fade.animate(deltatime);
		setTextureRect(fade.getCurrentFrame());
		if (fade.getCurrentFrame().top >= 111) {
			fade.reset();
			in_hole = false;
		}
	}
	else
	{
		setTextureRect(sf::IntRect(0, 0, 16, 16));
	}

}

void Hole::collisionResponse(enum Type type, float dt)
{

	if (in_hole == false);
	{
		in_hole = true;
	}

}

void Hole::portalupdate(float dt)
{
	portal.animate(dt);
	setTextureRect(portal.getCurrentFrame());
}

bool Hole::getHole()
{
	return in_hole;
}
