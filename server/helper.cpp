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