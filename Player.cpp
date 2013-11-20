/*
Project Codename: World Shaper
Project Leader: Mike Pezzetti
Latest Update: Nov 18, 2013
File: Player.cpp
*/

#include "Player.h"

Player::Player()
{
	//Initialize
	x = 0;
	y = 0;
	width = 100;
	height = 100;
	velocityX = 0;
	velocityY = 0;
	vel = 5;
}

Player::~Player()
{
	//Deallocate
	spriteSheet.free();
}

void Player::free()
{
	spriteSheet.free();
}

void Player::loadSprite(SDL_Renderer* r)
{
	spriteSheet.loadFromFile(r, "Artwork\\personSheet2.png");

	for (int i = 0; i < WALKING_FRAMES + IDLE_FRAMES; i++)
	{
		if (i < IDLE_FRAMES)
		{
			spriteIdleClips[i].x = width*i;
			spriteIdleClips[i].y =   0;
			spriteIdleClips[i].w = width;
			spriteIdleClips[i].h = height;
		}
		else
		{
			spriteMoveClips[i - IDLE_FRAMES].x = width*(i);
			spriteMoveClips[i - IDLE_FRAMES].y =   0;
			spriteMoveClips[i - IDLE_FRAMES].w = width;
			spriteMoveClips[i - IDLE_FRAMES].h = height;
		}
	}
	
}

void Player::handleEvent(SDL_Event& e)
{
	//If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        //Adjust the velocity
        switch(e.key.keysym.sym)
        {
            case SDLK_w:
				velocityY -= vel;
			break;
            case SDLK_s:
				velocityY += vel;
			break;
            case SDLK_a:
				velocityX -= vel;
				direction = WEST;
				flip = SDL_FLIP_NONE;
			break;
            case SDLK_d:
				velocityX += vel;
				direction = EAST;
				flip = SDL_FLIP_HORIZONTAL;
			break;
        }
    }
    //If a key was released
    else if(e.type == SDL_KEYUP)
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_w:
				velocityY += vel;
			break;
            case SDLK_s:
				velocityY -= vel;
			break;
            case SDLK_a:
				velocityX += vel;
			break;
            case SDLK_d:
				velocityX -= vel;
			break;
        }
    }
}

void Player::move(int w, int h)
{
	//Move the dot left or right
    x += velocityX;

    //If the dot went too far to the left or right
    if( ( x < 0 ) || ( (x + width) > w) )
    {
        //Move back
        x -= velocityX;
    }

    //Move the dot up or down
    y += velocityY;

    //If the dot went too far up or down
    if( ( y < 0 ) || ( (y + height) > h) )
    {
        //Move back
        y -= velocityY;
    }
}

void Player::render(SDL_Renderer* r, int camX, int camY)
{
	if (velocityY == 0 && velocityX == 0)
	{
		spriteSheet.render(r, (x - camX), (y - camY), &spriteIdleClips[idle], flip);

		//Go to next frame
		idle = (idle + 1)%IDLE_FRAMES;
		frame = 0;
	}
	else
	{
		
		spriteSheet.render(r, (x - camX), (y - camY), &spriteMoveClips[frame], flip);

		//Go to next frame
		frame = (frame + 1)%WALKING_FRAMES;
		idle = 0;
	}	
}

bool Player::check()
{
	return spriteSheet.getTexture() != NULL;
}
