#pragma once

#include<iostream>	
#include "SDL_image.h"
#include "SDL.h"
#include<vector>

const int WINDOW_WIDTH = 1600;
const int WINDOW_HEIGHT = 900;

static const int OBJECT_WIDTH = 16;
const int OBJECT_HEIGHT = 16;
const int MAP_WIDTH = 16 * 50;
const int MAP_HEIGHT = 16 * 50;

class ColliderComponent;

class Game {
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	
	void handleEvents();
	void update();		
	bool running() { return isRunning;}		
	void render();		 
	void clean();		 

	static SDL_Renderer* renderer;
	static SDL_Event event;
	static bool isRunning;
	static SDL_Rect camera;

	enum groupLabels : std::size_t {
		groupMap,
		groupPlayers,
		groupColliders
	};


private:

	int cnt = 0;
	SDL_Window* window;
};		


