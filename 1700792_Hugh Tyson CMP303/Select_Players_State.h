#pragma once
#include "SceneApp.h"
#include "Button.h"
#include "Collision.h"

enum SCondition_State
{
	READYS, CONTINUES, FINISHS
};

class Select_Players_State
{
public:
	Select_Players_State();
	~Select_Players_State();

	//functions to run the menu state

	void OnEnter();
	void OnExit();
	void Update(float frame_time, SCondition_State &state_change);
	void Draw();

	//functions specific to the runnign of the state

	void Sprite_Init();
	void Input(float deltatime);
	void Button_Update(float deltatime);
	void Selection(SCondition_State &state_change);
	

private:

	SCondition_State _state;

	Button one_player;
	sf::Texture green_1button_texture;
	sf::Texture red_1button_texture;

	Button two_player;
	sf::Texture green_2button_texture;
	sf::Texture red_2button_texture;

	bool one_player_collision = false;
	bool two_player_collision = false;
};

