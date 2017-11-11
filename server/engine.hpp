#pragma once
#include <SFML/Graphics.hpp>
#include <vector>


class State;

class Engine
{
private:

public:
	void loop();
	sf::RenderWindow window;
	std::vector<State*> states;
	State* getState();
	void pushState(State* state);
	int state;
	Engine();
};