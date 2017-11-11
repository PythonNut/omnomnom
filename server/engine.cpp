#include "engine.hpp"

#include <iostream>

Engine::Engine()
{
	window.create(sf::VideoMode(1024, 768), "omnomnom");
	window.setFramerateLimit(60);
}

void Engine::loop()
{
	sf::Clock clock;
	float dt;

	while (window.isOpen())
	{
		dt = clock.restart().asSeconds();

		handleInput();
		update(dt);
		window.clear(sf::Color::Black);
		draw(dt);
		window.display();
	}
}

void Engine::handleInput()
{
	// remove this code once we have actual input!
	sf::Event event;

	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
		{
			window.close();
			break;
		}
		case sf::Event::KeyPressed:
		{
			if (event.key.code == sf::Keyboard::Escape)
				window.close();
			if (event.key.code == sf::Keyboard::Left)
			{
				// do left
				level.input(Direction::LEFT);
				//std::cout << "left" << std::endl;
			}
			if (event.key.code == sf::Keyboard::Right)
			{
				// do right
				level.input(Direction::RIGHT);
				//std::cout << "right" << std::endl;
			}
			if (event.key.code == sf::Keyboard::Down)
			{
				// do down
				level.input(Direction::DOWN);
				//std::cout << "down" << std::endl;
			}
			if (event.key.code == sf::Keyboard::Up)
			{
				// do up
				level.input(Direction::UP);
				//std::cout << "up" << std::endl;
			}
			break;
		}
		default: break;
		}
	}


}

void Engine::draw(float dt)
{
	level.drawWalls(window, dt);
	level.drawPlayer(window, dt);
	level.drawGhosts(window, dt);
}

void Engine::update(float dt)
{
	level.update(dt);
}