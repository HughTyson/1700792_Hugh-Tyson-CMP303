#pragma once
#include "MySprite.h"

#include "Vector.h"

class Ball :
	public MySprite
{
public:
	Ball();
	~Ball();

	virtual void update(float deltatime, int mousex, int mousey, sf::RenderWindow* window);
	void collisionResponse(enum Type type, float deltatime);

	int getShots();
	inline void setShots(int shots) { shots_taken = shots; }

	bool getHole();
	inline void setHole(bool hole) { in_hole = hole; }

	bool getHit();
	inline void setHit(bool ht) { hit = ht; }



private:

	//functions used to calculate the direction and velocity of th ball


	void hittingBall(int mousex, int mousey);
	void ballSpeedControl(float deltatime);
	void onScreen(sf::RenderWindow *window);
	void ScaleChange(float x, float y);

	//variable to do with the player hitting thee ball
	int shots_taken;
	float friction;
	float speed;
	
	bool hitting;
	bool in_hole;
	bool hit;

	int tick = 0;

	float distance = 0;
	float currentx = 0;
	float currenty = 0;
	float newx = 0;
	float newy = 0;

	sf::Vector2f direction;
	sf::Vector2f target;
};

