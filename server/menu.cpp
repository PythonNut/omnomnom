#include "menu.hpp"
#include <SFML/Graphics.hpp>

void Menu::handleInput(sf::RenderWindow& window)
{
	
	sf::Event event;

	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
		{
			window.close();
			break;
		}
		case sf::Event::KeyPressed:
		{
			// do something
			moveOn = true;
		}
		default: break;
		}
	}


}

void Menu::draw(sf::RenderWindow& window, float dt)
{
	// display some image
	window.draw(sprite);
}

void Menu::update(Engine* engine, float dt)
{
	if (moveOn)
	{
		engine->state = 1;
		engine->refreshState(1);
	}
}

Menu::Menu()
{
	moveOn = false;

}

Menu::Menu(const std::string& filename)
{
	moveOn = false;

	ts = Texprite(filename, sf::IntRect(0, 0, 960, 832), 1);
	sprite.setTexture(ts.tex);
}