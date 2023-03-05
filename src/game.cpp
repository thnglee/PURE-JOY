#include "game.h"
#include "TextureManager.h"	
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;

auto& player(manager.addEntity());

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

	map = new Map();

	// ecs implementation:

	player.addComponent<TransformComponent>(50, 50);
	player.addComponent<SpriteComponent>("assets/Characters/character_spritesheet.png");
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
	manager.refresh();
	manager.update();

	player.getComponent<TransformComponent>().position.Add(Vector2D(1,0));
	if (player.getComponent<TransformComponent>().position.x > 100) {
		player.getComponent<SpriteComponent>().setTex("assets/Characters/cow_spritesheet.png");
	}
}

void Game::render() {
	SDL_RenderClear(renderer);
	map->DrawMap();

	manager.draw(); 
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
