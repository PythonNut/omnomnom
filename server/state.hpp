#pragma once

#include <SFML/Graphics.hpp>
#include "engine.hpp"

class State
{
public:
	virtual void draw(sf::RenderWindow& window, const float dt) = 0;
	virtual void update(Engine* engine, const float dt) = 0;
	virtual void handleInput(Engine* engine, sf::RenderWindow& window) = 0;
};