#include <SFML/Graphics.hpp>

#include "textures.hpp"

void Textures::loadTexture(const std::string& name, const std::string &filename)
{
	/* Load the texture */
	sf::Texture tex;
	tex.loadFromFile(filename);
	/* and add it to the map */
	this->textureMap[name] = tex;

	return;
}

sf::Texture& Textures::getTexture(const std::string& name)
{
	return this->textureMap.at(name);
}