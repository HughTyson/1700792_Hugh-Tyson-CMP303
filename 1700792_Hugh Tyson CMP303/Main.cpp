#include <iostream>
#include "SceneApp.h"

SceneApp application;


int main()
{

	//For Delta Time
	sf::Clock clock;
	float deltatime;


	//sf::RenderWindow window(sf::VideoMode(1280, 720), "Trinity Golf", sf::Style::Resize);


	application.Init();

	
	
	while (game_system->window_->isOpen())
	{
		game_system->window_->setSize(sf::Vector2u(1280, 720));
		sf::Event event;

		while (game_system->window_->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				game_system->window_->close();
				break;
			case sf::Event::Resized:
				game_system->window_->setView(sf::View(sf::FloatRect(0.f, 0.f,
					(float)event.size.width, (float)event.size.height)));
				break;
			case sf::Event::KeyPressed:
				// update input class
				game_system->input_->setKeyDown(event.key.code);
				break;
			case sf::Event::KeyReleased:
				//update input class
				game_system->input_->setKeyUp(event.key.code);
				break;
			case sf::Event::MouseMoved:
				//update input class
				game_system->input_->setMousePosition(event.mouseMove.x,
					event.mouseMove.y);
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					//update input class
					game_system->input_->setMouseLeftDown(true);
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					//update input class
					game_system->input_->setMouseLeftDown(false);
				}
				break;
			default:
				// don't handle other events
				break;
			}
		}
		//Calculate delta time. How much time has passed
		//since it was calculate (in seconds) adn restart the clock

		deltatime = clock.restart().asSeconds();
		application.Update(deltatime);

		
		
		application.Render();

	}
		return 0;


}