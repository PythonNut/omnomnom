#pragma once

#include <vector>
#include "helper.hpp"
#include "player.hpp"
#include "ghost.hpp"
#include "ai.hpp"
#include "textures.hpp"

#include <SFML/Graphics.hpp>


class Level
{
private:
	Helper helper;
	Textures textures;
	std::vector<int> tiles;


	// this will need to change to accomodate textures
	std::vector<sf::Sprite> wallsprites;

	std::vector<sf::RectangleShape> shapes; // these are grid textures
	sf::CircleShape dot;

	int score;

	// player stuff
	sf::Vector2f playerPos;
	Player player;
	Direction movingDirection;
	Direction turnDirection;

	int moving;

	// movement helpers
	void playerMove(float dt);

	// and the same for ghosts...
	std::vector<sf::Vector2f> ghostPos;
	std::vector<Ghost> ghosts;
	std::vector<Direction> ghostMovingDirection;
	std::vector<Direction> ghostTurnDirection;
	std::vector<int> ghostsMoving;
	void ghostMove(float dt, int i);
	void ghostInput(Direction direction, int i);

	// AI
	AI ai;

	// other helpers
	int getSquare(sf::Vector2f pos);
	sf::Vector2f getPosInTile(sf::Vector2f pos);
	bool willCrossMiddle(Direction direction, float dt);
	bool willGhostCrossMiddle(Direction direction, int i, float dt);
	bool gameIsOver;
public:
	const int TILESIZE = 64;
	const int SPEED = 150;
	const int GHOSTSPEED = 100;
	const int HEIGHT = 13;
	const int WIDTH = 15;
	const float TIMELIMIT = 1;
	void drawWalls(sf::RenderWindow& window, float dt);

	void drawPlayer(sf::RenderWindow& window, float dt);

	void drawGhosts(sf::RenderWindow& window, float dt);

	void loadTiles();



	void input(Direction direction);

	void update(float dt);

	bool isGameOver();


	float time;
	float turnTime;
	Level();
};