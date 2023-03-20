#pragma once

#include<iostream>	
#include "SDL_image.h"
#include "SDL.h"
#include<vector>

class ColliderComponent;

class Game {
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	
	void handleEvents();
	void update();		
	void render();		 
	void clean();		 

	bool running() {	 
		return isRunning;
	}		

	static void AddTile(int srcX, int srcY, int xpos, int ypos);

	static SDL_Renderer* renderer;
	static SDL_Event event;
	static std::vector<ColliderComponent*> colliders;

private:

	bool isRunning;
	int cnt = 0;
	SDL_Window* window;
};		


