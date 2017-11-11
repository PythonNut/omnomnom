#pragma once

#include "helper.hpp"
#include <stdlib.h>

class AI
{
public:
    AI();
	AI(Helper& helper);

    Direction clyde(int pacPosition, int clydePosition, Direction clydeDir);
    Direction spasy(int pacPosition, int clydePosition, Direction clydeDir);
private:
	Helper helper;

};