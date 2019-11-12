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

	Sprite_Init();

	Map_Init();
}

void Level1_State::OnExit()
{

	Object_Clean_Up();

	Texture_Clean_Up();

}

void Level1_State::Update(float deltatime, LCondition_State & menu_change)
{

	Inputs(); 

	switch (state_)
	{
	case CONTINUEL:
	{
		Player_Update(deltatime);

		Collisions(deltatime);

		
	}
		break;
	case PAUSEL:
	{
		Pause_Update(menu_change);
	}
		break;
	case FINISHL:
	{

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

	for (int i = 0; i < player.size(); i++)
	{
		game_system->window_->draw(player[i]);
	}

	game_system->window_->draw(hole);

	game_system->window_->draw(*game_system->cursor_);
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

}

void Level1_State::Sprite_Init()
{

	//Setting all the variables for the first players ball
	ballTexture1.loadFromFile("gfx/Ball.png");
	ballTexture1.setSmooth(true);

	temp_player.setTexture(&ballTexture1);
	temp_player.setSize(sf::Vector2f(18, 18));
	temp_player.setPosition(90, 500);
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

void Level1_State::Player_Update(float deltatime)
{

	if (Vector::magnitude(player[current_player].getVelocity()) < 10.f && player[current_player].getHit() == true)
	{
		player[current_player].setHit(false);
		current_player++;

	}

	if (current_player == amount_of_players)
	{	
		current_player = 0;
	}

	if (player[current_player].getHole() == true)
	{
		current_player++;

		if (current_player == amount_of_players)
		{
			current_player = 0;
		}
	}

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

void Level1_State::Player_Hole_Collision(int j, float deltatime)
{

	

	

}

void Level1_State::Pause_Update(LCondition_State & menu_change)
{

	if (game_system->input_->isMouseLeftDown())
	{
		menu_change = FINISHL;
	}

}

void Level1_State::Texture_Clean_Up()
{
	

}

void Level1_State::Object_Clean_Up()
{

	world->clear();
	world = NULL;

	player.clear();
	

}


