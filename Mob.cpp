#include "Mob.h"

Mob::Mob()
{
	//Initialize
	x = 0;
	y = 0;
	width = 100;
	height = 100;
	velocityX = 0;
	velocityY = 0;
	vel = 5;
	boss = false;
}

Mob::~Mob()
{
	//Deallocate
	spriteSheet.free();
}

void Mob::free()
{
	spriteSheet.free();
}

void Mob::loadSprite(SDL_Renderer* r)
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

void Mob::spawnMob(int coordX, int coordY)
{
	x = coordX;
	y = coordY;
}

void Mob::move(int w, int h)
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

void Mob::render(SDL_Renderer* r)
{
	if (velocityY == 0 && velocityX == 0)
	{
		spriteSheet.render(r, (x), (y), &spriteIdleClips[idle], flip);

		//Go to next frame
		idle = (idle + 1)%IDLE_FRAMES;
		frame = 0;
	}
	else
	{
		
		spriteSheet.render(r, (x), (y), &spriteMoveClips[frame], flip);

		//Go to next frame
		frame = (frame + 1)%WALKING_FRAMES;
		idle = 0;
	}	
}

bool Mob::check()
{
	return spriteSheet.getTexture() != NULL;
}
