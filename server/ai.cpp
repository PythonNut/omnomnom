#include "ai.hpp"


AI::AI()
{
    //Nothing to Do
}

AI::AI(Helper& helper)
{
	this->helper = helper;
}

Direction AI::kinky((int pacPosition, int inkyPosition, Direction inkyDir))
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
        return validDirections[0];
    }
    if (s == 1){
        return validDirections[0];
    }
    if (s == 2){
        return inkyDir;
    }
    pacx = getCol(pacPosition);
    pacy = getRow(pacPosition);
    inkx = getCol(inkyPosition);
    inkyy = getRow(inkyPosition);

    int score = 0;
    Direction best = inkyDir;
    for (iterator i = validDirections.begin();i!=validDirections.end();++i){
        if(validDirections[i] == Direction::UP){
            if ((pacy-inkyy)>score){
                it = find (validDirections.begin(), validDirections.end(), Directions::UP);
                if (it != validDirections.end()){
                    score = pacy-inkyy;
                    best = Direction::UP;
                }
            }
        }
        else if(validDirections[i] == Direction::DOWN){
            if ((inkyy-pacy)>score){
                it = find (validDirections.begin(), validDirections.end(), Directions::DOWN);
                if (it != validDirections.end()){
                    score = inkyy-pacy;
                    best = Direction::DOWN;
                }
            }
        }
        else if(validDirections[i] == Direction::LEFT){
            if ((inkx-pacx)>score){
                it = find (validDirections.begin(), validDirections.end(), Directions::LEFT);
                if (it != validDirections.end()){
                    score = inkx-pacx;
                    best = Direction::LEFT;
                }
            }
        }
        else if(validDirections[i] == Direction::RIGHT){
            if ((pacx-inkx)>score){
                it = find (validDirections.begin(), validDirections.end(), Directions::RIGHT);
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
