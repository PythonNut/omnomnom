#pragma once

#include "state.hpp"
class Menu : public State
{
private:
	bool moveOn;
public:
	virtual void draw(sf::RenderWindow& window, const float dt);
	virtual void update(Engine* engine, const float dt);
	virtual void handleInput(sf::RenderWindow& window);

	Menu();
	Menu(const std::string& filename);
};