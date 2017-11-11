#include "ghost.hpp"

Ghost::Ghost()
{
	direction = Direction::NONE;

	// init sprite stuff... that's annoying.
	// actually load a texture, and implement an animation switching algorithm


	shape.setRadius(20);
	shape.setFillColor(sf::Color::White);
	shape.setOrigin(0, 0);
}

Ghost::Ghost(sf::Color color)
{
	direction = Direction::NONE;

	// init sprite stuff. write a texture manager

	shape.setRadius(20);
	shape.setFillColor(color);
	shape.setOrigin(0, 0);
}

void Ghost::draw(sf::RenderWindow& window, float dt)
{
	window.draw(shape);
}

void Ghost::update(Direction direction, float dt)
{
	// do something? maybe nothing
}