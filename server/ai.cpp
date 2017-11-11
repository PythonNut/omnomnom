#include "ai.hpp"


AI::AI()
{
    //Nothing to Do
}

AI::AI(Helper& helper)
{
	this->helper = helper;
}

Direction AI::kinky(int pacPosition, int inkyPosition, Direction inkyDir)
{
    std::vector<Direction> validDirections;
    if (!helper.isWall(helper.getAboveTile(inkyPosition))){
        validDirections.push_back(Direction::UP);
    }
    if (!helper.isWall(helper.getRightTile(inkyPosition))){
        validDirections.push_back(Direction::RIGHT);
    }
    if (!helper.isWall(helper.getBottomTile(inkyPosition))){
        validDirections.push_back(Direction::DOWN);
    }     
    if (!helper.isWall(helper.getLeftTile(inkyPosition))){
        validDirections.push_back(Direction::LEFT);
    }
    int s = validDirections.size();
    if (s == 0){
        return validDirections[0];
    }
    if (s == 1){
        return validDirections[0];
    }
    if (s == 2){
        return inkyDir;
    }
    int pacx = helper.getCol(pacPosition);
    int pacy = helper.getRow(pacPosition);
    int inkx = helper.getCol(inkyPosition);
    int inkyy = helper.getRow(inkyPosition);

    int score = 0;
    Direction best = inkyDir;
    for (auto i = validDirections.begin();i!=validDirections.end();++i){
        if(*i == Direction::UP){
            if ((pacy-inkyy)>score){
                auto it = find (validDirections.begin(), validDirections.end(), Direction::UP);
                if (it != validDirections.end()){
                    score = pacy-inkyy;
                    best = Direction::UP;
                }
            }
        }
        else if(*i == Direction::DOWN){
            if ((inkyy-pacy)>score){
                auto it = find (validDirections.begin(), validDirections.end(), Direction::DOWN);
                if (it != validDirections.end()){
                    score = inkyy-pacy;
                    best = Direction::DOWN;
                }
            }
        }
        else if(*i == Direction::LEFT){
            if ((inkx-pacx)>score){
                auto it = find (validDirections.begin(), validDirections.end(), Direction::LEFT);
                if (it != validDirections.end()){
                    score = inkx-pacx;
                    best = Direction::LEFT;
                }
            }
        }
        else if(*i == Direction::RIGHT){
            if ((pacx-inkx)>score){
                auto it = find (validDirections.begin(), validDirections.end(), Direction::RIGHT);
                if (it != validDirections.end()){
                    score = pacx-inkx;
                    best = Direction::RIGHT;
                }
            }
        }
    }
    return best;
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
    if (s == 0){
        //If this line runs, there is significant trouble
		return Direction::NONE;
    }
    else if(clydeDir == Direction::NONE){
        clydesConscious = true;
        int index = rand()%s;
        return validDirections[index];
    }
    else if ((s>2 && !clydesConscious)) {
        clydesConscious = true;
        int index = rand()%s;
        return validDirections[index];
    }
    else if (s<=2){
        clydesConscious = false;
        return clydeDir;
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
    if (s == 0){
		return Direction::NONE;
    }
    else if(clydeDir == Direction::NONE){
        int index = rand()%s;
        return validDirections[index];
    }
    else if (s>1){
        int index = rand()%s;
        return validDirections[index];
    }
    else {
        return clydeDir;
    } 
}
