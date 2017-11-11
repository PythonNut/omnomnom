#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <map>

// create an instance of this class for each set of textures you need, and feed it the textures you want to load.
class Textures
{
private:

	/* A map containing the textures used */
	std::map<std::string, sf::Texture> textureMap;

public:

	void loadTexture(const std::string& name, const std::string& filename);

	sf::Texture& getTexture(const std::string& texture);

};