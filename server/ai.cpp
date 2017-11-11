
#include "ai.hpp"


Ai::Ai()
{
    //Nothing to Do
}

Direction Ai::clyde(std::vector<int> map, int pacPosition, int clydePosition, Direction clydeDir)
{   
    std::vector<Direction> validDirections;
    if !(isWall(getAboveTile(clydePosition))){
        validDirections.push_back(Direction::UP);
    }
    if !(isWall(getRightTile(clydePosition))){
        validDirections.push_back(Direction::RIGHT);
    }
    if !(isWall(getBottomTile(clydePosition))){
        validDirections.push_back(Direction::DOWN);
    }     
    if !(isWall(getLeftTile(clydePosition))){
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

Direction Ai::spasy(std::vector<int> map, int pacPosition, int clydePosition, Direction clydeDir)
{
    std::vector<Direction> validDirections;
    if !(isWall(getAboveTile(clydePosition))){
        validDirections.push_back(Direction::UP);
    }
    if !(isWall(getRightTile(clydePosition))){
        validDirections.push_back(Direction::RIGHT);
    }
    if !(isWall(getBottomTile(clydePosition))){
        validDirections.push_back(Direction::DOWN);
    }     
    if !(isWall(getLeftTile(clydePosition))){
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
