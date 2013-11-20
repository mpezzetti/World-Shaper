/*
Project Codename: World Shaper
Project Leader: Mike Pezzetti
Latest Update: Nov 18, 2013
File: Window.cpp
*/

#include "Window.h"

Window::Window()
{
	//Initialize non-existant window
	window = NULL;
	renderer = NULL;

	fullScreen = false;
	shown = false;
	
	width = 0;
	height = 0;

	//The camera area
	camera.x = 0;
	camera.y = 0;
	camera.h = SCREEN_HEIGHT;
	camera.w = SCREEN_WIDTH;
}

bool Window::init()
{
	//Set texture filtering to linear
	if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
	{
		printf( "Warning: Linear texture filtering not enabled!" );
	}

	//Enable VSync
	/*if( !SDL_SetHint( SDL_HINT_RENDER_VSYNC, "1" ) )
	{
		printf( "Warning: VSync not enabled!" );
	}*/

	//Create window
	window = SDL_CreateWindow( "World Shaper v0.0.1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	if(window != NULL)
	{
		width = SCREEN_WIDTH;
		height = SCREEN_HEIGHT;

		//Create renderer for window
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if(renderer == NULL)
		{
			printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Initialize renderer color
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF );
		
			//Initialize PNG loading
			int imgFlags = IMG_INIT_PNG;
			if( !( IMG_Init( imgFlags ) & imgFlags ) )
			{
				printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
			}
		}
	}
	else
	{
		printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
	}

	return window != NULL;
}

void Window::handleEvent( SDL_Event& e )
{
	//If an event was detected for this window
	if(e.type == SDL_WINDOWEVENT)
	{
		//Caption update flag
		bool updateCaption = false;

		switch( e.window.event )
		{
			//Window appeared
			case SDL_WINDOWEVENT_SHOWN:
				shown = true;
			break;

			//Window disappeared
			case SDL_WINDOWEVENT_HIDDEN:
				shown = false;
			break;

			//Get new dimensions and repaint
			case SDL_WINDOWEVENT_SIZE_CHANGED:
				width = e.window.data1;
				height = e.window.data2;
				SDL_RenderPresent(renderer);
			break;

			//Repaint on expose
			case SDL_WINDOWEVENT_EXPOSED:
				SDL_RenderPresent(renderer);
			break;

			//Hide on close
			case SDL_WINDOWEVENT_CLOSE:
				SDL_HideWindow(window);
			break;
		}

		//Update window caption with new data
		if( updateCaption )
		{
			std::stringstream caption;
			SDL_SetWindowTitle( window, caption.str().c_str() );
		}
	}
}

void Window::clear()
{
	//Clear screen
	SDL_RenderSetScale(renderer, 1.f, 1.f);
	SDL_SetRenderDrawColor(renderer, 0xF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);
}

void Window::update(Level& l, Player& p)
{
	//Clear screen
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear(renderer );

	//Render background
	l.render(renderer, &camera);

	//Render objects
	p.render(renderer, camera.x, camera.y);

	//Update screen
	SDL_RenderPresent(renderer);
}

void Window::updateCamera(Level& l, int x, int y, int h, int w)
{
	//Center the camera over the player
	camera.x = (x + w/2) - SCREEN_WIDTH / 2;
	camera.y = (y + h/2) - SCREEN_HEIGHT / 2;

	//Keep the camera in bounds
	if( camera.x < 0 )
	{ 
		camera.x = 0;
	}
	if( camera.y < 0 )
	{
		camera.y = 0;
	}
	if( camera.x > l.getWidth() - camera.w )
	{
		camera.x = l.getWidth() - camera.w;
	}
	if( camera.y > l.getHeight() - camera.h )
	{
		camera.y = l.getHeight() - camera.h;
	}
}

void Window::setCamera(int x, int y, int h, int w)
{
	
}

int Window::getCamX()
{
	return camera.x;
}

int Window::getCamY()
{
	return camera.y;
}

SDL_Rect Window::getCamera()
{
	return camera;
}

void Window::free()
{
	if( window != NULL )
	{
		//Destroy window	
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		window = NULL;
		renderer = NULL;
	}

	width = 0;
	height = 0;
}

SDL_Renderer* Window::getRenderer()
{
	return renderer;
}

int Window::getWidth()
{
	return width;
}

int Window::getHeight()
{
	return height;
}

bool Window::isShown()
{
	return shown;
}
