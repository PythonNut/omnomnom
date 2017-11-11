#include "player.hpp"

Player::Player()
{
	omNomming = false;
	direction = Direction::RIGHT;

	// init sprite stuff... that's annoying.
	// actually load a texture, and implement an animation switching algorithm


	shape.setRadius(20);
	shape.setFillColor(sf::Color::White);
	shape.setOrigin(20, 20);
}

void Player::draw(sf::RenderWindow& window, float dt)
{
	window.draw(shape);
}

void Player::update(Direction direction, float dt)
{
	// do something? maybe nothing
}