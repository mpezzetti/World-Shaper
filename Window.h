/*
Project Codename: World Shaper
Project Leader: Mike Pezzetti
Latest Update: Nov 18, 2013
File: Window.h
*/

#if !defined(_WINDOW_H_)
#define _WINDOW_H_

#include "Player.h"
#include "Level.h"

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

class Window
{
	public:
		//Initializes internals
		Window();

		//Creates window
		bool init();

		//Handles window events
		void handleEvent(SDL_Event&);

		//Clears the window
		void clear();

		//updates the window
		void update(Level&, Player&);

		//updates the camera
		void updateCamera(Level&, int x, int y, int h, int w);

		//Sets the camera
		void setCamera(int x, int y, int h, int w);

		//Returns the camera
		int getCamX();
		int getCamY();
		SDL_Rect getCamera();

		//Checks the window
		void check();

		//Deallocates internals
		void free();

		//Returns the Renderer
		SDL_Renderer* getRenderer();

		//Window dimensions
		int getWidth();
		int getHeight();

		//Window focii
		bool isShown();

	private:
		//Window data
		SDL_Window* window;
		SDL_Renderer* renderer;

		//Camera
		SDL_Rect camera;

		//Window dimensions
		int width;
		int height;

		//Window focus
		bool fullScreen;
		bool shown;
};
#endif
