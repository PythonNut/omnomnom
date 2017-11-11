#pragma once

#include <vector>

// a class to be used for indicating directions. For example, 
// for any methods may require a direction, you can pass in 
// Direction::UP, Direction::DOWN, etc.
enum class Direction { UP, DOWN, LEFT, RIGHT, NONE };

class Helper
{
public:
	// returns the index of the tile in the indicated direction.
	// currently returns -1 for any invalid input (off the grid, or 
	// Direction::NONE as inputs.
	int nextTile(int position, Direction direction);
private:
	// number of columns in the grid
	const int WIDTH = 8;
	// number of rows in the grid
	const int HEIGHT = 8;

	// a visualized grid of some random set of tiles
	// 8s are walls, 1s are empty spaces
	const std::vector<int> tiles{
		8,8,8,8,8,8,8,8,
		8,1,1,1,1,1,1,8,
		8,1,8,8,1,8,1,8,
		8,1,1,1,1,1,1,8,
		8,8,1,8,8,8,1,8,
		8,8,1,1,1,1,1,8,
		8,8,1,8,8,1,8,8,
		8,8,8,8,8,8,8,8
	};


};