#include "game.hpp"


void Game::handleInput(Engine* engine, sf::RenderWindow& window)
{
	// remove this code once we have actual input!
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
			if (event.key.code == sf::Keyboard::Escape)
				window.close();
			if (event.key.code == sf::Keyboard::Left)
			{
				// do left
				level.input(Direction::LEFT);
				//std::cout << "left" << std::endl;
			}
			if (event.key.code == sf::Keyboard::Right)
			{
				// do right
				level.input(Direction::RIGHT);
				//std::cout << "right" << std::endl;
			}
			if (event.key.code == sf::Keyboard::Down)
			{
				// do down
				level.input(Direction::DOWN);
				//std::cout << "down" << std::endl;
			}
			if (event.key.code == sf::Keyboard::Up)
			{
				// do up
				level.input(Direction::UP);
				//std::cout << "up" << std::endl;
			}
			break;
		}
		default: break;
		}
	}

	switch (engine->getInput())
		{
		case 1:
		{
			level.input(Direction::LEFT);
			break;
		}
		case 2:
		{
			level.input(Direction::RIGHT);
			break;
		}
		case 3:
		{
			level.input(Direction::UP);
			break;
		}
		case 4:
		{
			level.input(Direction::DOWN);
			break;
		}
		default:
			break;
	}

	




}

void Game::draw(sf::RenderWindow& window, float dt)
{
	level.drawWalls(window, dt);
	level.drawPlayer(window, dt);
	level.drawGhosts(window, dt);
}

void Game::update(Engine* engine, float dt)
{
	level.update(dt);
	if (level.isGameOver())
		engine->state = 2;
		engine->refreshState(2);
}

Game::Game()
{
}


