#pragma once	
#include "SceneApp.h"
#include "Button.h"

enum LobbyCondition_State
	{
		LOBBY, SERVER_READY, EXIT_SERVER
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
	void Sprite_Updating();
	void Client_Update();


	//Sprite Button varibles
	Button ready_button;
	Button exit_button;
	sf::Texture ready_tex;
	sf::Texture exit_tex;

	//mulitplayer variable

	bool ready;
	bool exit;
	
};

