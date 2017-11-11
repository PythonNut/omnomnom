#include "level.hpp"
#include "helper.hpp"

#include <iostream>

Level::Level()
{
	// maybe changhe this later
	shapes = {
		sf::RectangleShape{ sf::Vector2f(TILESIZE,TILESIZE) },
		sf::RectangleShape{ sf::Vector2f(TILESIZE,TILESIZE) },
		sf::RectangleShape{ sf::Vector2f(TILESIZE,TILESIZE) },
		sf::RectangleShape{ sf::Vector2f(TILESIZE,TILESIZE) },
		sf::RectangleShape{ sf::Vector2f(TILESIZE,TILESIZE) },
		sf::RectangleShape{ sf::Vector2f(TILESIZE,TILESIZE) },
		sf::RectangleShape{ sf::Vector2f(TILESIZE,TILESIZE) },
		sf::RectangleShape{ sf::Vector2f(TILESIZE,TILESIZE) },
		sf::RectangleShape{ sf::Vector2f(TILESIZE,TILESIZE) },
		sf::RectangleShape{ sf::Vector2f(TILESIZE,TILESIZE) },
		sf::RectangleShape{ sf::Vector2f(TILESIZE,TILESIZE) }
	};

	shapes[1].setFillColor(sf::Color::Black);
	shapes[8].setFillColor(sf::Color::Cyan);

	// init player
	playerPos = { 75, 75 };

	time = 0;
	turnTime = 0;
	moving = false;

	movingDirection = Direction::NONE;
	turnDirection = Direction::NONE;

	//
	ghosts = { Ghost{sf::Color::Color(255,160,0)} };

	ghostPos = { {275, 325} };

	ghostMovingDirection = { Direction::NONE };

	ghostTurnDirection = { Direction::NONE };

	ghostsMoving = { false };
	tiles = { 
		8,8,8,8,8,8,8,8,
		8,1,1,1,1,1,1,8,
		8,1,8,8,1,8,1,8,
		8,1,1,1,1,1,1,8,
		8,8,1,8,8,8,1,8,
		8,8,1,1,1,1,1,8,
		8,8,1,8,8,1,8,8,
		8,8,8,8,8,8,8,8
	};

	helper.loadTiles(8, 8, tiles);


	// init AI
	ai = AI(helper);
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

void Level::drawGhosts(sf::RenderWindow& window, float dt)
{
	for (int k = 0; k < ghosts.size(); ++k) {
		ghosts[k].shape.setPosition(ghostPos[k]);
		ghosts[k].draw(window, dt);
	}
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
			if (offset > 0 && offset < TILESIZE / 2 && tiles[helper.nextTile(getSquare(playerPos), turnDirection)] < 7) {
				movingDirection = Direction::UP;
				time = 0;
			}
			else if (offset < 0 && offset > TILESIZE / (-2) && tiles[helper.nextTile(getSquare(playerPos), turnDirection)] < 7) {
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
			if (offset > 0 && offset < TILESIZE / 2 && tiles[helper.nextTile(getSquare(playerPos), turnDirection)] < 7) {
				movingDirection = Direction::LEFT;
				time = 0;
			}
			else if (offset < 0 && offset > TILESIZE / (-2) && tiles[helper.nextTile(getSquare(playerPos), turnDirection)] < 7) {
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
			if (tiles[helper.nextTile(getSquare(playerPos), turnDirection)] < 7) {
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
		if (tiles[helper.nextTile(getSquare(playerPos), movingDirection)] >= 7) {

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
		return getPosInTile(playerPos).x >= TILESIZE / 2 &&
			getPosInTile(playerPos).x - dt * SPEED < TILESIZE / 2;
	}
	case Direction::RIGHT:
	{
		return getPosInTile(playerPos).x <= TILESIZE / 2 &&
			getPosInTile(playerPos).x + dt * SPEED > TILESIZE / 2;
	}
	case Direction::DOWN:
	{
		return getPosInTile(playerPos).y <= TILESIZE / 2 &&
			getPosInTile(playerPos).y + dt * SPEED > TILESIZE / 2;
	}
	case Direction::UP:
	{
		return getPosInTile(playerPos).y >= TILESIZE / 2 &&
			getPosInTile(playerPos).y - dt * SPEED < TILESIZE / 2;
	}
	default:
		return false;
	}
}

int Level::getSquare(sf::Vector2f pos)
{
	return int(pos.x) / TILESIZE + (int(pos.y) / TILESIZE) * 8;
}

sf::Vector2f Level::getPosInTile(sf::Vector2f pos)
{
	return sf::Vector2f(pos.x - int(pos.x / TILESIZE) * TILESIZE,
		pos.y - int(pos.y / TILESIZE) * TILESIZE);
}

void Level::update(float dt)
{
	time += dt;
	turnTime += dt;

	ghostInput(ai.clyde(getSquare(playerPos), getSquare(ghostPos[0]), ghostMovingDirection[0]), 0);

	for (int k = 0; k < ghosts.size(); ++k) {
		ghostMove(dt, k);

		ghosts[k].update(ghostMovingDirection[k], dt);
	}


	// if has received a successful input in the past 2 secs, 
	// continue moving, else stop





	playerMove(dt);
	player.update(movingDirection, dt);

	if (time > TIMELIMIT) {
		moving = false;
		movingDirection = Direction::NONE;
	}
}





void Level::ghostInput(Direction direction, int i)
{
	ghostTurnDirection[i] = direction;
	ghostsMoving[i] = true;
	if (ghostMovingDirection[i] == Direction::NONE) {
		// check whether it is safe to move.
		// doesn't handle stopped-in-corner cases, only stopped-at-edge cases
		// essentiall checks whether or not the thing is in the middle of the lane, and if not
		// it shouldn't be able to move along that axis
		if (ghostPos[i].y - int(ghostPos[i].y / TILESIZE) * TILESIZE != TILESIZE / 2 &&
			(ghostTurnDirection[i] == Direction::LEFT || ghostTurnDirection[i] == Direction::RIGHT)) {
			// now check whether we're close (TILESIZE/3) from being at a turn, and if so, then make it do that
			float offset = ghostPos[i].y - int(ghostPos[i].y / TILESIZE) * TILESIZE - TILESIZE / 2;
			if (offset > 0 && offset < TILESIZE / 2 && tiles[helper.nextTile(getSquare(ghostPos[i]), ghostTurnDirection[i])] < 7) {
				ghostMovingDirection[i] = Direction::UP;
			}
			else if (offset < 0 && offset > TILESIZE / (-2) && tiles[helper.nextTile(getSquare(ghostPos[i]), ghostTurnDirection[i])] < 7) {
				ghostMovingDirection[i] = Direction::DOWN;
			}
			else {
				ghostsMoving[i] = false;
				ghostTurnDirection[i] = Direction::NONE;
				return;
			}
		}
		else if (ghostPos[i].x - int(ghostPos[i].x / TILESIZE) * TILESIZE != TILESIZE / 2 &&
			(ghostTurnDirection[i] == Direction::UP || ghostTurnDirection[i] == Direction::DOWN)) {
			float offset = ghostPos[i].x - int(ghostPos[i].x / TILESIZE) * TILESIZE - TILESIZE / 2;
			if (offset > 0 && offset < TILESIZE / 2 && tiles[helper.nextTile(getSquare(ghostPos[i]), ghostTurnDirection[i])] < 7) {
				ghostMovingDirection[i] = Direction::LEFT;
			}
			else if (offset < 0 && offset > TILESIZE / (-2) && tiles[helper.nextTile(getSquare(ghostPos[i]), ghostTurnDirection[i])] < 7) {
				ghostMovingDirection[i] = Direction::RIGHT;
			}
			else {
				ghostsMoving[i] = false;
				ghostTurnDirection[i] = Direction::NONE;
				return;
			}

		}
		else {
			ghostMovingDirection[i] = direction;
		}

	}
	// if opposite direction, immediately flip
	if (ghostTurnDirection[i] == Direction::LEFT && ghostMovingDirection[i] == Direction::RIGHT ||
		ghostTurnDirection[i] == Direction::RIGHT && ghostMovingDirection[i] == Direction::LEFT ||
		ghostTurnDirection[i] == Direction::UP && ghostMovingDirection[i] == Direction::DOWN ||
		ghostTurnDirection[i] == Direction::DOWN && ghostMovingDirection[i] == Direction::UP) {
		ghostMovingDirection[i] = ghostTurnDirection[i];
	}


}

void Level::ghostMove(float dt, int i)
{
	if (!ghostsMoving[i]) return;
	if (willCrossMiddle(ghostMovingDirection[i], dt)) {
		// if there is a turn queued:
		if (ghostTurnDirection[i] != ghostMovingDirection[i]) {
			// if there is a tile to turn onto:
			if (tiles[helper.nextTile(getSquare(ghostPos[i]), ghostTurnDirection[i])] < 7) {
				// turn
				switch (ghostMovingDirection[i])
				{
				case Direction::LEFT:
				{
					float preTurn = ghostPos[i].x - int(ghostPos[i].x / TILESIZE) * TILESIZE - TILESIZE / 2;
					ghostPos[i].x = int(ghostPos[i].x / TILESIZE) * TILESIZE + TILESIZE / 2;

					if (ghostTurnDirection[i] == Direction::DOWN)
						ghostPos[i].y += (dt * SPEED - preTurn);
					if (ghostTurnDirection[i] == Direction::UP)
						ghostPos[i].y -= (dt * SPEED - preTurn);
					break;
				}
				case Direction::RIGHT:
				{
					float preTurn = int(ghostPos[i].x / TILESIZE) * TILESIZE + TILESIZE / 2 - ghostPos[i].x;
					ghostPos[i].x = int(ghostPos[i].x / TILESIZE) * TILESIZE + TILESIZE / 2;

					if (ghostTurnDirection[i] == Direction::DOWN)
						ghostPos[i].y += (dt * SPEED - preTurn);
					if (ghostTurnDirection[i] == Direction::UP)
						ghostPos[i].y -= (dt * SPEED - preTurn);
					break;
				}
				case Direction::DOWN:
				{
					float preTurn = int(ghostPos[i].y / TILESIZE) * TILESIZE + TILESIZE / 2 - ghostPos[i].y;
					ghostPos[i].y = int(ghostPos[i].y / TILESIZE) * TILESIZE + TILESIZE / 2;

					if (ghostTurnDirection[i] == Direction::RIGHT)
						ghostPos[i].x += (dt * SPEED - preTurn);
					if (ghostTurnDirection[i] == Direction::LEFT)
						ghostPos[i].x -= (dt * SPEED - preTurn);
					break;
				}
				case Direction::UP:
				{
					float preTurn = ghostPos[i].y - int(ghostPos[i].y / TILESIZE) * TILESIZE - TILESIZE / 2;
					ghostPos[i].y = int(ghostPos[i].y / TILESIZE) * TILESIZE + TILESIZE / 2;

					if (ghostTurnDirection[i] == Direction::DOWN)
						ghostPos[i].x += (dt * SPEED - preTurn);
					if (ghostTurnDirection[i] == Direction::UP)
						ghostPos[i].x -= (dt * SPEED - preTurn);
					break;
				}
				default:
					break;
				}

				ghostMovingDirection[i] = ghostTurnDirection[i];

				return;
			}
		}
		// check that it can cross the middle

		// also need to make sure not going along strange paths
		if (tiles[helper.nextTile(getSquare(ghostPos[i]), ghostMovingDirection[i])] >= 7) {

			// set position to snap to middle of tile
			if (ghostMovingDirection[i] == Direction::LEFT || ghostMovingDirection[i] == Direction::RIGHT)
				ghostPos[i].x = int(ghostPos[i].x / TILESIZE) * TILESIZE + TILESIZE / 2;
			else
				ghostPos[i].y = int(ghostPos[i].y / TILESIZE) * TILESIZE + TILESIZE / 2;
			ghostMovingDirection[i] = Direction::NONE;
			ghostTurnDirection[i] = Direction::NONE;
			ghostsMoving[i] = false;
			return;
		}
	}
	// otherwise, we can just move
	switch (ghostMovingDirection[i])
	{
	case Direction::LEFT:
	{
		ghostPos[i].x -= dt * SPEED;
		return;
	}
	case Direction::RIGHT:
	{
		ghostPos[i].x += dt * SPEED;
		return;
	}
	case Direction::DOWN:
	{
		ghostPos[i].y += dt * SPEED;
		return;
	}
	case Direction::UP:
	{
		ghostPos[i].y -= dt * SPEED;
		return;
	}
	default:
		return;
	}

}
