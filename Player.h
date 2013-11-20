/*
Project Codename: World Shaper
Project Leader: Mike Pezzetti
Latest Update: Nov 18, 2013
File: Player.h
*/

#include "Character.h"

class Player : public virtual Character
{
	public:
		//Initializes the player
		Player();

		//Deallocates memory
		~Player();

		//Deallocates the player
		void free();

		//Loads the sprite from a file
		void loadSprite(SDL_Renderer*);

		//Handles events
		void handleEvent(SDL_Event&);

		//Updates the sprite location
		void move(int w, int h);

		//Renders the player
		void render(SDL_Renderer*, int camX, int camY);

		//Returns the sprite Texture
		SDL_Texture* getSprite();

		bool check();

	private:
		int velocityX;
		int velocityY;
		int vel;
};
