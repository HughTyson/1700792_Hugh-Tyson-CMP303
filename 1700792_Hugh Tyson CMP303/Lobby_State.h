#pragma once	
#include "SceneApp.h"
#include "Button.h"
#include "Collision.h"

enum LobbyCondition_State
{
	LOBBY, SERVER_READY, EXIT_SERVER
};

struct lobby_data
{
	bool start_game;
};

class Lobby_State
{
public:
	Lobby_State();
	~Lobby_State();

	//function to run the Menu

	void OnEnter();
	void OnExit();
	void Update(float frame_time, LobbyCondition_State &lobby_change);
	void Draw();

	LobbyCondition_State state_;

private:
	
	//functions local to the state
	void Inputs();
	void Sprite_Init();
	void Sprite_Updating(float deltatime);
	void Client_Update(LobbyCondition_State & lobby_change);

	void Ready_Button();
	void Exit_Button();
	bool button_hover;

	lobby_data data;

	//Sprite Button varibles
	Button ready_button;
	Button exit_button;
	sf::Texture ready_tex;
	sf::Texture ready_tex_red;
	sf::Texture exit_tex;
	sf::Texture exit_tex_red;

	//mulitplayer variable

	bool ready;
	bool exit;
	
};

