#include "Arrow.h"



Arrow::Arrow()
{
	setOrigin(0, 0);
}


Arrow::~Arrow()
{
}

void Arrow::Update(float deltatime, int mousex, int mousey, sf::Vector2f ball_position, sf::RenderWindow * window, Input *in)
{
	setPosition(ball_position);

	update_arrow(mousex, mousey, in);


	
}

void Arrow::update_arrow(int mousex, int mousey, Input *in)
{

	if (in->isMouseLeftDown())
	{
		if (hitting == false)
		{
			currentx = mousex;
			currenty = mousey;
			hitting = true;
		}

	}
	
	if (!in->isMouseLeftDown())
	{
		hitting = false;
	}

	if (in->isMouseLeftDown() && hitting)
	{

		newx = mousex;
		newy = mousey;

		float a = newx - currentx ;
		float b = newy - currenty;

		//float rotation = a + b;
		float rotation = ((atan2(a, b)) * (180 / 3.146));

		rotation = 360 - rotation;
		angle = rotation;
		setRotation(rotation);
	
	}		
}
