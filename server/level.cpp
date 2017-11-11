#include "level.hpp"
#include "helper.hpp"

#include <iostream>

Level::Level()
{
	// maybe changhe this later
	shapes = {
		sf::RectangleShape{ sf::Vector2f(TILESIZE,TILESIZE) },
		sf::RectangleShape{ sf::Vector2f(TILESIZE,TILESIZE) }
	};

	shapes[1].setFillColor(sf::Color::Black);
	shapes[0].setFillColor(sf::Color::Cyan);


	playerPos = { 75, 75 };

	time = 0;
	turnTime = 0;
	moving = false;

	movingDirection = Direction::NONE;
	turnDirection = Direction::NONE;

	tiles = { 0,0,0,0,0,0,0,0,
		0,1,1,1,1,1,1,0,
		0,1,0,0,1,0,1,0,
		0,1,1,1,1,1,1,0,
		0,0,1,0,0,0,1,0,
		0,0,1,1,1,1,1,0,
		0,0,1,0,0,1,0,0,
		0,0,0,0,0,0,0,0
	};

	helper.loadTiles(8, 8, tiles);
}

void Level::drawWalls(sf::RenderWindow& window, float dt)
{
	for (int i = 0; i < 64; ++i) {
		shapes[tiles[i]].setPosition((i % 8) * TILESIZE, (i / 8) * TILESIZE);
		window.draw(shapes[tiles[i]]);
	}
}

void Level::drawPlayer(sf::RenderWindow& window, float dt)
{
	player.shape.setPosition(playerPos);
	player.draw(window, dt);
}

void Level::loadTiles() {}

void Level::input(Direction direction)
{
	turnDirection = direction;
	moving = true;
	turnTime = 0;
	if (movingDirection == Direction::NONE) {
		// check whether it is safe to move.
		// doesn't handle stopped-in-corner cases, only stopped-at-edge cases
		// essentiall checks whether or not the thing is in the middle of the lane, and if not
		// it shouldn't be able to move along that axis
		if (playerPos.y - int(playerPos.y / TILESIZE) * TILESIZE != TILESIZE / 2 &&
			(turnDirection == Direction::LEFT || turnDirection == Direction::RIGHT)) {
			// now check whether we're close (TILESIZE/3) from being at a turn, and if so, then make it do that
			float offset = playerPos.y - int(playerPos.y / TILESIZE) * TILESIZE - TILESIZE / 2;
			if (offset > 0 && offset < TILESIZE / 2 && tiles[helper.nextTile(getSquare(), turnDirection)] == 1) {
				movingDirection = Direction::UP;
				time = 0;
			}
			else if (offset < 0 && offset > TILESIZE / (-2) && tiles[helper.nextTile(getSquare(), turnDirection)] == 1) {
				movingDirection = Direction::DOWN;
				time = 0;
			}
			else {
				moving = false;
				turnDirection = Direction::NONE;
				return;
			}
		}
		else if (playerPos.x - int(playerPos.x / TILESIZE) * TILESIZE != TILESIZE / 2 &&
			(turnDirection == Direction::UP || turnDirection == Direction::DOWN)) {
			float offset = playerPos.x - int(playerPos.x / TILESIZE) * TILESIZE - TILESIZE / 2;
			if (offset > 0 && offset < TILESIZE / 2 && tiles[helper.nextTile(getSquare(), turnDirection)] == 1) {
				movingDirection = Direction::LEFT;
				time = 0;
			}
			else if (offset < 0 && offset > TILESIZE / (-2) && tiles[helper.nextTile(getSquare(), turnDirection)] == 1) {
				movingDirection = Direction::RIGHT;
				time = 0;
			}
			else {
				moving = false;
				turnDirection = Direction::NONE;
				return;
			}

		}
		else {
			movingDirection = direction;
			time = 0;
		}

	}
	// if continue, reset time.
	if (movingDirection == turnDirection) {
		time = 0;
	}
	// if opposite direction, immediately flip
	if (turnDirection == Direction::LEFT && movingDirection == Direction::RIGHT ||
		turnDirection == Direction::RIGHT && movingDirection == Direction::LEFT ||
		turnDirection == Direction::UP && movingDirection == Direction::DOWN ||
		turnDirection == Direction::DOWN && movingDirection == Direction::UP) {
		movingDirection = turnDirection;
		time = 0;
	}


}

void Level::playerMove(float dt)
{
	if (!moving) return;
	if (willCrossMiddle(movingDirection, dt)) {
		// if there is a turn queued:
		if (turnDirection != movingDirection) {
			// if there is a tile to turn onto:
			if (tiles[helper.nextTile(getSquare(), turnDirection)] == 1) {
				// turn
				switch (movingDirection)
				{
				case Direction::LEFT:
				{
					float preTurn = playerPos.x - int(playerPos.x / TILESIZE) * TILESIZE - TILESIZE / 2;
					playerPos.x = int(playerPos.x / TILESIZE) * TILESIZE + TILESIZE / 2;

					if (turnDirection == Direction::DOWN)
						playerPos.y += (dt * SPEED - preTurn);
					if (turnDirection == Direction::UP)
						playerPos.y -= (dt * SPEED - preTurn);
					break;
				}
				case Direction::RIGHT:
				{
					float preTurn = int(playerPos.x / TILESIZE) * TILESIZE + TILESIZE / 2 - playerPos.x;
					playerPos.x = int(playerPos.x / TILESIZE) * TILESIZE + TILESIZE / 2;

					if (turnDirection == Direction::DOWN)
						playerPos.y += (dt * SPEED - preTurn);
					if (turnDirection == Direction::UP)
						playerPos.y -= (dt * SPEED - preTurn);
					break;
				}
				case Direction::DOWN:
				{
					float preTurn = int(playerPos.y / TILESIZE) * TILESIZE + TILESIZE / 2 - playerPos.y;
					playerPos.y = int(playerPos.y / TILESIZE) * TILESIZE + TILESIZE / 2;

					if (turnDirection == Direction::RIGHT)
						playerPos.x += (dt * SPEED - preTurn);
					if (turnDirection == Direction::LEFT)
						playerPos.x -= (dt * SPEED - preTurn);
					break;
				}
				case Direction::UP:
				{
					float preTurn = playerPos.y - int(playerPos.y / TILESIZE) * TILESIZE - TILESIZE / 2;
					playerPos.y = int(playerPos.y / TILESIZE) * TILESIZE + TILESIZE / 2;

					if (turnDirection == Direction::DOWN)
						playerPos.x += (dt * SPEED - preTurn);
					if (turnDirection == Direction::UP)
						playerPos.x -= (dt * SPEED - preTurn);
					break;
				}
				default:
					break;
				}

				movingDirection = turnDirection;
				time = turnTime;

				return;
			}
		}
		// check that it can cross the middle

		// also need to make sure not going along strange paths
		if (tiles[helper.nextTile(getSquare(), movingDirection)] != 1) {

			// set position to snap to middle of tile
			if (movingDirection == Direction::LEFT || movingDirection == Direction::RIGHT)
				playerPos.x = int(playerPos.x / TILESIZE) * TILESIZE + TILESIZE / 2;
			else
				playerPos.y = int(playerPos.y / TILESIZE) * TILESIZE + TILESIZE / 2;
			movingDirection = Direction::NONE;
			turnDirection = Direction::NONE;
			moving = false;
			return;
		}
	}
	// otherwise, we can just move
	switch (movingDirection)
	{
	case Direction::LEFT:
	{
		playerPos.x -= dt * SPEED;
		return;
	}
	case Direction::RIGHT:
	{
		playerPos.x += dt * SPEED;
		return;
	}
	case Direction::DOWN:
	{
		playerPos.y += dt * SPEED;
		return;
	}
	case Direction::UP:
	{
		playerPos.y -= dt * SPEED;
		return;
	}
	default:
		return;
	}

}

bool Level::willCrossMiddle(Direction direction, float dt)
{
	switch (direction)
	{
	case Direction::LEFT:
	{
		return getPosInTile().x >= TILESIZE / 2 &&
			getPosInTile().x - dt * SPEED < TILESIZE / 2;
	}
	case Direction::RIGHT:
	{
		return getPosInTile().x <= TILESIZE / 2 &&
			getPosInTile().x + dt * SPEED > TILESIZE / 2;
	}
	case Direction::DOWN:
	{
		return getPosInTile().y <= TILESIZE / 2 &&
			getPosInTile().y + dt * SPEED > TILESIZE / 2;
	}
	case Direction::UP:
	{
		return getPosInTile().y >= TILESIZE / 2 &&
			getPosInTile().y - dt * SPEED < TILESIZE / 2;
	}
	default:
		return false;
	}
}

int Level::getSquare()
{
	return int(playerPos.x) / TILESIZE + (int(playerPos.y) / TILESIZE) * 8;
}

sf::Vector2f Level::getPosInTile()
{
	return sf::Vector2f(playerPos.x - int(playerPos.x / TILESIZE) * TILESIZE,
		playerPos.y - int(playerPos.y / TILESIZE) * TILESIZE);
}

void Level::update(float dt)
{
	time += dt;
	turnTime += dt;

	// if has received a successful input in the past 2 secs, 
	// continue moving, else stop

	playerMove(dt);
	player.update(movingDirection, dt);

	if (time > TIMELIMIT) {
		moving = false;
		movingDirection = Direction::NONE;
	}
}