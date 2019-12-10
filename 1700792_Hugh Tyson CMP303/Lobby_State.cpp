#include "Lobby_State.h"



Lobby_State::Lobby_State()
{
	button_hover = false;
	ready = false;
	data.start_game = false;
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
	game_system->network_->game_time.restart();
}

void Lobby_State::Update(float frame_time, LobbyCondition_State & lobby_change)
{

	game_system->window_->setView(game_system->lobby_view);
	
	
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
			game_system->network_->disconnect();
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
	ready_tex_red.loadFromFile("gfx/ready button red.png");
	ready_button.setSize(sf::Vector2f(400, 150));
	ready_button.setCollisionBox(sf::FloatRect(40, 50, 400, 70));
	ready_button.setPosition(0, 50);
	ready_button.setOrigin(sf::Vector2f(0, 0));
	ready_button.setTexture(&ready_tex_red);

	exit_tex.loadFromFile("gfx/exit button.png");
	exit_tex_red.loadFromFile("gfx/exit button red.png");
	exit_button.setSize(sf::Vector2f(400, 150));
	exit_button.setCollisionBox(sf::FloatRect(40, 50, 400, 70));
	exit_button.setPosition(550,50);
	exit_button.setOrigin(sf::Vector2f(0, 0));
	exit_button.setTexture(&exit_tex_red);

}

void Lobby_State::Sprite_Updating(float deltatime)
{

}

void Lobby_State::Client_Update(LobbyCondition_State & lobby_change)
{
	float timeSinceLastUpdate = game_system->network_->player_clock.getElapsedTime().asSeconds();

	if (timeSinceLastUpdate >= game_system->network_->updateTick)
	{
		game_system->network_->player_clock.restart();
		game_system->network_->lobby_update(ready, exit);
	}		

	data.start_game = game_system->network_->client_recive();
	if (game_system->network_->get_connected() == false)
	{
		state_ = EXIT_SERVER;
		game_system->network_->lobby_update(ready, exit);
	}

	if (data.start_game)
	{
		std::cout << "now" << std::endl;
		game_system->setOnlineMulti(true);
		game_system->setLocalMulti(false);
		lobby_change = SERVER_READY;
	}

	
}

void Lobby_State::Ready_Button()
{
	if (Collision::checkBoundingBox(game_system->cursor_, &ready_button))
	{
		game_system->cursor_->collisionResponse(NULL);
		ready_button.collisionResponse(NULL);
		ready_button.setTexture(&ready_tex);
		button_hover = true;
	}
	else
	{
		button_hover = false;
		ready_button.setTexture(&ready_tex_red);
	}

	if (button_hover == true && !ready)
	{
		if (game_system->input_->isMouseLeftDown())
		{
			ready = true;
			game_system->input_->setMouseLeftDown(false);
		}
	}
	else if (button_hover == true && ready)
	{
		if (game_system->input_->isMouseLeftDown())
		{
			ready = false;
			game_system->input_->setMouseLeftDown(false);
		}
	}

	if (ready == true)
	{
		ready_button.setTexture(&ready_tex);
	}

}

void Lobby_State::Exit_Button()
{

	if (Collision::checkBoundingBox(game_system->cursor_, &exit_button))
	{
		game_system->cursor_->collisionResponse(NULL);
		exit_button.collisionResponse(NULL);
		exit_button.setTexture(&exit_tex);
		button_hover = true;
	}
	else
	{
		button_hover = false;
		exit_button.setTexture(&exit_tex_red);
	}

	if (button_hover == true)
	{
		if (game_system->input_->isMouseLeftDown())
		{
			exit = true;
			game_system->input_->setMouseLeftDown(false);
		}
		button_hover = false;
	}


}
