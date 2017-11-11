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
	int getRow(int position);
	int getCol(int position);
	int getLeftTile(int position);
	int getAboveTile(int position);
	int getRightTile(int position);
	int getBottomTile(int position);
	bool isWall(int position);
	
	Helper();
	void loadTiles(int width, int height, std::vector<int> tiles);
private:
	// number of columns in the grid
	int WIDTH;
	// number of rows in the grid
	int HEIGHT;

	// a visualized grid of some random set of tiles
	// 8s are walls, 1s are empty spaces
	std::vector<int> tiles;


};
