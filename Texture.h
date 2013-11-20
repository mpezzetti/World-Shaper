/*
Project Codename: World Shaper
Project Leader: Mike Pezzetti
Latest Update: Nov 18, 2013
File: Texture.h
*/

#if !defined(_TEXTURE_H_)

#define _TEXTURE_H_

//Using SDL, standard IO, strings, and string streams
#include <stdio.h>
#include <string>
#include <sstream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class Texture
{
	public:
		//Initializes variables
		Texture();

		//Deallocates memory
		~Texture();

		//Loads image at specified path
		void loadFromFile(SDL_Renderer* r, std::string path);

		//Loads image from given Texture
		void loadfromSurface(SDL_Renderer* r, SDL_Surface*);

		//Deallocates texture
		void free();

		//Set color modulation
		void setColor(Uint8 red, Uint8 green, Uint8 blue);

		//Set blending
		void setBlendMode(SDL_BlendMode blending);

		//Set alpha modulation
		void setAlpha( Uint8 alpha );

		//Renders texture at given point
		void render(SDL_Renderer* r, int x = 0, int y = 0, SDL_Rect* clip = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE, double angle = 0.0, SDL_Point* center = NULL);

		//Checks for texture
		bool check();

		//Returns the texture
		SDL_Texture* getTexture();

		//Gets image dimensions
		int getWidth();
		int getHeight();

	private:
		//The actual hardware texture
		SDL_Texture* texture;

		//Image dimensions
		int width;
		int height;
};
#endif
