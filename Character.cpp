/*
Project Codename: World Shaper
Project Leader: Mike Pezzetti
Latest Update: Nov 18, 2013
File: Character.cpp
*/

#include "Character.h"

Character::Character()
{
	//Initialize
	frame = 0;
	idle = 0;
	direction = WEST;
	flip = SDL_FLIP_NONE;
}

int Character::getX()
{
	return x;
}

int Character::getY()
{
	return y;
}

int Character::getW()
{
	return width;
}

int Character::getH()
{
	return height;
}
