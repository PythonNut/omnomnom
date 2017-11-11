#include "ai.hpp"


AI::AI()
{
    //Nothing to Do
}

AI::AI(Helper& helper)
{
	this->helper = helper;
}

Direction AI::clyde(int pacPosition, int clydePosition, Direction clydeDir)
{   
    std::vector<Direction> validDirections;
    if (!helper.isWall(helper.getAboveTile(clydePosition))){
        validDirections.push_back(Direction::UP);
    }
    if (!helper.isWall(helper.getRightTile(clydePosition))){
        validDirections.push_back(Direction::RIGHT);
    }
    if (!helper.isWall(helper.getBottomTile(clydePosition))){
        validDirections.push_back(Direction::DOWN);
    }     
    if (!helper.isWall(helper.getLeftTile(clydePosition))){
        validDirections.push_back(Direction::LEFT);
    }
    int s = validDirections.size();
    if (s>2){
        int index = rand()%s;
        return validDirections[index];
    }
    else {
        return clydeDir;
    }
}

Direction AI::spasy(int pacPosition, int clydePosition, Direction clydeDir)
{
    std::vector<Direction> validDirections;
    if (!helper.isWall(helper.getAboveTile(clydePosition))){
        validDirections.push_back(Direction::UP);
    }
    if (!helper.isWall(helper.getRightTile(clydePosition))){
        validDirections.push_back(Direction::RIGHT);
    }
    if (!helper.isWall(helper.getBottomTile(clydePosition))){
        validDirections.push_back(Direction::DOWN);
    }     
    if (!helper.isWall(helper.getLeftTile(clydePosition))){
        validDirections.push_back(Direction::LEFT);
    }
    int s = validDirections.size();
    if (s>1){
        int index = rand()%s;
        return validDirections[index];
    }
    else {
        return clydeDir;
    } 
}
