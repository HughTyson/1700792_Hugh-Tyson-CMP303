#pragma once
#include "SFML\Graphics.hpp"
#include "Input.h"

enum Type
{
	BALL, GROUND, ROUGH, HOLE
};

class MySprite : public sf::RectangleShape
{
public:
	MySprite();
	~MySprite();


	virtual void update(float dt);

	// sprite speed and direction
	void setVelocity(sf::Vector2f vel);
	void setVelocity(float vx, float vy);
	sf::Vector2f getVelocity();

	// sprite state
	bool isAlive() { return alive; };
	void setAlive(bool b) { alive = b; };

	// for sprite collision
	bool isCollider() { return collider; };
	void setCollider(bool b) { collider = b; };
	sf::FloatRect getCollisionBox();
	void setCollisionBox(float x, float y, float width, float height) { collisionBox = sf::FloatRect(x, y, width, height); };
	void setCollisionBox(sf::FloatRect fr) { collisionBox = fr; };
	virtual void collisionResponse(enum Type type);

	// input component
	void setInput(Input* in) { input = in; };

	//set a type for the sprite

	inline void setType(Type temp_type) { type_ = temp_type; }
	Type getType();

protected:
	// Sprite properties
	sf::Vector2f velocity;
	bool alive;

	// Collision vars
	sf::FloatRect collisionBox;
	bool collider;

	// input component
	Input* input;

	Type type_;
};