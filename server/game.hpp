#pragma once

#include "state.hpp"
#include "level.hpp"


class Game : public State
{
private:
	Level level;
public:
	virtual void draw(sf::RenderWindow& window, const float dt);
	virtual void update(Engine* engine, const float dt);
	virtual void handleInput(Engine* engine, sf::RenderWindow& window);

	Game();
};