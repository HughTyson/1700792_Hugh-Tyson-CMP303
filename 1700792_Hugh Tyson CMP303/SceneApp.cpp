#include "SceneApp.h"
#include "GameState.h"
#include "Menu_State.h"
#include "Level1_State.h"


void SceneApp::Init()
{

	game_system = new System();
	game_system->Init();

	currentState = new Menu_Manager();
	nextState_ = currentState;
	currentState->OnEnter(); //run Init of the new function
}

void SceneApp::CleanUp()
{
	//game_system->Release(); //clean up the game system e.g delete primitive builder, audio etc

	//CleanUpFont();

}

bool SceneApp::Update(float frame_time)
{

	fps_ = 1.0f / frame_time; //calculte fps
	game_system->setMouseX(game_system->input_->getMouseX());
	game_system->setMouseY(game_system->input_->getMouseY());


	game_system->cursor_->update(frame_time, game_system->input_, game_system->getMouseX(), game_system->getMouseY());

	if (nextState_ != currentState) //check if tere has bee na state change
	{
		currentState->OnExit(); //run the clean up function for the current state
		delete currentState; //delete the current state
		currentState = nextState_; //updtae current state variable to tell it wha the new state is
		nextState_->OnEnter(); //initialise the new state
	}


	nextState_ = currentState->Update(frame_time); //run current state, if the state changes nextState variable is changed

	return true;

}

void SceneApp::Render()
{
	currentState->Draw(); //render the appropriate state to screen
}

System *game_system;

void System::Init()
{
	window_ = new sf::RenderWindow();
	window_->create(sf::VideoMode(1280, 720), "Trinity Golf", sf::Style::Resize);
	
	input_ = new Input;

	audio_ = new AudioManager;

	cursor_ = new Cursor();
	cursor_texture.loadFromFile("gfx/Mousebobanimation.png");
	cursor_->setTexture(&cursor_texture);
	cursor_->setCollisionBox(0, 0, 32, 32);
	cursor_->setSize(sf::Vector2f(32, 32));
	cursor_->setInput(game_system->input_);
	window_->setMouseCursorVisible(false);

	font_ = new sf::Font;

	if (!font_->loadFromFile("font/varsity_regular.ttf")) {
		std::cout << "Arial not loaded" << std::endl;
	}

	local_multiplayer = true;

	//tileMap.loadTexture("gfx/groundGrass_mown.png");

	tileMap.loadTexture((char*)"gfx/ground.png");

	tile.setSize(sf::Vector2f(64, 64));
	tile.setCollisionBox(0, 0, 64, 64);
	tile.setCollider(false);
	tile.setType(GROUND);
	for (int i = 0; i < 17; i++)
	{
		tile.setTextureRect(sf::IntRect(0, i*64, 64, 64));
		tiles.push_back(tile);
	}

	tile.setCollider(true);
	tile.setType(ROUGH);
	tile.setTextureRect(sf::IntRect(0, 1088, 64, 64));
	tiles.push_back(tile);

	tileMap.setTileSet(tiles);

	view.setSize(830, 630);
	view.setCenter(415, 315);

	lobby_view.setSize(window_->getSize().x, window_->getSize().y);
	lobby_view.setCenter(window_->getSize().x/2 , window_->getSize().y/2);


	network_ = new NetworkingManager();
}

void System::Release() //Clean up functin for system
{
}

float System::getMouseX()
{
	return mousex;
}

float System::getMouseY()
{
	return mousey;
}

void System::setMouseX(float mx)
{
	mousex = mx;
}

void System::setMouseY(float my)
{
	mousey = my;
}

bool System::getLocalMulti()
{
	return local_multiplayer;
}

void System::setLocalMulti(bool multi)
{
	local_multiplayer = multi;
}

bool System::getOnlineMulti()
{
	return online_multiplayer;
}

void System::setOnlineMulti(bool multi)
{
	online_multiplayer = multi;
}

void System::restartNetwork()
{

	network_ = NULL;
	delete network_;

	network_ = new NetworkingManager;


}
