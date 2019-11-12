#include "Arrow.h"



Arrow::Arrow()
{
}


Arrow::~Arrow()
{
}

void Arrow::Update(float deltatime, int mousex, int mousey, sf::Vector2f ball_position, sf::RenderWindow * window)
{

	update_arrow(mousex, mousey);

	if (hitting == true)
	{
		draw(ball_position);
	}
	
}

void Arrow::update_arrow(int mousex, int mousey)
{

	if (input->isMouseLeftDown() == true)
	{
		if (hitting == false)
		{
			currentx = mousex;
			currenty = mousey;
			hitting = true;
		}
		return;
	}
	
	if (hitting == true)
	{
		newx = mousex;
		newy = mousey;

		direction = sf::Vector2f(newx, newy) - sf::Vector2f(currentx, currenty);
		direction = Vector::normalise(direction);


	}


}

void Arrow::draw(sf::Vector2f ball_position)
{
	setPosition(ball_position.x, ball_position.y);
}
