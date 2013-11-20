#include "Character.h"

class Mob : public virtual Character
{
	public:
		//Initializes the player
		Mob();

		//Deallocates memory
		~Mob();

		//Deallocates the player
		void free();

		//Loads the sprite from a file
		void loadSprite(SDL_Renderer*);

		void spawnMob(int coordX, int coordY);

		//Updates the sprite location
		void move(int w, int h);

		//Renders the player
		void render(SDL_Renderer*);

		//Returns the sprite Texture
		SDL_Texture* getSprite();

		bool check();

	private:
		int velocityX;
		int velocityY;
		int vel;

		bool boss;

		SDL_RendererFlip flip;
};
