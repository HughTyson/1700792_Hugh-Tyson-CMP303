#include "GameState.h"





void GameState::OnEnter()
{
}

GameState *GameState::Update(float frame_time)
{
	return this;
}

void GameState::Draw()
{
}

void GameState::OnExit()
{
}

//menu manager class, used to call all appropriate states in Menu_State


void Menu_Manager::OnEnter()
{

	menu.OnEnter();
}

GameState * Menu_Manager::Update(float delta_time)
{
	menu.Update(delta_time, _state);

	if (_state == MCondition_State::EXIT)
	{
		return this;
	}

	if (_state != MCondition_State::FINISH)
	{
		if (_state == MCondition_State::FINISH_NETWORK)
		{
			return new Lobby_Manager;
		}

		return this;
	}
	else if (_state == MCondition_State::FINISH)
	{
		return new Select_PLayer_Manager;
	}

	return this;
}

void Menu_Manager::Draw()
{
	menu.Draw();
}

void Menu_Manager::OnExit()
{
	menu.OnExit();
}


//level 1 class, used to call all appropriate functions for the first level

void Level1_Manager::OnEnter()
{
	level1.OnEnter();
}

GameState * Level1_Manager::Update(float delta_time)
{
	level1.Update(delta_time, _state);

	if (_state == LCondition_State::ENDL)
	{
		return this;
	}

	if (_state != LCondition_State::FINISHL)
	{
		return this;
	}
	else if (_state == LCondition_State::FINISHL)
	{
		return new Menu_Manager;
	}

	return this;
}

void Level1_Manager::Draw()
{
	level1.Draw();
}

void Level1_Manager::OnExit()
{
	level1.OnExit();
}

//select player state

void Select_PLayer_Manager::OnEnter()
{
	select_players.OnEnter();
}

GameState * Select_PLayer_Manager::Update(float delta_time)
{

	select_players.Update(delta_time, _state);

	if (_state != SCondition_State::FINISHS)
	{
		return this;
	}
	else if (_state == SCondition_State::FINISHS)
	{
		return new Level1_Manager;
	}

	return this;
}

void Select_PLayer_Manager::Draw()
{
	select_players.Draw();
}

void Select_PLayer_Manager::OnExit()
{
}

//lobby state

void Lobby_Manager::OnEnter()
{
	lobby.OnEnter();
}

GameState * Lobby_Manager::Update(float delta_time)
{

	lobby.Update(delta_time, _state);

	if (_state != LobbyCondition_State::SERVER_READY)
	{
		return this;
	}
	else if (_state == LobbyCondition_State::SERVER_READY)
	{
		return new Level1_Manager;
	}

	return this;
	
}

void Lobby_Manager::Draw()
{
	lobby.Draw();
}

void Lobby_Manager::OnExit()
{
	lobby.OnExit();
}
