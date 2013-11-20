/*
Project Codename: World Shaper
Project Leader: Mike Pezzetti
Latest Update: Nov 18, 2013
*/

#include "Window.h"

//Initialize SDL
bool init(Window&);

//Loads data
void loadData(Window& w, Player&, Level&);

//Frees media and shuts down SDL
void close(Window&, Player&, Level&);


bool init(Window& win)
{
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		return false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
			return false;
		}

		return win.init();
	}
}

void loadData(Window& w, Player& p, Level& l)
{
	//Load player texture
	p.loadSprite(w.getRenderer());
	if(!p.check())
	{
		printf( "Failed to load Foo' texture image!\n" );
	}

	//Load level data
	l.loadLevel(w.getRenderer(), DEMO);
	if (!l.check())
	{
		printf( "Failed to load Level!\n" );
	}

	//if(!background.check()) //LOL background checks
	//{
	//	printf( "Failed to load background texture image!\n" );
	//}
}

void close(Window& win, Player& p, Level& l)
{
	//Destroy Textures
	p.free();
	l.free();
	
	//Destroy window
	win.free();
	
	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* args[])
{
	//Declaring the objects
	Window win0;
	Player player;
	Level level;

	//Start up SDL and create window
	if(!init(win0))
	{
		printf( "Failed to initialize!\n" );
		system("pause");
	}
	else
	{
		//Load data
		loadData(win0, player, level);

		//Render window
		win0.clear();
		level.render(win0.getRenderer(), &win0.getCamera());

		//Render Player
		player.render(win0.getRenderer(), win0.getCamX(), win0.getCamY());

		win0.updateCamera(level, player.getX(), player.getY(), player.getH(), player.getW());

		//Main loop flag
		bool quit = false;

		//Event handler
		SDL_Event e;

		//While application is running
		while( !quit )
		{
			//Handle events on queue
			while( SDL_PollEvent( &e ) != 0 )
			{
				//User requests quit
				if( e.type == SDL_QUIT )
				{
					quit = true;
				}
				//User presses a key
				else if( e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
				{
					player.handleEvent(e);
					win0.clear();
					player.move(level.getWidth(), level.getHeight());
					win0.updateCamera(level, player.getX(), player.getY(), player.getH(), player.getW());
					win0.update(level, player);
				}
				else
				{
					win0.handleEvent(e);
				}
				
			}
		}
	}

	//Free resources and close SDL
	close(win0, player, level);

	return 0;
}
