#pragma once
#include "MySprite.h"
#include "Animation.h"
#include <iostream>
class Cursor :
	public MySprite
{
public:
	Cursor();
	~Cursor();

	virtual void update(float deltatime, Input* input, int mousex, int mousey);
	virtual void swingUpdate(float deltatime, Input* input, int mousex, int mousey);
	void collisionResponse(MySprite* sp);

protected:

	Animation bob;
	Animation swing;
};

