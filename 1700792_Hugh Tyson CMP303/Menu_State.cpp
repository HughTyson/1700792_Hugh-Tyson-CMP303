#include "Menu_State.h"



Menu_State::Menu_State()
{
}

Menu_State::~Menu_State()
{
}

//functions for the running of the state

void Menu_State::OnEnter()
{

	state_ = MENU;

	Sprite_Init();

	Audio_Text_Tnit();
	
}

void Menu_State::OnExit()
{
}

void Menu_State::Update(float deltatime, MCondition_State & menu_change)
{
	state_timer_ += deltatime;

	sf::Vector2u size = game_system->window_->getSize();
	int windowsizex = size.x;
	int windowsizey = size.y;


	Inputs();


	switch (state_) //go betwee ndifferent states in the menu, main_menu, options, how to play and exit
	{
		case MCondition_State::MENU:
		{
			menu_change = MENU;

			SpriteUpdating_Menu(deltatime);
			
			StartButton(menu_change);

			HowtoPlayButton();
		
			
		}
		break;
		case MCondition_State::GAME:
		{
			if (loading_wait > 0.5f) // wit on the loading screen till 0.5 f to stop texture glitch 
			{
				menu_change = FINISH; //set menu state to FINISh indicting ot the state change to set new state up
			}
			else
			{
				loading_wait += deltatime; //increae oading time by frame time
			}
		}
		break;
		case MCondition_State::NETWORKING:
		{

			

		}
		break;
		case MCondition_State::HOW_TO_PLAY:
		{

			HowtoPlayScreen(deltatime);

		}
		
		break;
		case MCondition_State::EXIT:
		{
			menu_change = MCondition_State::EXIT; //set to exit so the application closes
		}
		break;
		default:
			break;
	}

	game_system->cursor_->update(deltatime, game_system->input_, game_system->getMouseX(), game_system->getMouseY()); //update the cursor everyt time no matter what sub section you are in
}

void Menu_State::Draw()
{
	
	game_system->window_->clear();
	
	switch (state_) //go betwee ndifferent states in the menu, main_menu, options, how to play and exit
	{
	case MCondition_State::MENU:
	{

		game_system->window_->draw(start_button);
		game_system->window_->draw(how_to_button);

	}
	break;
	case MCondition_State::NETWORKING:
	{


	}
	break;
	case MCondition_State::HOW_TO_PLAY:
	{

		game_system->window_->draw(back_button);
	
		game_system->window_->draw(menu_text);
	}

	break;
	case MCondition_State::EXIT:
	{
		
	}
	break;
	default:
		break;
	}

	game_system->window_->draw(*game_system->cursor_); //this hsoudl always be last drawn so the cursor is drawn on top of all other sprites

	game_system->window_->display();

}


//functions that are specific to the state

void Menu_State::Inputs()
{
	if (game_system->input_->isKeyDown(sf::Keyboard::Escape)) //press the escape key to quit the game
	{
		game_system->input_->setKeyUp(sf::Keyboard::Escape);
		game_system->window_->close();//closes the game
	}

}

void Menu_State::Sprite_Init()
{

	start_green_texture.loadFromFile("gfx/Startbuttongreen.png");
	start_red_texture.loadFromFile("gfx/Startbuttonred.png");
	start_button.setSize(sf::Vector2f(600, 200));
	start_button.setCollisionBox(sf::FloatRect(40, 50, 600, 100));
	start_button.setPosition(0, 0);
	start_button.setOrigin(sf::Vector2f(0, 0));
	start_button.setTexture(&start_red_texture);

	how_to_green_texture.loadFromFile("gfx/HowToPlayGreen.png");
	how_to_red_texture.loadFromFile("gfx/HowToPlayRed.png");
	how_to_button.setSize(sf::Vector2f(500, 200));
	how_to_button.setCollisionBox(sf::FloatRect(60, 70, 600, 100));
	how_to_button.setPosition(800, 0);
	how_to_button.setOrigin(sf::Vector2f(0, 0));
	how_to_button.setTexture(&how_to_red_texture);

	back_red_texture.loadFromFile("gfx/Pausemenubuttonred.png");
	back_green_texture.loadFromFile("gfx/Pausemenubuttongreen.png");
	back_button.setTexture(&back_red_texture);
	back_button.setSize(sf::Vector2f(400, 150));
	back_button.setCollisionBox(sf::FloatRect(40, 50, 280, 100));
	back_button.setPosition(750, 500);
	back_button.setOrigin(sf::Vector2f(0, 0));

	//if (!font_.loadFromFile("font/varsity_regular.ttf")) {
	//	std::cout << "Arial not loaded" << std::endl;
	//}


}

void Menu_State::Audio_Text_Tnit()
{	
	menu_text.setFont(*game_system->font_);
	menu_text.setCharacterSize(24);
	menu_text.setPosition(90, 100);


	game_system->audio_->addMusic("sfx/MenuMusic.ogg", "Menu");
	game_system->audio_->playMusicbyName("Menu");
}

void Menu_State::SpriteUpdating_Menu(float deltatime)
{
	start_button.update(deltatime);
	how_to_button.update(deltatime);

}



void Menu_State::StartButton(MCondition_State& menu_change)
{

	if (Collision::checkBoundingBox(game_system->cursor_, &start_button))
	{
		
		start_button.collisionResponse(NULL);
		start_button.setTexture(&start_green_texture);
		button_hover = true;
	}
	else {
		button_hover = false;
		start_button.setTexture(&start_red_texture);
	}

	if (button_hover == true) {

		if (game_system->input_->isMouseLeftDown() == true) {
			menu_change = FINISH;
		}
	}

}

void Menu_State::HowtoPlayButton()
{

	if (Collision::checkBoundingBox(game_system->cursor_, &how_to_button))
	{
		
		how_to_button.collisionResponse(NULL);
		how_to_button.setTexture(&how_to_green_texture);
		button_hover = true;
	}
	else {
		how_to_button.setTexture(&how_to_red_texture);
		button_hover = false;
	}

	if (button_hover == true) {

		if (game_system->input_->isMouseLeftDown() == true) {
			state_ = HOW_TO_PLAY;
		}

	}

}

void Menu_State::HowtoPlayScreen(float deltatime)
{

	
	if (Collision::checkBoundingBox(game_system->cursor_, &back_button)) //checks if the cursor and button collide
	{
		game_system->cursor_->collisionResponse(NULL);
		back_button.collisionResponse(NULL);
		button_hover = true; //if their is collision set back collision variable to true
		back_button.setTexture(&back_green_texture); //change button colour to green if there is collision
	}
	else
	{
		button_hover = false;
		back_button.setTexture(&back_red_texture); // if no collision set texture red
	}

	if (button_hover == true) {

		if (game_system->input_->isMouseLeftDown() == true) {
			// if the left mouse button is clicked when mouse collides with button change instructions to false to display the main menu
			state_ = MENU;

		}

	}
	
	//setting the text to tell the player how ot play
	menu_text.setString("CONTROLS \nMOVE BALL : CLICK WHERE YOU WANT BALL TO GO, DRAG TOWARDS BALL AND RELEASE CLICK. \nPAUSE : P \nOBJECTIVE : GET YOUR BALL IN THE HOLE WITH THE LEAST AMOUNT OF SHOTS TAKEN \nEXIT : TO EXIT PUSH THE ESCAPE KEY");
	back_button.update(deltatime);
}
