#pragma once

#include <SFML/Graphics.hpp>
#include "helper.hpp"

class Player
{
private:

	bool omNomming;

public:
	Direction direction;
	void draw(sf::RenderWindow& window, float dt);
	void update(Direction direction, float dt);
	//sf::Sprite sprite;
	sf::CircleShape shape;
	Player();
};