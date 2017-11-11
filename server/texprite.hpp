#pragma once

#include <SFML/Graphics.hpp>

#include <string>

class Texprite
{
private:

	

	int version;
	int numVers;
	sf::IntRect bounds;
	sf::IntRect frameSize;
public:
	sf::Texture tex;
	sf::IntRect getBounds();

	void changeVersion(int version);

	Texprite(const std::string& filename, const sf::IntRect& frameSize, int numVers);
	Texprite();
};