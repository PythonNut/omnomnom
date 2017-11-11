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

	version = 0;
	ts = Texprite("images/face.png", sf::IntRect(0, 0, 50, 50), 1);

	sprite.setTexture(ts.tex);
	sprite.setOrigin(25, 25);
}

void Player::draw(sf::RenderWindow& window, float dt)
{
	//window.draw(shape);


	ts.changeVersion(version);

	sprite.setTextureRect(ts.getBounds());

	window.draw(sprite);
}

void Player::update(Direction direction, float dt)
{
	this->direction = direction;

}