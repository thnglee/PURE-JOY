#include "game.h"
#include "TextureManager.h"	
#include "GameObject.h"
#include "Map.h"

GameObject* cow;
GameObject* bunny;
Map* map;

SDL_Renderer* Game::renderer = nullptr;

Game::Game() {}
Game::~Game() {}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}
		isRunning = true;
	}
	else isRunning = false;

	cow = new GameObject("assets/Characters/cow_spritesheet.png", 0, 0);
	bunny = new GameObject("assets/Characters/character_actions_spritesheet.png", 50, 50);
	map = new Map();
}


void Game::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;

	default:
		break;
	}
}

void Game::update() {
	cow->Update();
	bunny->Update();
}

void Game::render() {
	SDL_RenderClear(renderer);
	map->DrawMap();
	cow->Render();
	bunny->Render();
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
