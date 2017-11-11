#pragma once

#include <vector>
#include "helper.hpp"
#include "player.hpp"


#include <SFML/Graphics.hpp>


class Level
{
private:
	Helper helper;

	std::vector<int> tiles;

	// this will need to change to accomodate textures
	std::vector<sf::RectangleShape> shapes;
	sf::Vector2f playerPos;

	Player player;
	Direction movingDirection;
	Direction turnDirection;

	bool moving;

	// movement helpers
	void playerMove(float dt);

	// other helpers
	int getSquare();
	sf::Vector2f getPosInTile();
	bool willCrossMiddle(Direction direction, float dt);

public:
	const int TILESIZE = 50;
	const int SPEED = 150;
	const int HEIGHT = 8;
	const int WIDTH = 8;
	const float TIMELIMIT = 1;
	void drawWalls(sf::RenderWindow& window, float dt);

	void drawPlayer(sf::RenderWindow& window, float dt);

	void drawGhosts(sf::RenderWindow& window, float dt);

	void loadTiles();



	void input(Direction direction);

	void update(float dt);


	float time;
	float turnTime;
	Level();
};