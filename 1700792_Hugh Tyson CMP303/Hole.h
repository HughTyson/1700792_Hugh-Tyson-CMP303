#pragma once
#include "MySprite.h"
#include "Animation.h"

class Hole :
	public MySprite
{
public:
	Hole();
	~Hole();

	void Update(float deltatime);
	void collisionResponse(enum Type type, float dt);
	void portalupdate(float dt);

	bool getHole();
	inline void setHole(bool hole) { in_hole = hole; };

private:

	Animation fade;
	Animation portal;

	bool in_hole;
};

