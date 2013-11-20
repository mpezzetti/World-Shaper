/*
Project Codename: World Shaper
Project Leader: Mike Pezzetti
Latest Update: Nov 18, 2013
File: Level.cpp
*/

#include "Level.h"

Level::Level()
{
	width = 0;
	height = 0;
}

Level::~Level()
{
	free();
}

void Level::free()
{
	background.free();
}

void Level::loadLevel(SDL_Renderer* r, int l)
{
	switch(l)
	{
	case DEMO:
		SDL_Surface *image = IMG_Load("Artwork\\shoama2.png");
		background.loadfromSurface(r, image);
		width = image->w;
		height = image->h;
	break;
	}
}

void Level::closeLevel()
{

}

void Level::render(SDL_Renderer* r, SDL_Rect* clip)
{
	background.render(r, 0, 0, clip);
}

bool Level::check()
{
	return background.getTexture() != NULL;
}

SDL_Texture* Level::getBackground()
{
	return background.getTexture();
}
