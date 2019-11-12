#pragma once
#include "SceneApp.h"
#include "Button.h"
#include "Cursor.h"
#include "Collision.h"
enum MCondition_State
{
	 MENU, GAME, NETWORKING, FINISH, EXIT, HOW_TO_PLAY
};



class Menu_State
{
public:
	Menu_State();
	~Menu_State();

	//functions to run the menu state

	void OnEnter();
	void OnExit();
	void Update(float frame_time, MCondition_State &menu_change);
	void Draw();

	//functions specific to the state

	void Inputs();
	void Sprite_Init();
	void SpriteUpdating_Menu(float deltatime);
	void Audio_Text_Tnit();
	void StartButton(MCondition_State &menu_change);
	void HowtoPlayButton();
	void HowtoPlayScreen(float deltatime);


	MCondition_State state_;
	inline void SetState(MCondition_State newState) { state_ = newState; state_timer_ = 0.f; }

	

private:

	float state_timer_;
	float loading_wait = 0.0f;

	//----button variables----\\

	Button start_button;
	Button how_to_button;
	Button back_button;

	bool button_hover;

	sf::Texture how_to_red_texture;
	sf::Texture how_to_green_texture;

	sf::Texture start_green_texture;
	sf::Texture start_red_texture;

	sf::Texture back_red_texture;
	sf::Texture back_green_texture;

	//----text variables----\\

	sf::Text menu_text;

	//---- Audio Variable----\\

	bool musicStarted;

};

