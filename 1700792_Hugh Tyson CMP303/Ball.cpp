#include "Ball.h"



Ball::Ball()
{

	shots_taken = 0;
	friction = 100;
	speed = 0;
	hitting = false;
	in_hole = false;
	hit = false;

	distance = 0;
	currentx = 0;
	currenty = 0;
	newx = 0;
	newy = 0;

	type_ = BALL;
}


Ball::~Ball()
{
}

void Ball::update(float deltatime, int mousex, int mousey, sf::RenderWindow* window)
{
	//ScaleChange(1, 1);

	hittingBall(mousex, mousey);

	ballSpeedControl(deltatime);

	onScreen(window);
	
	move(velocity*deltatime);

}

void Ball::collisionResponse(enum Type type, float deltatime)
{


	switch (type) 
	{
	case ROUGH:
	{
		if (velocity.x < 0)
		{
			velocity.x += ((2000.f * 1)*deltatime);
		}
		else if (velocity.x > 0)
		{
			velocity.x += ((2000.f * -1)*deltatime);
		}

		if (velocity.y < 0)
		{
			velocity.y += ((2000.f * 1)*deltatime);
		}
		else if (velocity.y > 0)
		{
			velocity.y += ((2000.f * -1)*deltatime);
		}
		break;
	}
	case BALL:
	{
		speed *= -0.8;

		velocity = speed * direction;
	}
	break;

	case::HOLE:
	{
		setPosition(sf::Vector2f(900, 900));
		in_hole = true;
	}
	break;
	default:
		break;

	}
	

}

void Ball::hittingBall(int mousex, int mousey)
{
	if (Vector::magnitude(velocity) < 10) //check if the ball has stopped moving
	{
		if (input->isMouseLeftDown())
		{
			if (hitting == false)
			{
				currentx = mousex;
				currenty = mousey;
				hitting = true;
			}
			
			
			return;
		}
		else if (!input->isMouseLeftDown() && hitting == true)
		{
			speed = 0;
			shots_taken += 1;
			newx = mousex;
			newy = mousey;
			hitting = false;
			hit = true;
	


			direction = sf::Vector2f(newx, newy) - sf::Vector2f(currentx, currenty);
			direction = Vector::normalise(direction);

			speed = Vector::magnitude(sf::Vector2f(newx, newy) - sf::Vector2f(currentx, currenty));
			speed *= -1;
			velocity = direction * speed; // calculate velocity that the ball will move at

			////////PUT SOUND HERE\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

			return;
		}
	}
}

void Ball::ballSpeedControl(float deltatime)
{
	if (velocity.x > 400) {
		velocity.x = 399;
	}
	else if (velocity.y > 400) {
		velocity.y = 399;
	}
	else if (velocity.x < -400) {
		velocity.x = -399;
	}
	else if (velocity.y < -400) {
		velocity.y = -300;
	}

	//stopping the ball completely if ti gets too slow
	if (velocity.x < 10 && velocity.x >0 || velocity.x > -10 && velocity.x < 0) {
		velocity.x = 0;
	}
	else if (velocity.y < 10 && velocity.y >0 || velocity.y > -10 && velocity.y < 0) {
		velocity.y = 0;
	}


	if (velocity.x < 0)
	{
		velocity.x += ((friction * 1)*deltatime);
	}
	else if (velocity.x > 0)
	{
		velocity.x += ((friction * -1)*deltatime);
	}

	if (velocity.y < 0)
	{
		velocity.y += ((friction * 1)*deltatime);
	}
	else if (velocity.y > 0)
	{
		velocity.y += ((friction * -1)*deltatime);
	}
}

void Ball::onScreen(sf::RenderWindow* window)
{

	// keeps the ball within the screen
	if (getPosition().x < 0)
	{
		setPosition(0, getPosition().y);
		velocity.x = -velocity.x;
		
	}
	if (getPosition().x > (window->getSize().x - 460))
	{
		setPosition((window->getSize().x - 460), getPosition().y);
		velocity.x = -velocity.x;
		
	}
	if (getPosition().y < 0)
	{
		setPosition(getPosition().x, 0);
		velocity.y = -velocity.y;
		
	}
	if (getPosition().y > (window->getSize().y - 95))
	{
		setPosition(getPosition().x, (window->getSize().y -95));
		velocity.y = -velocity.y;
		
	}

}

void Ball::ScaleChange(float x, float y)
{
	setScale(sf::Vector2f(x,y));
}

int Ball::getShots()
{
	return shots_taken;
}

bool Ball::getHole()
{
	return in_hole;
}

bool Ball::getHit()
{
	return hit;
}








