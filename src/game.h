#pragma once
#include<stdio.h>
#include<iostream>	
#include "SDL_image.h"
#include "SDL.h"

class Game {
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	
	void handleEvents(); // handle user input
	void update();		 // update the game
	void render();		 // draw the game
	void clean();		 // clean game memory once finished

	bool running() {	 // asking if the game is still running
		return isRunning;
	}		

	static SDL_Renderer* renderer;
	// avoid passing too many same pointer references.

private:
	int cnt = 0; // count - testing if the game is running -> update();
	bool isRunning;
	SDL_Window* window;
};		


