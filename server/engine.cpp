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
}

void Engine::draw(float dt)
{

}

void Engine::update(float dt)
{
}