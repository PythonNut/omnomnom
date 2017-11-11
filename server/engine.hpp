#pragma once
#include <SFML/Graphics.hpp>

#include "level.hpp"

class Engine
{
private:

	Level level;
	void handleInput();
	void update(float dt);
	void draw(float dt);


public:
	void loop();
	sf::RenderWindow window;


	Engine();
};