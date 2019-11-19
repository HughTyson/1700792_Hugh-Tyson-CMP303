#include "Lobby_State.h"



Lobby_State::Lobby_State()
{
}


Lobby_State::~Lobby_State()
{
}

void Lobby_State::OnEnter()
{
	state_ = LOBBY;
	//game_system->setOnlineMulti(true);

	Sprite_Init();

}

void Lobby_State::OnExit()
{
}

void Lobby_State::Update(float frame_time, LobbyCondition_State & lobby_change)
{


	switch (state_)
	{
		case LobbyCondition_State::LOBBY:
		{
			Client_Update();
			Sprite_Updating();
		}
	}



}

void Lobby_State::Draw()
{

	game_system->window_->clear();
	
	game_system->window_->draw(ready_button);
	game_system->window_->draw(exit_button);


	game_system->window_->draw(*game_system->cursor_);

	game_system->window_->display();
}

void Lobby_State::Inputs()
{
}

void Lobby_State::Sprite_Init()
{
	ready_tex.loadFromFile("gfx/ready button.png");
	ready_button.setSize(sf::Vector2f(600, 200));
	ready_button.setCollisionBox(sf::FloatRect(40, 50, 600, 100));
	ready_button.setPosition(0, 50);
	ready_button.setOrigin(sf::Vector2f(0, 0));
	ready_button.setTexture(&ready_tex);

	exit_tex.loadFromFile("gfx/exit button.png");
	exit_button.setSize(sf::Vector2f(600, 200));
	exit_button.setCollisionBox(sf::FloatRect(40, 50, 600, 100));
	exit_button.setPosition(350,50);
	exit_button.setOrigin(sf::Vector2f(0, 0));
	exit_button.setTexture(&exit_tex);

}

void Lobby_State::Sprite_Updating()
{
}

void Lobby_State::Client_Update()
{

	game_system->network_->lobby_update(ready, exit);

}
