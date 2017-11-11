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
		}
		default: break;
		}
	}


}

void Menu::draw(sf::RenderWindow& window, float dt)
{
	// display some image
}

void Menu::update(Engine* engine, float dt)
{
	
}

Menu::Menu()
{

}