#include "helper.hpp"

int Helper::nextTile(int position, Direction direction)
{
	switch (direction)
	{
	case Direction::UP:
	{
		if (position < WIDTH)
			return -1;
		return position - WIDTH;
	}
	case Direction::DOWN:
	{
		if (position >= WIDTH * (HEIGHT - 1))
			return -1;
		return position + WIDTH;
	}
	case Direction::LEFT:
	{
		if (position % WIDTH == 0)
			return -1;
		return position - 1;
	}
	case Direction::RIGHT:
	{
		if (position % WIDTH == -1 % HEIGHT)
			return -1;
		return position + 1;
	}
	case Direction::NONE:
	{
		return position;
	}
	default:
		return -1;
	}
}

int Helper::getRow(int position) {
    //use int division to get the row
    return position / WIDTH;
}

int Helper::getCol(int position) {
    //use mods to get the column
    return (position % WIDTH);
}

int Helper::getLeftTile(int position) {
    //If on the far left side, loop to the right side
    if (position%WIDTH == 0) {
        return tiles[position+WIDTH-1];
    }
    //Else return the tile directly to the left
    else {
        return tiles[position-1];
    }
}

int Helper::getAboveTile(int position) {
    // If on the top row, loop to the bottom
    if (position < WIDTH){
        return tiles[(HEIGHT*WIDTH) - WIDTH + position];
    }
    else {
        return tiles[position-WIDTH];
    }
}

int Helper::getRightTile(int position) {
    // If on the far right row, loop to the left side
    if (position%WIDTH == (WIDTH-1)){
        return tiles[position-WIDTH+1];
    }
    else{
        return tiles[position+1];
    }
}

int Helper::getBottomTile(int position) {
    // If on the Bottom Row, loop to the top
    if (position >= (HEIGHT*WIDTH)-WIDTH){
        return tiles[(position%WIDTH)];
    }
    else {
        return tiles[position+WIDTH];
    }
}

bool Helper::isWall(int position) {
    if (position >= 7){
        return true;
    }
    else {
        return false;
    }
}

void Helper::loadTiles(int width, int height, std::vector<int> tiles) {
	WIDTH = width;
	HEIGHT = height;
	this->tiles = tiles;
}

Helper::Helper()
{}
