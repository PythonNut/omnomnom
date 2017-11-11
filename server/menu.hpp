#pragma once

#include "state.hpp"
#include "textures.hpp"
#include "texprite.hpp"
class Menu : public State
{
private:
	bool moveOn;
	Textures textures;
	Texprite ts;
	sf::Sprite sprite;
public:
	virtual void draw(sf::RenderWindow& window, const float dt);
	virtual void update(Engine* engine, const float dt);
	virtual void handleInput(Engine* engine, sf::RenderWindow& window);

	Menu();
	Menu(const std::string& filename);
};