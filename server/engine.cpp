#include "engine.hpp"
#include "state.hpp"

#include <iostream>

Engine::Engine()
{
	window.create(sf::VideoMode(1024, 768), "omnomnom");
	window.setFramerateLimit(60);
	
	
	state = 1;
}

void Engine::loop()
{
	sf::Clock clock;
	float dt;

	while (window.isOpen())
	{
		dt = clock.restart().asSeconds();
		getState()->handleInput(window);
		getState()->update(this,dt);
		window.clear(sf::Color::Black);
		getState()->draw(window,dt);
		window.display();
	}
}

State* Engine::getState()
{
	return states[state];
}

void Engine::pushState(State* state)
{
	states.push_back(state);
	return;
}