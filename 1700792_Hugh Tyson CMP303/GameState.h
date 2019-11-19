#pragma once
#include "Menu_State.h" 
#include "Level1_State.h"
#include "Select_Players_State.h"
#include "Lobby_State.h"
class GameState
{
public:

	virtual void OnEnter();
	virtual GameState *Update(float delta_time) = 0;
	virtual void Draw();
	virtual void OnExit();
};

class Menu_Manager : public GameState
{
public:

	Menu_State menu; //create the menu state as an object, so its functions can be called


	MCondition_State _state; //check fr a change in state for mthe menu e.g change to game


	void OnEnter();
	GameState *Update(float delta_time); //returning a pointer of menu_update to scene app
	void Draw();
	void OnExit();
};

class Level1_Manager : public GameState
{
	Level1_State level1;

	LCondition_State _state;

	void OnEnter();
	GameState *Update(float delta_time); //returning a pointer of level_update to scene app
	void Draw();
	void OnExit();
};

class Select_PLayer_Manager :public GameState
{

	Select_Players_State select_players;

	SCondition_State _state;

	void OnEnter();
	GameState *Update(float delta_time); //returning a pointer of level_update to scene app
	void Draw();
	void OnExit();
};

class Lobby_Manager : public GameState
{
	Lobby_State lobby;

	LobbyCondition_State _state;

	void OnEnter();
	GameState *Update(float delta_time); //returning a pointer of level_update to scene app
	void Draw();
	void OnExit();
};
