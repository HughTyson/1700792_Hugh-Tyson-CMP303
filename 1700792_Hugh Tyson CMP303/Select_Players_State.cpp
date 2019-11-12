#include "Select_Players_State.h"



Select_Players_State::Select_Players_State()
{
}


Select_Players_State::~Select_Players_State()
{
}

void Select_Players_State::OnEnter()
{
	Sprite_Init();
	_state = CONTINUES;
}

void Select_Players_State::OnExit()
{
}

void Select_Players_State::Update(float frame_time, SCondition_State & state_change)
{

	game_system->window_->setView(game_system->view);
	switch (_state)
	{
		break;
	case CONTINUES:
	{
		Input(frame_time);
		Button_Update(frame_time);
		Selection(state_change);

	}
		break;
	default:
		break;
	}



}

void Select_Players_State::Draw()
{
	game_system->window_->clear();
	game_system->window_->draw(one_player);
	game_system->window_->draw(two_player);

	game_system->window_->draw(*game_system->cursor_);
	game_system->window_->display();
}

void Select_Players_State::Sprite_Init()
{

	red_1button_texture.loadFromFile("gfx/oneplayerred.png");green_1button_texture.loadFromFile("gfx/oneplayerbutton.png");
	one_player.setTexture(&red_1button_texture);
	one_player.setSize(sf::Vector2f(350, 150));
	one_player.setCollisionBox(sf::FloatRect(40, 50, 280, 100));
	one_player.setOrigin(0, 0);
	one_player.setPosition(50, 166);

	

	red_2button_texture.loadFromFile("gfx/twoplayerred.png");green_2button_texture.loadFromFile("gfx/twoplayergreen.png");
	two_player.setTexture(&red_2button_texture);
	two_player.setSize(sf::Vector2f(350, 150));
	two_player.setCollisionBox(sf::FloatRect(40, 50, 280, 100));
	two_player.setOrigin(0, 0);
	two_player.setPosition(450, 166);

	
}

void Select_Players_State::Input(float deltatime)
{
	game_system->cursor_->update(deltatime, game_system->input_, game_system->getMouseX(), game_system->getMouseY());

	if (game_system->input_->isKeyDown(sf::Keyboard::Escape)) //press the escape key to quit the game
	{
		game_system->input_->setKeyUp(sf::Keyboard::Escape);
		game_system->window_->close();//closes the game
	}
}

void Select_Players_State::Button_Update(float deltatime)
{

	one_player.update(deltatime);
	two_player.update(deltatime);

	if (Collision::checkBoundingBox(game_system->cursor_, &one_player)) // collision between mouse and on player button making the button green
	{
		one_player.collisionResponse(NULL);
		one_player_collision = true;
		one_player.setTexture(&green_1button_texture);
	}
	else {
		one_player_collision = false;
		one_player.setTexture(&red_1button_texture);
	}

	//// ------------------------------- TWO PLAYER SELECTION -----------------------

	if (Collision::checkBoundingBox(game_system->cursor_, &two_player)) // collision between mouse and two player button, making the button turn green
	{
		
		two_player.collisionResponse(NULL);
		two_player_collision = true;
		two_player.setTexture(&green_2button_texture);
	}
	else {
		two_player_collision = false;
		two_player.setTexture(&red_2button_texture);
	}

}

void Select_Players_State::Selection(SCondition_State &state_change)
{

	if (one_player_collision == true) 
	{
		if (game_system->input_->isMouseLeftDown() == true) 
		{
			game_system->setLocalMulti(false);
			game_system->input_->setMouseLeftDown(false);
			_state = FINISHS;
			state_change = FINISHS;
		}
	}

	if (two_player_collision == true)
	{
		if (game_system->input_->isMouseLeftDown() == true) 
		{
			game_system->setLocalMulti(true);
			game_system->input_->setMouseLeftDown(false);
			_state = FINISHS;
			state_change = FINISHS;

		}
	}
}
