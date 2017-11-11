#include "texprite.hpp"

Texprite::Texprite()
{

}

Texprite::Texprite(const std::string& filename, const sf::IntRect& frameSize, int numVers)
{
	tex.loadFromFile(filename);
	this->frameSize = frameSize;
	bounds = frameSize;
	version = 0;
	this->numVers = numVers;
	return;
}

void Texprite::changeVersion(int version)
{
	// don't change if the change does nothing or isn't valid
	if (version == version || version >= numVers || version < 0) return;

	this->version = version;

	sf::IntRect newBounds = frameSize;
	newBounds.top = version * frameSize.top;
	bounds = newBounds;

	return;
}

sf::IntRect Texprite::getBounds()
{
	return bounds;
}