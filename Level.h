/*
Project Codename: World Shaper
Project Leader: Mike Pezzetti
Latest Update: Nov 18, 2013
File: Level.h
*/

#include "Texture.h"
#include "Mob.h"

enum LevelSelection
{
	DEMO
};

class Level
{
	public:
		Level();
		~Level();

		void free();

		void loadLevel(SDL_Renderer*, int);
		void closeLevel();

		void render(SDL_Renderer*, SDL_Rect*);

		bool check();

		SDL_Texture* getBackground();

		int getWidth() { return width; }
		int getHeight() { return height; }

	private:
		Texture background;

		int level;

		int width;
		int height;
};
