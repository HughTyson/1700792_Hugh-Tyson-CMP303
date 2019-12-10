#pragma once
#include <SFML\Graphics.hpp>
#include "Input.h"
#include "Cursor.h"
#include "MySprite.h"
#include "TileMap.h"
#include "AudioManager.h"
#include "NetworkingManager.h"


class GameState;

class SceneApp
{
public:


	void Init();

	void CleanUp();
	bool Update(float frame_time);
	void Render();
	//void InitFont();
	//void CleanUpFont();
	//void DrawHUD();

private:

	GameState *currentState;
	GameState *nextState_;

	float fps_;

};



class System
{
public:

	void Init();
	void Release();

	float getMouseX();
	float getMouseY();
	void setMouseX(float mx);
	void setMouseY(float my);

	bool getLocalMulti();
	void setLocalMulti(bool multi);

	bool getOnlineMulti();
	void setOnlineMulti(bool multi);

	void restartNetwork();


	sf::RenderWindow *window_;
	Input* input_;

	AudioManager *audio_;

	Cursor* cursor_;
	sf::Texture cursor_texture;


	sf::Font* font_;

	MySprite tile;
	std::vector<MySprite> tiles;

	TileMap tileMap;

	sf::View view;
	sf::View lobby_view;

	NetworkingManager* network_;

private:

	bool local_multiplayer;
	bool online_multiplayer;
	float mousex = 0;
	float mousey = 0;
};

extern System *game_system;
