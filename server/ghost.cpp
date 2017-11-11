#include "ghost.hpp"

Ghost::Ghost()
{
	direction = Direction::NONE;

	// init sprite stuff... that's annoying.
	// actually load a texture, and implement an animation switching algorithm


	shape.setRadius(20);
	shape.setFillColor(sf::Color::White);
	shape.setOrigin(20, 20);

}

Ghost::Ghost(sf::Color color)
{
	direction = Direction::NONE;

	// init sprite stuff. write a texture manager

	shape.setRadius(20);
	shape.setFillColor(color);
	shape.setOrigin(20, 20);
}

Ghost::Ghost(const std::string& filename)
{
	direction = Direction::NONE;

	version = 0;
	ts = Texprite(filename, sf::IntRect(0, 0, 64, 64), 1);
	sprite.setOrigin(32, 32);
}

Ghost::Ghost(sf::Texture& tex)
{
	direction = Direction::NONE;

	version = 0;
	ts = Texprite("images/face.png", sf::IntRect(0, 0, 64, 64), 1);
	sprite.setTexture(tex);
	sprite.setOrigin(32, 32);
}

void Ghost::draw(sf::RenderWindow& window, float dt)
{

	ts.changeVersion(version);
	sprite.setTextureRect(ts.getBounds());
	window.draw(sprite);
}

void Ghost::update(Direction direction, float dt)
{
	// do something? maybe nothing
}