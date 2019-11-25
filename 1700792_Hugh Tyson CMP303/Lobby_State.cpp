#include "Lobby_State.h"



Lobby_State::Lobby_State()
{
	button_hover = false;
	ready = false;
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
			Client_Update(lobby_change);
			Sprite_Updating(frame_time);
			Ready_Button();
			Exit_Button();
			break;
		}
		case LobbyCondition_State::EXIT_SERVER:
		{
			lobby_change = EXIT_SERVER;
			break;
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
	ready_button.setSize(sf::Vector2f(400, 150));
	ready_button.setCollisionBox(sf::FloatRect(40, 50, 600, 100));
	ready_button.setPosition(0, 50);
	ready_button.setOrigin(sf::Vector2f(0, 0));
	ready_button.setTexture(&ready_tex);

	exit_tex.loadFromFile("gfx/exit button.png");
	exit_button.setSize(sf::Vector2f(400, 150));
	exit_button.setCollisionBox(sf::FloatRect(40, 50, 600, 100));
	exit_button.setPosition(450,50);
	exit_button.setOrigin(sf::Vector2f(0, 0));
	exit_button.setTexture(&exit_tex);

}

void Lobby_State::Sprite_Updating(float deltatime)
{

}

void Lobby_State::Client_Update(LobbyCondition_State & lobby_change)
{
	game_system->network_->lobby_update(ready, exit);

	data.start_game = game_system->network_->lobby_recive(&data.start_game);

	if (exit == true)
	{
		lobby_change = EXIT_SERVER;
	}

	if (data.start_game)
	{
		lobby_change = SERVER_READY;
	}
}

void Lobby_State::Ready_Button()
{
	if (Collision::checkBoundingBox(game_system->cursor_, &ready_button))
	{
		game_system->cursor_->collisionResponse(NULL);
		ready_button.collisionResponse(NULL);
		button_hover = true;
	}
	else
	{
		button_hover = false;
	}

	if (button_hover == true && !ready)
	{
		if (game_system->input_->isMouseLeftDown())
		{
			ready = true;
		}
		button_hover = false;
		//change the colour of the button
	}
	else if (button_hover == true && ready)
	{
		if (game_system->input_->isMouseLeftDown())
		{
			ready = false;
		}
		//change the colour of the button
		button_hover = false;
	}

}

void Lobby_State::Exit_Button()
{

	if (Collision::checkBoundingBox(game_system->cursor_, &exit_button))
	{
		game_system->cursor_->collisionResponse(NULL);
		exit_button.collisionResponse(NULL);
		button_hover = true;
	}
	else
	{
		button_hover = false;
	}

	if (button_hover == true && !ready)
	{
		if (game_system->input_->isMouseLeftDown())
		{
			exit = true;
		}
		button_hover = false;
	}


}
