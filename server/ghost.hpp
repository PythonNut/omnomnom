#pragma once

#include <SFML/Graphics.hpp>
#include "helper.hpp"

class Ghost
{
private:

public:
	Direction direction;
	void draw(sf::RenderWindow& window, float dt);
	void update(Direction direction, float dt);
	//sf::Sprite sprite;
	sf::CircleShape shape;
	Ghost();
	Ghost(sf::Color color);
};