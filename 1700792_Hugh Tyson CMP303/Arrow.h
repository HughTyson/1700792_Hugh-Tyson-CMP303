#pragma once
#include "MySprite.h"
#include "Vector.h"
class Arrow :
	public MySprite
{
public:
	Arrow();
	~Arrow();

	void Update(float deltatime, int mousex, int mousey, sf::Vector2f ball_position, sf::RenderWindow* window);

	void update_arrow(int mousex, int mousey);

	void draw(sf::Vector2f ball_position);

	bool hitting = false;

private:

	int newx, newy, currentx, currenty;

	sf::Vector2f direction;
};

