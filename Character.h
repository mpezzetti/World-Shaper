/*
Project Codename: World Shaper
Project Leader: Mike Pezzetti
Latest Update: Nov 18, 2013
File: Character.h
*/

#if !defined(_CHARACTER_H_)

#define _CHARACTER_H_

#include "Texture.h"

enum CharacterType
{
	NO_OBJECT,
	PLAYER,
	MOB
};

enum MovementDirection
{
	DEFAULT,
	UP,
	DOWN,
	LEFT,
	RIGHT
};

enum FaceDirection
{
	NORTH,
	SOUTH,
	EAST,
	WEST
};

//Walking Animation
const int IDLE_FRAMES = 2;
const int WALKING_FRAMES = 6;

class Character
{
	public:
		Character();
		//~Character();
		//virtual void collide();
		//SDL_Texture* getSprite();
		
		int getX();
		int getY();
		int getW();
		int getH();

	protected:
		Texture spriteSheet;
		SDL_Rect spriteMoveClips[WALKING_FRAMES];	
		SDL_Rect spriteIdleClips[IDLE_FRAMES];

		int frame;
		int idle;

		int direction;

		SDL_RendererFlip flip;

		//The coordinates on screen
		int x;
		int y;
		int width;
		int height;
};
#endif
