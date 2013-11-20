/*
Project Codename: World Shaper
Project Leader: Mike Pezzetti
Latest Update: Nov 18, 2013
File: Texture.cpp
*/

#include "Texture.h"
//#include "Window.h"

Texture::Texture()
{
	//Initialize
	texture = NULL;
	width = 0;
	height = 0;
}

Texture::~Texture()
{
	//Deallocate
	free();
}

void Texture::loadFromFile(SDL_Renderer* r, std::string path)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(r, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			width = loadedSurface->w;
			height = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	texture = newTexture;
}

void Texture::loadfromSurface(SDL_Renderer* r, SDL_Surface* s)
{
	texture = SDL_CreateTextureFromSurface(r, s);
	width = s->w;
	height = s->h;

	SDL_FreeSurface(s);
}

void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture rgb
	SDL_SetTextureColorMod(texture, red, green, blue);
}

void Texture::setBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(texture, blending);
}
		
void Texture::setAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(texture, alpha);
}

void Texture::free()
{
	//Free texture if it exists
	if(texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
		width = 0;
		height = 0;
	}
}

void Texture::render(SDL_Renderer* r, int x, int y, SDL_Rect* clip, SDL_RendererFlip flip, double angle, SDL_Point* center)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, width, height };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(r, texture, clip, &renderQuad, angle, center, flip);
	SDL_RenderPresent(r);
}

bool Texture::check()
{
	return texture != NULL;
}

int Texture::getWidth()
{
	return width;
}

int Texture::getHeight()
{
	return height;
}

SDL_Texture* Texture::getTexture()
{
	return texture;
}
