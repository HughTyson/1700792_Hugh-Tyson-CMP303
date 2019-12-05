#pragma once
#include "SceneApp.h"
#include "Ball.h"
#include "Hole.h"
#include "Arrow.h"
#include "Collision.h"
#include <vector>
enum LCondition_State
{
	READYL, CONTINUEL, ENDL, PAUSEL, FINISHL, FINISHL_SERVER
};

enum Movement_Type
{
	POSITION, PREDICTION, VELOCITY
};

class Level1_State
{
public:
	Level1_State();
	~Level1_State();

	//functions to run the menu state

	void OnEnter();
	void OnExit();
	void Update(float frame_time, LCondition_State &menu_change);
	void Draw();

	//variables specific to the level
	void Inputs();
	void Sprite_Init();
	void Map_Init();
	void Sound_Init();
	void Collisions(float deltatime);

	void Player_Update(float deltatime);
	void Player_Ground_Collision(int i,float deltatime);
	void Player_Hole_Collision(int j, float deltatime);

	void Pause_Update(LCondition_State & menu_change);

	float lerp(float a, float b, float t);
	void Object_Clean_Up();

	LCondition_State state_;
	inline void SetState(LCondition_State newState) { state_ = newState; state_timer_ = 0.f; }

	//functions used for networking

	void NetworkingUpdate(float deltatime);
	void NetworkingPlayerUpdate(float deltatime);
	void NetworkingMouseUpdate(float deltatime);

	
private:

	
	float state_timer_;
	float loading_wait = 0.0f;

	bool local_multiplayer = false;
	bool online_multiplayer = false;
	int current_player = 0;
	int amount_of_players = 0;

	//----player variables----\\

	std::vector<Ball> player;
	std::vector<Arrow> arrow;
	Ball temp_player;
	Arrow temp_arrow;
	sf::Texture ballTexture1;
	sf::Texture arrowTexture;

	// text for the game
	sf::Text player1text;
	sf::Text player2text;
	sf::Text whatPlayer;
	
	//variable used to check collisions with tiles in the tilesheets

	std::vector<MySprite>* world;

	//variable used for holes

	
	Hole hole;
	sf::Texture hole_texture;


	//variables used for networking

	Cursor* second_cursor;
	sf::Texture cursor_tex;

	bool level_finished;

	int other_player;

	int ball_movement_type;


};

