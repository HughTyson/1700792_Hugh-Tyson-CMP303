#include "Level1_State.h"



Level1_State::Level1_State()
{
}


Level1_State::~Level1_State()
{
}

void Level1_State::OnEnter()
{

	state_ = CONTINUEL;

	game_system->window_->setView(game_system->view);

	if (game_system->getLocalMulti() == true)
	{
		local_multiplayer = true;
	}

	if (game_system->getOnlineMulti() == true)
	{
		online_multiplayer = true;
	}

	Sprite_Init();

	Map_Init();

	if (game_system->network_->getClientNumber() == 0)
	{
		other_player = 1;
	}
	else if (game_system->network_->getClientNumber() == 1)
	{
		other_player = 0;
	}

	level_finished = false;

	ball_movement_type = POSITION;
}

void Level1_State::OnExit()
{

	Object_Clean_Up();


}

void Level1_State::Update(float deltatime, LCondition_State & level_change)
{

	Inputs(); 

	switch (state_)
	{
	case CONTINUEL:
	{

		if (online_multiplayer == true)
		{
			NetworkingUpdate(deltatime);
		}
			

		Player_Update(deltatime);

		Collisions(deltatime);

		
	}
		break;
	case PAUSEL:
	{
		Pause_Update(level_change);
	}
		break;
	case FINISHL:
	{

	}
	case FINISHL_SERVER:
	{
		level_change = FINISHL_SERVER;
	}
		break;
	default:
		break;
	}


	player1text.setString("STROKES = " + std::to_string(player[0].getShots()));

}

void Level1_State::Draw()
{

	game_system->window_->clear();
	
	game_system->tileMap.render(game_system->window_);

	//for (int i = 0; i < player.size(); i++)
	//{
	//	game_system->window_->draw(player[i]);
	//}

	game_system->window_->draw(player[0]);
	game_system->window_->draw(player[1]);
	
	game_system->window_->draw(hole);

	game_system->window_->draw(*game_system->cursor_);

	if (online_multiplayer)
	{
		game_system->window_->draw(*second_cursor);
	}

	game_system->window_->display();
}

void Level1_State::Inputs()
{

	if (game_system->input_->isKeyDown(sf::Keyboard::P)) {
		
		if (state_ == PAUSEL)
		{
			state_ = CONTINUEL;
		}
		else
		{
			state_ = PAUSEL;
		}
		
		game_system->input_->setKeyUp(sf::Keyboard::P);
	}

	if (game_system->input_->isKeyDown(sf::Keyboard::Escape)) //press the escape key to quit the game
	{
		game_system->input_->setKeyUp(sf::Keyboard::Escape);
		game_system->window_->close();//closes the game
	}

	
	if (game_system->input_->isKeyDown(sf::Keyboard::Num1))
	{
		ball_movement_type = POSITION;
	}

	if (game_system->input_->isKeyDown(sf::Keyboard::Num2))
	{
		ball_movement_type = PREDICTION;
	}

	if (game_system->input_->isKeyDown(sf::Keyboard::Num3))
	{
		ball_movement_type = VELOCITY;
	}

}



void Level1_State::Player_Update(float deltatime)
{

	current_player = game_system->network_->getClientNumber();

	if (Vector::magnitude(player[game_system->network_->getClientNumber()].getVelocity()) < 10.f && player[game_system->network_->getClientNumber()].getHit() == false)
	{
		player[current_player].setHit(false);
	}


	//if (Vector::magnitude(player[current_player].getVelocity()) < 10.f && player[current_player].getHit() == true)
	//{
	//	player[current_player].setHit(false);
	//	pl
	//	current_player++;
	//}





	//if (current_player == amount_of_players)
	//{	
	//	current_player = 0;
	//}

	//if (player[current_player].getHole() == true)
	//{
	//	current_player++;

	//	if (current_player == amount_of_players)
	//	{
	//		current_player = 0;
	//	}
	//}

	player[current_player].update(deltatime, game_system->getMouseX(), game_system->getMouseY(), game_system->window_);

	
	hole.Update(deltatime);
}

void Level1_State::Collisions(float deltatime)
{

	//check for ball collision with the tile sheet

	for (int i = 0; i < player.size(); i++)
	{
		if (Vector::magnitude(player[i].getVelocity()) > 10.f)
		{
			Player_Ground_Collision(i, deltatime);
		}

		//checking if the player has collided with the hole
		if (player[i].getHole() == false)
		{
			if (Collision::checkBoundingBox(&hole, &player[i]))
			{
				hole.collisionResponse(BALL, deltatime);
				player[i].collisionResponse(HOLE, deltatime);
			}
		}
	}

}

void Level1_State::Player_Ground_Collision(int j, float deltatime)
{
	for (int i = 0; i < (int)world->size(); i++)
	{
		// if collision check should occur
		if ((*world)[i].isCollider())
		{
			if (Collision::checkBoundingBox(&player[j], &(*world)[i]))
			{
				player[j].collisionResponse(ROUGH, deltatime);
			}
		}
	}

}

void Level1_State::Pause_Update(LCondition_State & menu_change)
{

	if (!online_multiplayer)
	{
		if (game_system->input_->isMouseLeftDown())
		{
			menu_change = FINISHL;
		}
	}
}



void Level1_State::NetworkingUpdate(float deltatime)
{
	float timeSinceLastUpdate = game_system->network_->player_clock.getElapsedTime().asSeconds();

	if (timeSinceLastUpdate >= game_system->network_->updateTick)
	{
		game_system->network_->player_clock.restart();
		game_system->network_->game_update();
	}
	
	level_finished = game_system->network_->client_recive();


	//if (level_finished == true)
	//{
	//	state_ = FINISHL_SERVER;
	//}

	NetworkingPlayerUpdate(deltatime);
	NetworkingMouseUpdate(deltatime);
}

void Level1_State::NetworkingPlayerUpdate(float deltatime)
{
	float predictedX;
	float predictedY;
	float x_change;
	float y_change;
	float predicted_x;
	float predicted_y;

	if (ball_movement_type == POSITION)
	{
		player[other_player].setPosition(sf::Vector2f(game_system->network_->player_info[other_player].ball_position));
	}
	else if (ball_movement_type == PREDICTION)
	{
		int size = game_system->network_->messages.size();

		if (size > 3)
		{
			const PlayerInfo& msg0 = game_system->network_->messages[size - 1];
			const PlayerInfo& msg1 = game_system->network_->messages[size - 2];
			const PlayerInfo& msg2 = game_system->network_->messages[size - 3];

			sf::Vector2f velocity_a(msg0.ball_position.x - msg1.ball_position.x, msg0.ball_position.y - msg1.ball_position.y);
			sf::Vector2f velocity_b(msg1.ball_position.x - msg2.ball_position.x, msg1.ball_position.y - msg2.ball_position.y);

			//x_change = msg0.mouse_pos.x - msg1.mouse_pos.x;
			//y_change = msg0.mouse_pos.y - msg1.mouse_pos.y;

			float time_diff = game_system->network_->game_time.getElapsedTime().asSeconds() - msg0.last_time; //find latency by calculating difference in the local clock and the networck clock

			//x_change /= time_diff;
			//y_change /= time_diff;

			//predictedX = msg0.mouse_pos.x + (time_diff * x_change);
			//predictedY = msg0.mouse_pos.y + (time_diff * y_change);

			float time_ = msg0.last_time - msg1.last_time;

			sf::Vector2f acceleration = (velocity_b - velocity_a) / time_;

			predictedX = msg0.mouse_pos.x + (velocity_a.x*time_diff) + (0.5*acceleration.x*pow(time_diff, 2));
			predictedY = msg0.mouse_pos.y + (velocity_a.y*time_diff) + (0.5*acceleration.y*pow(time_diff, 2));

			predictedX = lerp(second_cursor->getPosition().x, predictedX, (game_system->network_->offset_time));
			predictedY = lerp(second_cursor->getPosition().y, predictedY, (game_system->network_->offset_time));

			second_cursor->update(deltatime, game_system->input_, predictedX, predictedY);
			//second_cursor->update(deltatime, game_system->input_, msg0.mouse_pos.x, msg0.mouse_pos.y);
		}
		else
		{
			second_cursor->update(deltatime, game_system->input_, game_system->network_->player_info[other_player].mouse_pos.x, game_system->network_->player_info[other_player].mouse_pos.y);
		}

	}

	game_system->network_->player_info[game_system->network_->getClientNumber()].ball_position = sf::Vector2f(player[current_player].getPosition());

}

void Level1_State::NetworkingMouseUpdate(float deltatime)
{

	float predictedX = -1.f;
	float predictedY = -1.f;
	float x_change;
	float y_change;
	float predicted_x;
	float predicted_y;


	 int size = game_system->network_->messages.size();


	if (size > 3)
	{
		const PlayerInfo& msg0 = game_system->network_->messages[size - 1];
		const PlayerInfo& msg1 = game_system->network_->messages[size - 2];
		const PlayerInfo& msg2 = game_system->network_->messages[size - 3];
		
		sf::Vector2f velocity_a(msg0.mouse_pos.x - msg1.mouse_pos.x, msg0.mouse_pos.y - msg1.mouse_pos.y);
		sf::Vector2f velocity_b(msg1.mouse_pos.x - msg2.mouse_pos.x, msg1.mouse_pos.y - msg2.mouse_pos.y);

		float time_diff = game_system->network_->game_time.getElapsedTime().asSeconds() - msg0.last_time; //find latency by calculating difference in the local clock and the networck clock
																							 
		float time_ = msg0.last_time - msg1.last_time;

		sf::Vector2f acceleration = (velocity_b - velocity_a) / time_;

		predictedX = msg0.mouse_pos.x + (velocity_a.x*time_diff) + (0.5*acceleration.x*pow(time_diff, 2));
		predictedY = msg0.mouse_pos.y + (velocity_a.y*time_diff) + (0.5*acceleration.y*pow(time_diff, 2));

		//predictedX = lerp(second_cursor->getPosition().x, predictedX, msg0.last_time + time_diff);
		//predictedY = lerp(second_cursor->getPosition().y, predictedY, msg0.last_time + time_diff);

		std::cout << predictedX << std::endl;

		second_cursor->update(deltatime, game_system->input_, predictedX, predictedY);
		
	}
	else
	{
		second_cursor->update(deltatime, game_system->input_, game_system->network_->player_info[other_player].mouse_pos.x, game_system->network_->player_info[other_player].mouse_pos.y);
	}

	//uppdate this clients info to be sent to the server
	game_system->network_->player_info[game_system->network_->getClientNumber()].mouse_pos = sf::Vector2f(game_system->cursor_->getPosition().x, game_system->cursor_->getPosition().y);


}

float Level1_State::lerp(float a, float b, float t)
{
	return a+t*(b-a);
}

void Level1_State::Object_Clean_Up()
{

	world->clear();
	world = NULL;

	player.clear();
	

}

void Level1_State::Sprite_Init()
{

	//Setting all the variables for the first players ball
	ballTexture1.loadFromFile("gfx/Ball.png");
	ballTexture1.setSmooth(true);

	temp_player.setTexture(&ballTexture1);
	temp_player.setSize(sf::Vector2f(18, 18));
	temp_player.setPosition(game_system->network_->player_info[0].ball_position);
	temp_player.setInput(game_system->input_);
	temp_player.setCollisionBox(0, 0, 18, 18);
	temp_player.setOrigin(sf::Vector2f(0, 0));
	temp_player.setVelocity(0, 0);

	player.push_back(temp_player);

	temp_arrow.setTexture(&arrowTexture);
	temp_arrow.setSize(sf::Vector2f(20, 20));
	temp_arrow.setPosition(0, 0);
	temp_player.setOrigin(sf::Vector2f(0, 0));

//	arrow.push_back(temp_player);


	//an if statement that is used for any sprites that get declared if the game is multiplayer
	if (local_multiplayer == true)
	{
		//Setting all the variables for the first players ball
		temp_player.setPosition(457, 500);
		temp_player.setFillColor(sf::Color::Blue);
		player.push_back(temp_player);

		amount_of_players = 2;

		player2text.setFont(*game_system->font_);
		player2text.setCharacterSize(24);
		player2text.setPosition(600, 0);

		whatPlayer.setFont(*game_system->font_);
		whatPlayer.setCharacterSize(32);
		whatPlayer.setPosition(280, 0);
	}
	player1text.setFont(*game_system->font_);
	player1text.setCharacterSize(24);

	amount_of_players = player.size();

	//defining the hole

	hole_texture.loadFromFile("gfx/GolfHole.png");
	hole.setTexture(&hole_texture);
	hole.setSize(sf::Vector2f(32, 32));
	hole.setOrigin(sf::Vector2f(0, 0));
	hole.setCollisionBox(2, 2, 25, 25);
	hole.setPosition(670, 96);

	if (online_multiplayer)
	{
		second_cursor = new Cursor;
		cursor_tex.loadFromFile("gfx/Mousebobanimation.png");
		second_cursor->setTexture(&cursor_tex);
		second_cursor->setCollisionBox(0, 0, 32, 32);
		second_cursor->setSize(sf::Vector2f(32, 32));
		second_cursor->setInput(game_system->input_);
		game_system->window_->setMouseCursorVisible(false);

		temp_player.setPosition(game_system->network_->player_info[1].ball_position);
		temp_player.setTexture(&ballTexture1);
		temp_player.setSize(sf::Vector2f(18, 18));
		temp_player.setCollisionBox(0, 0, 18, 18);
		temp_player.setOrigin(sf::Vector2f(0, 0));
		temp_player.setVelocity(0, 0);

		player.push_back(temp_player);
	}
}

void Level1_State::Map_Init()
{
	// Map dimensions
	sf::Vector2u mapSize(13, 10);

	std::vector<int> map = {
		17, 0, 0, 0, 0, 0, 0, 0, 17, 0, 0, 0, 17,
		17, 0, 0, 0, 0, 0, 0, 0, 17, 0, 0, 0, 17,
		17, 0, 0, 0, 0, 0, 0, 0, 17, 0, 0, 0, 17,
		17, 0, 0, 0, 17, 0, 0, 0,17, 0, 0, 0, 17,
		17, 0, 0, 0, 17, 0, 0, 0, 17, 0, 0, 0, 17,
		17, 0, 0, 0, 17, 0, 0, 0, 17, 0, 0, 0, 17,
		17, 0, 0, 0, 17, 0, 0, 0, 17, 0, 0, 0, 17,
		17, 0, 0, 0, 17, 0, 0, 0, 0, 0, 0, 0, 17,
		17, 5, 5, 5, 17, 0, 0, 0, 0, 0, 0, 0, 17,
		17, 8, 0, 0, 17, 0, 0, 0, 0, 0, 0, 0, 17,
	};

	game_system->tileMap.setTileMap(map, mapSize);
	game_system->tileMap.setPosition(sf::Vector2f(0, 0));
	game_system->tileMap.buildLevel();

	world = game_system->tileMap.getLevel();
}

void Level1_State::Sound_Init()
{
	game_system->audio_->addSound("sfx/GolfPutt.ogg", "Menu");
}