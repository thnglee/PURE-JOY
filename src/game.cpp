#include "game.h"
#include "TextureManager.h"	
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;

auto& player(manager.addEntity());
auto& wall(manager.addEntity());

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

	player.addComponent<TransformComponent>(3);
	player.addComponent<SpriteComponent>("assets/Characters/character_spritesheet.png");
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	
	wall.addComponent<TransformComponent>(300.0f, 300.0f, 16, 16, 3);
	wall.addComponent<SpriteComponent>("assets/Tilesets/Fences.png");
	wall.addComponent<ColliderComponent>("fences"); 
}


void Game::handleEvents() {
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
	// for (auto cc : colliders) Collision::AABB(player.getComponent<ColliderComponent>(), *cc);
}

void Game::render() {
	SDL_RenderClear(renderer);
	manager.draw(); 
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void Game::AddTile(int id, int x, int y) {
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(x, y, 16, 16, id);
}
