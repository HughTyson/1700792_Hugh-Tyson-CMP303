#pragma once
#include "MySprite.h"
#include "Animation.h"
class Button :
	public MySprite
{
public:
	Button();
	~Button();

	void update(float deltatime);
	void collisionResponse(MySprite* sp);

protected:

	Animation pulse;
};

