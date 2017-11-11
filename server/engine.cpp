#include "engine.hpp"
#include "state.hpp"
#include "game.hpp"
#include "menu.hpp"

#include <iostream>

Engine::Engine()
{
	window.create(sf::VideoMode(960, 832), "omnomnom");
	window.setFramerateLimit(60);
	
	
	state = 0;
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

void Engine::refreshState(int i)
{
	delete states[i];
	if (i == 1) {
		states[i] = new Game;
	}
	if (i == 2) {
		states[i] = new Menu;
	}
}