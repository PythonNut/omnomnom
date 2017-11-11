#pragma once

#include <SFML/Graphics.hpp>
#include "helper.hpp"
#include "texprite.hpp"

class Player
{
private:

	bool omNomming;
	int version;

public:
	Direction direction;
	void draw(sf::RenderWindow& window, float dt);
	void update(Direction direction, float dt);
	sf::Sprite sprite;
	Texprite ts;
	sf::CircleShape shape;
	Player();
};