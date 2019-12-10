#pragma once
#include "MySprite.h"
#include "Vector.h"
class Arrow :
	public MySprite
{
public:
	Arrow();
	~Arrow();

	void Update(float deltatime, int mousex, int mousey, sf::Vector2f ball_position, sf::RenderWindow* window, Input *in);

	void update_arrow(int mousex, int mousey, Input *in);

	void predicted_arrow(float angle);

	float getAngle() { return angle; };

	//void draw(sf::Vector2f ball_position);

	bool hitting = false;

private:

	float newx, newy, currentx, currenty;

	float angle;
};

