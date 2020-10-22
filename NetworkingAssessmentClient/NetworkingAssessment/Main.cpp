/*
	2D 2 player Shooter game designed to demonstrate networking between 2 client versions of the games through a server.
	CLIENT version of the game.
	@Author Ruaraidh Canaway.
	The Game Loop in Main, Animation Class, collision and Input class is Paul Robertsons code.
*/

#include <SFML/Graphics.hpp>
#include "Input.h"
#include "Game.h"

int WINDOW_WIDTH = 1250;
int WINDOW_HEIGHT = 950;
int NUM_OF_SQUARES = 15;
int SQUARE_SIZE = 50;
int XSIZE = 25;
int YSIZE = 19;
//25/19
int main() 
{
	// Create window
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Networking Shooter Client 1");
	window.setPosition(sf::Vector2i(0, 0));
	window.setFramerateLimit(60);

	//Input Control
	Input input;

	//Game State
	Game game(&window, &input);

	//For Delta time
	sf::Clock clock;
	float deltaTime;

	//Game Loop
	while (window.isOpen())
	{
		//Calculate delta time. How much time has passed and since last calculated. Restart clock. 
		deltaTime = clock.restart().asSeconds();

		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				window.setView(sf::View(sf::FloatRect(0.f, 0.f,
					(float)event.size.width, (float)event.size.height)));
				break;
			case sf::Event::KeyPressed:
				// update input class
				input.setKeyDown(event.key.code);
				break;
			case sf::Event::KeyReleased:
				//update input class
				input.setKeyUp(event.key.code);
				break;
			case sf::Event::MouseMoved:
				//update input class
				input.setMousePosition(event.mouseMove.x,
					event.mouseMove.y);
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					//update input class
					input.setMouseLeftDown(true);
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					//update input class
					input.setMouseLeftDown(false);
				}
				break;
			default:
				// don't handle other events
				break;
			}

			
		}
			if (input.isKeyDown(sf::Keyboard::Escape)) {
				input.setKeyUp(sf::Keyboard::Escape);
				window.close();
			}

			game.inputControl(deltaTime);
			game.update(deltaTime);

			window.clear();
			game.render(deltaTime);
			window.display();
	}

	return 0;
}
