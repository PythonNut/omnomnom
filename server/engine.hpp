#pragma once
#include <SFML/Graphics.hpp>



class Engine
{
private:
	void handleInput();
	void update(float dt);
	void draw(float dt);


public:
	void loop();
	sf::RenderWindow window;


	Engine();
};